#include <imageTools.hpp>
#include <cstdio>
#include <malloc.h>
#include <jpeglib.h>
#include <cstring>
#include <draw_buffers.h>
#include "loaders/texture/jpg_loader.hpp"
#include "file/file_utils.hpp"
#include <csetjmp>
#include <cmath>

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
Tyra::TextureBuilderData* JPGLoaderUnlimited::load(const char* fullPath) {
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

  auto* result = new Tyra::TextureBuilderData();
  result->width = cinfo.output_width;
  result->height = cinfo.output_height;
  result->name = filename;
  result->gsComponents = TEXTURE_COMPONENTS_RGB;

  int textureSize;
  printf("width, height: %d,%d\n",cinfo.output_width, cinfo.output_height);

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

    unsigned char* newArray = static_cast<unsigned char*>(
        memalign(128, getTextureSize(result->width, result->height, Tyra::bpp24)));
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

  return result;
}
