#include "PVZ.hpp"
#include "imageTools.hpp"
#include "debug/debug.hpp"
#include <file/file_utils.hpp>
#include <cmath>
#include <cstring>
#include <draw_buffers.h>
#include <jpeglib.h>
#include <malloc.h>
#include <setjmp.h>
#include <stdio.h>
#include <png.h>

struct JpgPixel3 {
  u8 r, g, b;
};

static u32 getTextureSize(const u32& width, const u32& height,
                   const Tyra::TextureBpp& bpp) {
  switch (bpp) {
    case Tyra::bpp32:
      return (width * height * 4);
    case Tyra::bpp24:
      return (width * height * 3);
    case Tyra::bpp8:
      return (width * height);
    case Tyra::bpp4:
      return (width * height / 2);
    default:
      TYRA_TRAP("Unknown texture bpp");
  }

  return -1;
}

struct my_error_mgr {
  struct jpeg_error_mgr pub; /* "public" fields */

  jmp_buf setjmp_buffer; /* for return to caller */
};

typedef struct my_error_mgr* my_error_ptr;

METHODDEF(void)
my_error_exit(j_common_ptr cinfo) {
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr)cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message)(cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}

/** Based on GsKit texture loading - thank you guys! */
JpgScaleData JpgImageScale::load(const char* fullPath,
                                              const TextureScale sWidth,
                                              const TextureScale sHeight) {
  std::string path = fullPath;
  TYRA_ASSERT(!path.empty(), "Provided path is empty!");

  auto filename = Tyra::FileUtils::getFilenameFromPath(path);

  FILE* file = fopen(fullPath, "rb");
  TYRA_ASSERT(file != nullptr, "Failed to load ", fullPath);

  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;

  /* We set up the normal JPEG error routines, then override error_exit. */
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  /* Establish the setjmp return context for my_error_exit to use. */

  if (setjmp(jerr.setjmp_buffer)) {
    /* If we get here, the JPEG code has signaled an error.
     * We need to clean up the JPEG object, close the input file, and return.
     */
    jpeg_destroy_decompress(&cinfo);
    fclose(file);
    TYRA_ASSERT(!setjmp(jerr.setjmp_buffer),
                "jpeg: error during processing file");
  }
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  jpeg_start_decompress(&cinfo);

  std::vector<Tyra::TextureBuilderData*> textures;
  JpgScaleData jpgData;

  Tyra::TextureBuilderData* result = new Tyra::TextureBuilderData();
  result->width = cinfo.output_width;
  result->height = cinfo.output_height;
  result->name = filename;
  result->gsComponents = TEXTURE_COMPONENTS_RGB;

  
  int widthBlock = ceil((float)result->height/sHeight);
  int heightBlock = ceil((float)result->width/sWidth);

  jpgData.width = heightBlock;
  jpgData.height = widthBlock;


  // printf("cinfo %d,%d\n",result->width,result->height);
  // printf("cinfo %d/%d=%d,%d/%d=%d\n",result->width,sWidth,heightBlock,result->height,sHeight,widthBlock);

  int textureSize;

  if (cinfo.out_color_components == JCS_YCbCr) {
    result->bpp = Tyra::bpp24;
    textureSize = getTextureSize(result->width, result->height, Tyra::bpp24);

    result->data = static_cast<unsigned char*>(memalign(128, textureSize));
    memset(result->data, 0, textureSize);

    unsigned int row_stride = textureSize / result->height;
    unsigned char* row_pointer = result->data;

    while (cinfo.output_scanline < cinfo.output_height) {
      jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&row_pointer, 1);
      row_pointer += row_stride;
    }
    
    JpgPixel3* pixel = (JpgPixel3*) result->data; 

    int textureMax = heightBlock * widthBlock;
    // printf("textureMax: %d\n",textureMax);
    int textureCount = 0;
    int h=0;
    int w=0;
    int hmax=0;
    int wmax=0;
    int test=0;
    // while(test != 7){
    while(w != heightBlock && h!=widthBlock){
      test++;
      int p=0;
      int i=h*sHeight;
      int j=w*sWidth;
      hmax = i + sHeight;
      wmax = j + sWidth;
      
      if(hmax > result->height){
        hmax = result->height;
      }

      if(wmax > result->width){
        wmax = result->width;
      }
      
      Tyra::TextureBuilderData* texData = new Tyra::TextureBuilderData();
      texData->width = sWidth;
      texData->height = sHeight;
      texData->name = filename;
      texData->gsComponents = TEXTURE_COMPONENTS_RGB;
      texData->bpp = Tyra::bpp24;
      textureSize = getTextureSize(sWidth, sHeight, Tyra::bpp24);
      texData->data = static_cast<unsigned char*>(memalign(128, textureSize));
      memset(texData->data, 0, textureSize);
      JpgPixel3* jpgData = (JpgPixel3*) texData->data;
      // printf("textureCount %d: %d,%d. %d,%d\n",textureCount,i,j,hmax,wmax);
      int l=0;
      for(;i < hmax; i++){
        j = w * sWidth;
        p = i * result->width + j;
        // printf("p: %d\n",p);
        // printf("l: %d\n",l);
        for(;j < wmax; j++){
          // printf("p: %d\n",p);
          jpgData[l] = pixel[p];
          // i:0,j=0 - i:0,j=127
          // i:1,j=0 - i:1,j=127 = i:1*1400=1400,j=0 - i:1*1400=1400,j=127 
          p++;
          l++;
        }
        if(wmax == result->width){
          // printf("pase 1\n");
          l += (w*sWidth) + sWidth - wmax;
          // l+=;
        }
        // printf("sali\n");
      }
      w++;
      if(w==heightBlock){
        h++;
        w=0;
      }
      
      textureCount++;
      textures.push_back(texData);
    }
    delete result->data;   
    jpgData.data = textures;
  } else if (cinfo.out_color_components == JCS_CMYK) {
    result->bpp = Tyra::bpp32;
    textureSize = getTextureSize(result->width, result->height, Tyra::bpp32);

    result->data = static_cast<unsigned char*>(memalign(128, textureSize));
    memset(result->data, 0, textureSize);

    unsigned int row_stride = textureSize / result->height;
    unsigned char* row_pointer = result->data;

    while (cinfo.output_scanline < cinfo.output_height) {
      jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&row_pointer, 1);
      row_pointer += row_stride;
    }
  } else if (cinfo.out_color_components == JCS_GRAYSCALE) {
    /**
     * This color of 8 bits is converted to 24 bits
     */
    result->bpp = Tyra::bpp24;
    textureSize = getTextureSize(result->width, result->height, Tyra::bpp8);

    result->data = static_cast<unsigned char*>(memalign(128, textureSize));
    memset(result->data, 0, textureSize);

    unsigned int row_stride = textureSize / result->height;
    unsigned char* row_pointer = result->data;

    while (cinfo.output_scanline < cinfo.output_height) {
      jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&row_pointer, 1);
      row_pointer += row_stride;
    }

    unsigned char* newArray = static_cast<unsigned char*>(memalign(
        128, getTextureSize(result->width, result->height, Tyra::bpp24)));
    int u = 0;
    for (int i = 0; i < result->height * result->width; i++) {
      newArray[u++] = result->data[i];
      newArray[u++] = result->data[i];
      newArray[u++] = result->data[i];
    }
    delete result->data;
    result->data = newArray;
  } else
    TYRA_TRAP("This texture depth is not supported!");

  jpeg_finish_decompress(&cinfo);

  jpeg_destroy_decompress(&cinfo);
  fclose(file);

  return jpgData;
}

JpgScaleData JpgImageScale::load(Tyra::Texture* texture, const TextureScale sWidth,
  const TextureScale sHeight, const int TextureComponent){
    if(texture == nullptr){
      TYRA_TRAP("ERROR CUTTING TEXTURE");
    }

    // JCS_YCbCr
    std::vector<Tyra::TextureBuilderData*> textures;
    JpgScaleData jpgData;
    JpgPixel3* pixel = (JpgPixel3*) texture->core->data; 
    int widthBlock = ceil((float)texture->core->height/sHeight);
    int heightBlock = ceil((float)texture->core->width/sWidth);
    
    jpgData.width = heightBlock;
    jpgData.height = widthBlock;
    int textureMax = heightBlock * widthBlock;
    // printf("textureMax: %d\n",textureMax);
    int textureCount = 0;
    int h=0;
    int w=0;
    int hmax=0;
    int wmax=0;
    int test=0;
    // while(test != 1){
    while(w != heightBlock && h!=widthBlock){
      test++;
      int p=0;
      int i=h*sHeight;
      int j=w*sWidth;
      hmax = i + sHeight;
      wmax = j + sWidth;
      
      // printf("texture->core->height:%d\n",texture->core->height);
      if(hmax > texture->core->height){
        hmax = texture->core->height;
      }

      if(wmax > texture->core->width){
        wmax = texture->core->width;
      }
      printf("x:%d,y:%d,hmax:%d,wmax:%d\n",i,j,hmax,wmax);
      
      Tyra::TextureBuilderData* texData = new Tyra::TextureBuilderData();
      texData->width = sWidth;
      texData->height = sHeight;
      texData->name = texture->name;
      texData->gsComponents = TextureComponent;
      texData->bpp = Tyra::bpp24;
      int textureSize = getTextureSize(sWidth, sHeight, Tyra::bpp24);
      texData->data = static_cast<unsigned char*>(memalign(128, textureSize));
      memset(texData->data, 0, textureSize);
      
      JpgPixel3* jpgData = (JpgPixel3*) texData->data;
      // printf("textureCount %d: %d,%d. %d,%d\n",textureCount,i,j,hmax,wmax);
      int l=0;
      for(;i < hmax; i++){
        j = w * sWidth;
        p = i * texture->core->width + j;
        // printf("p: %d\n",p);
        // printf("l: %d\n",l);
        for(;j < wmax; j++){
          // printf("p: %d\n",p);
          jpgData[l] = pixel[p];
          // i:0,j=0 - i:0,j=127
          // i:1,j=0 - i:1,j=127 = i:1*1400=1400,j=0 - i:1*1400=1400,j=127 
          p++;
          l++;
        }
        if(wmax == texture->core->width){
          // printf("pase 1\n");
          l += (w*sWidth) + sWidth - wmax;
          // l+=;
        }
        // printf("sali\n");
      }
      w++;
      if(w==heightBlock){
        h++;
        w=0;
      }
      
      textureCount++;
      textures.push_back(texData);
    } 
    jpgData.data = textures;
    return jpgData;
}

JpgScaleData PNGImageScale::load(Tyra::Texture* texture, const TextureScale sWidth,
  const TextureScale sHeight, const int TextureComponent){
    if(texture == nullptr){
      TYRA_TRAP("ERROR CUTTING TEXTURE");
    }
    texture->print();
    
    std::vector<Tyra::TextureBuilderData*> textures;
    JpgScaleData jpgData;
    JpgPixel3* pixel = (JpgPixel3*) texture->core->data; 
    int widthBlock = ceil((float)texture->core->height/sHeight);
    int heightBlock = ceil((float)texture->core->width/sWidth);
    
    jpgData.width = heightBlock;
    jpgData.height = widthBlock;
    int textureMax = heightBlock * widthBlock;
    // printf("textureMax: %d\n",textureMax);
    int textureCount = 0;
    int h=0;
    int w=0;
    int hmax=0;
    int wmax=0;
    int test=0;
    
    if(texture->clut->data != nullptr && texture->core->bpp == Tyra::bpp8){
      printf("png 8bits\n");
    }else if(texture->core->bpp == Tyra::bpp24){
      printf("png 3\n");
      // while(test != 1){
      while(w != heightBlock && h!=widthBlock){
        test++;
        int p=0;
        int i=h*sHeight;
        int j=w*sWidth;
        hmax = i + sHeight;
        wmax = j + sWidth;
        
        if(hmax > texture->core->height){
          hmax = texture->core->height;
        }
  
        if(wmax > texture->core->width){
          wmax = texture->core->width;
        }
        
        Tyra::TextureBuilderData* texData = new Tyra::TextureBuilderData();
        texData->width = sWidth;
        texData->height = sHeight;
        texData->name = texture->name;
        texData->gsComponents = TextureComponent;
        texData->bpp = Tyra::bpp24;
        int textureSize = getTextureSize(sWidth, sHeight, Tyra::bpp24);
        texData->data = static_cast<unsigned char*>(memalign(128, textureSize));
        memset(texData->data, 0, textureSize);
        
        JpgPixel3* jpgData = (JpgPixel3*) texData->data;
        // printf("textureCount %d: %d,%d. %d,%d\n",textureCount,i,j,hmax,wmax);
        int l=0;
        for(;i < hmax; i++){
          j = w * sWidth;
          p = i * texture->core->width + j;
          // printf("p: %d\n",p);
          // printf("l: %d\n",l);
          for(;j < wmax; j++){
            // printf("p: %d\n",p);
            jpgData[l] = pixel[p];
            // i:0,j=0 - i:0,j=127
            // i:1,j=0 - i:1,j=127 = i:1*1400=1400,j=0 - i:1*1400=1400,j=127 
            p++;
            l++;
          }
          if(wmax == texture->core->width){
            // printf("pase 1\n");
            l += (w*sWidth) + sWidth - wmax;
            // l+=;
          }
          // printf("sali\n");
        }
        w++;
        if(w==heightBlock){
          h++;
          w=0;
        }
        
        textureCount++;
        textures.push_back(texData);
      }
    }
     
    jpgData.data = textures;
    return jpgData;
}

JpgScaleData PNGImageScale::loadOne(Tyra::Texture* texture, const TextureScale sWidth,
  const TextureScale sHeight, const int TextureComponent){
    if(texture == nullptr){
      TYRA_TRAP("ERROR CUTTING TEXTURE");
    }
    texture->print();
    
    std::vector<Tyra::TextureBuilderData*> textures;
    JpgScaleData jpgData;
    JpgPixel3* pixel = (JpgPixel3*) texture->core->data; 
    int widthBlock = ceil((float)texture->core->height/sHeight);
    int heightBlock = ceil((float)texture->core->width/sWidth);
    
    jpgData.width = heightBlock;
    jpgData.height = widthBlock;
    int textureMax = heightBlock * widthBlock;
    // printf("textureMax: %d\n",textureMax);
    int textureCount = 0;
    int h=0;
    int w=0;
    int hmax=0;
    int wmax=0;
    int test=0;
    
    if(texture->clut->data != nullptr && texture->core->bpp == Tyra::bpp8){
      printf("png 8bits\n");
    }else if(texture->core->bpp == Tyra::bpp24){
      printf("png 3\n");
      // while(test != 1){
      while(w != heightBlock && h!=widthBlock){
        test++;
        int p=0;
        int i=h*sHeight;
        int j=w*sWidth;
        hmax = i + sHeight;
        wmax = j + sWidth;
        
        if(hmax > texture->core->height){
          hmax = texture->core->height;
        }
  
        if(wmax > texture->core->width){
          wmax = texture->core->width;
        }
        
        Tyra::TextureBuilderData* texData = new Tyra::TextureBuilderData();
        texData->width = sWidth;
        texData->height = sHeight;
        texData->name = texture->name;
        texData->gsComponents = TextureComponent;
        texData->bpp = Tyra::bpp24;
        int textureSize = getTextureSize(sWidth, sHeight, Tyra::bpp24);
        texData->data = static_cast<unsigned char*>(memalign(128, textureSize));
        memset(texData->data, 0, textureSize);
        
        JpgPixel3* jpgData = (JpgPixel3*) texData->data;
        // printf("textureCount %d: %d,%d. %d,%d\n",textureCount,i,j,hmax,wmax);
        int l=0;
        for(;i < hmax; i++){
          j = w * sWidth;
          p = i * texture->core->width + j;
          // printf("p: %d\n",p);
          // printf("l: %d\n",l);
          for(;j < wmax; j++){
            // printf("p: %d\n",p);
            jpgData[l] = pixel[p];
            // i:0,j=0 - i:0,j=127
            // i:1,j=0 - i:1,j=127 = i:1*1400=1400,j=0 - i:1*1400=1400,j=127 
            p++;
            l++;
          }
          if(wmax == texture->core->width){
            // printf("pase 1\n");
            l += (w*sWidth) + sWidth - wmax;
            // l+=;
          }
          // printf("sali\n");
        }
        w++;
        if(w==heightBlock){
          h++;
          w=0;
        }
        
        textureCount++;
        textures.push_back(texData);
      }
    }
     
    jpgData.data = textures;
    return jpgData;
}

unsigned char* RotateClut(Tyra::PngPixel4* data){
  // unsigned char clutDataNormal[256*4];
  unsigned char* clutData = static_cast<unsigned char*>(memalign(128, getTextureSize(16, 16, Tyra::bpp32)));;
  
  Tyra::PngPixel4* pngClutData = (Tyra::PngPixel4*)clutData;
  for (int i = 0; i < 256; i++) {
    pngClutData[i] = data[i];
  }
  for (int i = 0; i < 256; i++) {
    if ((i & 0x18) == 8) {
      struct Tyra::PngPixel4 tmp = pngClutData[i];
      pngClutData[i] = pngClutData[i + 8];
      pngClutData[i + 8] = tmp;
    }
  }
  return clutData;
}


void SetAlphaFrom8BppToJPG(Tyra::PngPixel3* jpgData, Tyra::PngPixel4* clutData,
  unsigned char* clutPos, int width, int height){
  float alphaval;
  int clutColor;
  int v=0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if(i==22 && j == 152){
        printf("pixel clut pos[%d]: %d\n",v,clutPos[v]);
        printf("pixel clut[%d]: %d,%d,%d\n",v,clutData[clutPos[v]].r,clutData[clutPos[v]].g,clutData[clutPos[v]].b);
      }
      
      clutColor= clutData[clutPos[v]].r;
      // if(clutData[clutPos[v]].g>clutColor){
      //   clutColor = clutData[clutPos[v]].g;
      //   if(clutData[clutPos[v]].b>clutColor){
      //     clutColor = clutData[clutPos[v]].b;
      //   }
      // }else if(clutData[clutPos[v]].b>clutColor){
      //   clutColor = clutData[clutPos[v]].b;
      // }
      alphaval = ((float)clutColor / 255);
      jpgData[v].r *= alphaval;
      jpgData[v].g *= alphaval;
      jpgData[v].b *= alphaval;
      v++;
    }
  }
}

struct PngClut {
  u8 r, g, b, a;
};

/** Based on GsKit texture loading - thank you guys! */
Tyra::TextureBuilderData* PngLoaderUnlimited::load(const char* fullPath) {
  std::string path = fullPath;
  TYRA_ASSERT(!path.empty(), "Provided path is empty!");

  auto filename = Tyra::FileUtils::getFilenameFromPath(path);

  FILE* file = fopen(fullPath, "rb");
  TYRA_ASSERT(file != nullptr, "Failed to load ", fullPath);

  png_structp pngPtr;
  png_infop infoPtr;
  png_uint_32 width, height;
  png_bytep* rowPointers = nullptr;

  u32 sigRead = 0;
  int bitDepth, colorType, interlaceType;

  pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp) nullptr,
                                  nullptr, nullptr);
  TYRA_ASSERT(pngPtr, "PNG read struct init failed for: ", filename);

  infoPtr = png_create_info_struct(pngPtr);
  TYRA_ASSERT(infoPtr, "PNG read struct init failed for: ", filename);

  TYRA_ASSERT(!setjmp(png_jmpbuf(pngPtr)), "PNG read error for: ", filename);

  png_init_io(pngPtr, file);
  png_set_sig_bytes(pngPtr, sigRead);
  png_read_info(pngPtr, infoPtr);
  png_get_IHDR(pngPtr, infoPtr, &width, &height, &bitDepth, &colorType,
               &interlaceType, nullptr, nullptr);

  if (bitDepth == 16) png_set_strip_16(pngPtr);
  if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 4) png_set_expand(pngPtr);

  png_set_filler(pngPtr, 0xff, PNG_FILLER_AFTER);

  png_read_update_info(pngPtr, infoPtr);

  auto* result = new Tyra::TextureBuilderData();
  result->width = width;
  result->height = height;
  result->name = filename;

  auto updatedColorType = png_get_color_type(pngPtr, infoPtr);
  printf("color: %d\n",updatedColorType);
  if (updatedColorType == PNG_COLOR_TYPE_PALETTE) {
    handlePalletized(result, pngPtr, infoPtr, rowPointers, bitDepth);
  } else if (updatedColorType == PNG_COLOR_TYPE_RGB_ALPHA) {
    handle32bpp(result, pngPtr, infoPtr, rowPointers);
  } else if (updatedColorType == PNG_COLOR_TYPE_RGB) {
    handle24bpp(result, pngPtr, infoPtr, rowPointers);
  } else if (updatedColorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
    handleGrayAlpha(result, pngPtr, infoPtr, rowPointers);
  } else if (updatedColorType == PNG_COLOR_TYPE_GRAY) {
    handleGray(result, pngPtr, infoPtr, rowPointers);
  } else
    TYRA_TRAP("This texture depth is not supported!");

  png_read_end(pngPtr, nullptr);
  png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);
  fclose(file);

  return result;
}

void PngLoaderUnlimited::handle32bpp(Tyra::TextureBuilderData* result, png_structp pngPtr,
                              png_infop infoPtr, png_bytep* rowPointers) {
  int rowBytes = png_get_rowbytes(pngPtr, infoPtr);

  result->gsComponents = TEXTURE_COMPONENTS_RGBA;
  result->bpp = Tyra::bpp32;

  int originalWidth = result->width;
  int originalHeight = result->height;

  if (result->width == 8) {
    result->width = 8;
  } else if (result->width <= 16) {
    result->width = 16;
  } else if (result->width <= 32) {
    result->width = 32;
  } else if (result->width <= 64) {
    result->width = 64;
  } else if (result->width <= 128) {
    result->width = 128;
  } else if (result->width <= 256) {
    result->width = 256;
  } else if (result->width <= 512) {
    result->width = 512;
  }

  if (result->height == 8) {
    result->height = 8;
  } else if (result->height <= 16) {
    result->height = 16;
  } else if (result->height <= 32) {
    result->height = 32;
  } else if (result->height <= 64) {
    result->height = 64;
  } else if (result->height <= 128) {
    result->height = 128;
  } else if (result->height <= 256) {
    result->height = 256;
  } else if (result->height <= 512) {
    result->height = 512;
  }

  result->data = static_cast<unsigned char*>(memalign(
      128, getTextureSize(result->width, result->height, result->bpp)));

  rowPointers =
      static_cast<png_bytep*>(calloc(result->height, sizeof(png_bytep)));

  for (int row = 0; row < result->height; row++)
    rowPointers[row] = static_cast<png_bytep>(malloc(rowBytes));

  png_read_image(pngPtr, rowPointers);

  struct Tyra::PngPixel4* pixels = (struct Tyra::PngPixel4*)result->data;

  int k = 0;
  for (int i = 0; i < originalHeight; i++) {
    for (int j = 0; j < originalWidth; j++) {
      pixels[k].r = rowPointers[i][4 * j];
      pixels[k].g = rowPointers[i][4 * j + 1];
      pixels[k].b = rowPointers[i][4 * j + 2];
      pixels[k++].a = ((int)rowPointers[i][4 * j + 3] * 128 / 255);
    }
    for (int j = 0; j < result->width - originalWidth; j++) {
      pixels[k].r = 0;
      pixels[k].g = 0;
      pixels[k].b = 0;
      pixels[k++].a = 0;
    }
  }

  for (int i = 0; i < result->height - originalHeight; i++) {
    for (int j = 0; j < result->width; j++) {
      pixels[k++].a = 0;
    }
  }

  for (int row = 0; row < result->height; row++) free(rowPointers[row]);

  free(rowPointers);
}

void PngLoaderUnlimited::handle24bpp(Tyra::TextureBuilderData* result, png_structp pngPtr,
                              png_infop infoPtr, png_bytep* rowPointers) {
  int rowBytes = png_get_rowbytes(pngPtr, infoPtr);

  result->gsComponents = TEXTURE_COMPONENTS_RGB;
  result->bpp = Tyra::bpp24;
  result->data = static_cast<unsigned char*>(memalign(
      128, getTextureSize(result->width, result->height, result->bpp)));

  rowPointers =
      static_cast<png_bytep*>(calloc(result->height, sizeof(png_bytep)));

  for (int row = 0; row < result->height; row++)
    rowPointers[row] = static_cast<png_bytep>(malloc(rowBytes));

  png_read_image(pngPtr, rowPointers);

  struct Tyra::PngPixel3* pixels = (struct Tyra::PngPixel3*)result->data;

  int k = 0;
  for (int i = 0; i < result->height; i++) {
    for (int j = 0; j < result->width; j++) {
      pixels[k].r = rowPointers[i][4 * j];
      pixels[k].g = rowPointers[i][4 * j + 1];
      pixels[k++].b = rowPointers[i][4 * j + 2];
    }
  }

  for (int row = 0; row < result->height; row++) free(rowPointers[row]);

  free(rowPointers);
}

void PngLoaderUnlimited::handleGrayAlpha(Tyra::TextureBuilderData* result,
                                  png_structp pngPtr, png_infop infoPtr,
                                  png_bytep* rowPointers) {
  int rowBytes = png_get_rowbytes(pngPtr, infoPtr);

  result->gsComponents = TEXTURE_COMPONENTS_RGBA;
  result->bpp = Tyra::bpp32;

  int originalWidth = result->width;
  int originalHeight = result->height;

  if (result->width == 8) {
    result->width = 8;
  } else if (result->width <= 16) {
    result->width = 16;
  } else if (result->width <= 32) {
    result->width = 32;
  } else if (result->width <= 64) {
    result->width = 64;
  } else if (result->width <= 128) {
    result->width = 128;
  } else if (result->width <= 256) {
    result->width = 256;
  } else if (result->width <= 512) {
    result->width = 512;
  }

  if (result->height == 8) {
    result->height = 8;
  } else if (result->height <= 16) {
    result->height = 16;
  } else if (result->height <= 32) {
    result->height = 32;
  } else if (result->height <= 64) {
    result->height = 64;
  } else if (result->height <= 128) {
    result->height = 128;
  } else if (result->height <= 256) {
    result->height = 256;
  } else if (result->height <= 512) {
    result->height = 512;
  }

  result->data = static_cast<unsigned char*>(memalign(
      128, getTextureSize(result->width, result->height, result->bpp)));

  rowPointers =
      static_cast<png_bytep*>(calloc(result->height, sizeof(png_bytep)));

  for (int row = 0; row < result->height; row++)
    rowPointers[row] = static_cast<png_bytep>(malloc(rowBytes));

  png_read_image(pngPtr, rowPointers);

  struct Tyra::PngPixel4* pixels = (struct Tyra::PngPixel4*)result->data;

  int k = 0;
  for (int i = 0; i < originalHeight; i++) {
    for (int j = 0; j < originalWidth; j++) {
      pixels[k].r = rowPointers[i][2 * j];
      pixels[k].g = pixels[k].r;
      pixels[k].b = pixels[k].r;
      pixels[k].a = ((int)rowPointers[i][2 * j + 1] * 128 / 255);
      k++;
    }
    for (int j = 0; j < result->width - originalWidth; j++) {
      pixels[k].r = 0;
      pixels[k].g = 0;
      pixels[k].b = 0;
      pixels[k++].a = 0;
    }
  }

  for (int i = 0; i < result->height - originalHeight; i++) {
    for (int j = 0; j < result->width; j++) {
      pixels[k++].a = 0;
    }
  }

  for (int row = 0; row < result->height; row++) free(rowPointers[row]);

  free(rowPointers);
}

void PngLoaderUnlimited::handleGray(Tyra::TextureBuilderData* result, png_structp pngPtr,
                             png_infop infoPtr, png_bytep* rowPointers) {
  int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
  printf("rowbytes: %d\n", rowBytes);

  result->gsComponents = TEXTURE_COMPONENTS_RGB;
  result->bpp = Tyra::bpp24;

  int originalWidth = result->width;
  int originalHeight = result->height;

  result->data = static_cast<unsigned char*>(memalign(
      128, getTextureSize(result->width, result->height, result->bpp)));

  rowPointers =
      static_cast<png_bytep*>(calloc(result->height, sizeof(png_bytep)));

  for (int row = 0; row < result->height; row++)
    rowPointers[row] = static_cast<png_bytep>(malloc(rowBytes));

  png_read_image(pngPtr, rowPointers);

  struct Tyra::PngPixel3* pixels = (struct Tyra::PngPixel3*)result->data;

  int k = 0;
  for (int i = 0; i < originalHeight; i++) {
    for (int j = 0; j < originalWidth; j++) {
      pixels[k].r = rowPointers[i][2 * j];
      pixels[k].g = pixels[k].r;
      pixels[k].b = pixels[k].r;
      k++;
    }
  }

  for (int row = 0; row < result->height; row++) free(rowPointers[row]);

  free(rowPointers);
}

void PngLoaderUnlimited::handlePalletized(Tyra::TextureBuilderData* result,
                                   png_structp pngPtr, png_infop infoPtr,
                                   png_bytep* rowPointers,
                                   const int& bitDepth) {
  png_colorp palette = nullptr;
  png_bytep trans = nullptr;
  int numPallete = 0;
  int numTrans = 0;

  png_get_PLTE(pngPtr, infoPtr, &palette, &numPallete);
  png_get_tRNS(pngPtr, infoPtr, &trans, &numTrans, nullptr);
  result->clutBpp = Tyra::bpp32;
  result->clutGsComponents = TEXTURE_COMPONENTS_RGBA;

  if (bitDepth == 4) {
    handle4bppPalletized(result, pngPtr, infoPtr, rowPointers, palette,
    trans,
                         numPallete, numTrans);
  } else if (bitDepth == 8) {
    handle8bppPalletized(result, pngPtr, infoPtr, rowPointers, palette,
    trans,
                         numPallete, numTrans);
  } else {
    TYRA_TRAP("Only 4 and 8 bits palettes are supported");
  }
}

void PngLoaderUnlimited::handle8bppPalletized(Tyra::TextureBuilderData* result,
                                       png_structp pngPtr, png_infop infoPtr,
                                       png_bytep* rowPointers,
                                       png_colorp palette, png_bytep trans,
                                       const int& numPallete,
                                       const int& numTrans) {
  int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
  result->bpp = Tyra::bpp8;
  result->clutWidth = 16;
  result->clutHeight = 16;

  int originalWidth = result->width;
  int originalHeight = result->height;

  // if (result->width == 8) {
  //   result->width = 8;
  // } else if (result->width <= 16) {
  //   result->width = 16;
  // } else if (result->width <= 32) {
  //   result->width = 32;
  // } else if (result->width <= 64) {
  //   result->width = 64;
  // } else if (result->width <= 128) {
  //   result->width = 128;
  // } else if (result->width <= 256) {
  //   result->width = 256;
  // } else if (result->width <= 512) {
  //   result->width = 512;
  // }

  // if (result->height == 8) {
  //   result->height = 8;
  // } else if (result->height <= 16) {
  //   result->height = 16;
  // } else if (result->height <= 32) {
  //   result->height = 32;
  // } else if (result->height <= 64) {
  //   result->height = 64;
  // } else if (result->height <= 128) {
  //   result->height = 128;
  // } else if (result->height <= 256) {
  //   result->height = 256;
  // } else if (result->height <= 512) {
  //   result->height = 512;
  // }

  result->gsComponents = TEXTURE_COMPONENTS_RGBA;
  result->data = static_cast<unsigned char*>(memalign(
      128, getTextureSize(result->width, result->height, result->bpp)));

  rowPointers =
      static_cast<png_bytep*>(calloc(result->height, sizeof(png_bytep)));

  for (int row = 0; row < result->height; row++)
    rowPointers[row] = static_cast<png_bytep>(malloc(rowBytes));

  png_read_image(pngPtr, rowPointers);

  result->clut =
      static_cast<unsigned char*>(memalign(128, getTextureSize(16, 16,
      Tyra::bpp32)));
  memset(result->clut, 0, getTextureSize(16, 16, Tyra::bpp32));

  auto* pixel = static_cast<unsigned char*>(result->data);
  struct PngClut* clut = (struct PngClut*)result->clut;

  for (int i = 0; i < numPallete; i++) {
    clut[i].r = palette[i].red;
    clut[i].g = palette[i].green;
    clut[i].b = palette[i].blue;
    clut[i].a = 0x80;
  }

  for (int i = 0; i < numTrans; i++) clut[i].a = trans[i] >> 1;

  // int alpha = -1;
  // for (int i = 0; i < numTrans; i++) {
  //   if (clut[i].a == 0) {
  //     alpha = i;
  //     break;
  //   }
  // }

  // if (alpha == -1 && (result->width - originalWidth != 0 ||
  //                     result->height - originalHeight != 0)) {
  //   TYRA_WARN("Alpha doesn't found in palette, using first color");
  //   alpha = 0;
  // }

  // rotate clut
  for (int i = 0; i < numPallete; i++) {
    // printf("clut pos: %d\n",i);
    if ((i & 0x18) == 8) {
      // printf("rotar\n");
      struct PngClut tmp = clut[i];
      clut[i] = clut[i + 8];
      clut[i + 8] = tmp;
    }
  }

  int k = 0;
  for (int i = 0; i < originalHeight; i++) {
    for (int j = 0; j < originalWidth; j++) {
      memcpy(&pixel[k++], &rowPointers[i][1 * j], 1);
    }
    // for (int j = 0; j < result->width - originalWidth; j++) {
    //   memcpy(&pixel[k++], &alpha, 1);
    // }
  }

  // for (int j = 0; j < result->height - originalHeight; j++) {
  //   for (int j = 0; j < result->width; j++) {
  //     memcpy(&pixel[k++], &alpha, 1);
  //   }
  // }

  for (int row = 0; row < result->height; row++) free(rowPointers[row]);

  free(rowPointers);
}

void PngLoaderUnlimited::handle4bppPalletized(Tyra::TextureBuilderData* result,
                                       png_structp pngPtr, png_infop infoPtr,
                                       png_bytep* rowPointers,
                                       png_colorp palette, png_bytep trans,
                                       const int& numPallete,
                                       const int& numTrans) {
  int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
  result->bpp = Tyra::bpp4;
  result->clutWidth = 8;
  result->clutHeight = 2;
  result->gsComponents = TEXTURE_COMPONENTS_RGBA;
  result->data = static_cast<unsigned char*>(memalign(
      128, getTextureSize(result->width, result->height, result->bpp)));

  rowPointers =
      static_cast<png_bytep*>(calloc(result->height, sizeof(png_bytep)));

  for (int row = 0; row < result->height; row++)
    rowPointers[row] = static_cast<png_bytep>(malloc(rowBytes));

  png_read_image(pngPtr, rowPointers);

  result->clut =
      static_cast<unsigned char*>(memalign(128, getTextureSize(8, 2,
      Tyra::bpp32)));
  memset(result->clut, 0, getTextureSize(8, 2, Tyra::bpp32));

  auto* pixel = static_cast<unsigned char*>(result->data);
  struct PngClut* clut = (struct PngClut*)result->clut;

  for (int i = 0; i < numPallete; i++) {
    clut[i].r = palette[i].red;
    clut[i].g = palette[i].green;
    clut[i].b = palette[i].blue;
    clut[i].a = 0x80;
  }

  for (int i = 0; i < numTrans; i++) clut[i].a = trans[i] >> 1;

  int k = 0;
  for (int i = 0; i < result->height; i++) {
    for (int j = 0; j < result->width / 2; j++)
      memcpy(&pixel[k++], &rowPointers[i][1 * j], 1);
  }
  unsigned char* tmpdst = (unsigned char*)result->data;
  unsigned char* tmpsrc = (unsigned char*)pixel;

  for (u32 byte = 0;
       byte < getTextureSize(result->width, result->height, result->bpp);
       byte++)
    tmpdst[byte] = (tmpsrc[byte] << 4) | (tmpsrc[byte] >> 4);

  for (int row = 0; row < result->height; row++) free(rowPointers[row]);

  free(rowPointers);
}

void Shader_SetAlphaToImage(const int textureAlphaID, const int textureImageID){
  Tyra::Texture* alpha = renderer->getTextureRepository().getByTextureId(textureAlphaID);
  Tyra::Texture* image = renderer->getTextureRepository().getByTextureId(textureImageID);
  
  TYRA_ASSERT(alpha!=nullptr,"Alpha Texture is NUll");
  TYRA_ASSERT(image!=nullptr,"Image Texture is NUll");
  
  image->core->components = TEXTURE_COMPONENTS_RGBA;

  Tyra::PngPixel4* clutData = (Tyra::PngPixel4*)alpha->clut->data;
  unsigned char* pixelData = alpha->core->data;

  unsigned char* clutDataNormal= RotateClut(clutData);
  Tyra::PngPixel4* newClutData = (Tyra::PngPixel4*)clutDataNormal;

  struct Tyra::PngPixel3* backData =
      (struct Tyra::PngPixel3*)image->core->data;
  SetAlphaFrom8BppToJPG(backData,newClutData,pixelData,image->core->width,image->core->height);

  free(clutDataNormal);
}