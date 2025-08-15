#pragma once

#include <loaders/texture/base/texture_loader.hpp>
#include <renderer/core/texture/models/texture.hpp>
#include <tyra>

#ifdef INTELLISENSE
#else
#include <jpeglib.h>
#endif

enum TextureScale {
  Tex32 = 32,
  Tex64 = 64,
  Tex128 = 128,
  Tex256 = 256,
  tex512 = 512
};

struct BigTexture {
  std::vector<Tyra::TextureBuilderData*> data;
  int width;
  int height;
};

class JpgImageScale {
 public:
  static BigTexture load(const char* fullpath, const TextureScale sWidth,
                           const TextureScale sHeight);
  static BigTexture load(Tyra::Texture* texture, const TextureScale sWidth,
                           const TextureScale sHeight,
                           const int TextureComponent);
};

class PngLoaderUnlimited {
  public:
  Tyra::TextureBuilderData* load(const char* fullPath);
   void handle32bpp(Tyra::TextureBuilderData* result, png_structp pngPtr,
                    png_infop infoPtr, png_bytep* rowPointers);
   void handle24bpp(Tyra::TextureBuilderData* result, png_structp pngPtr,
                    png_infop infoPtr, png_bytep* rowPointers);
   void handleGrayAlpha(Tyra::TextureBuilderData* result, png_structp pngPtr,
                        png_infop infoPtr, png_bytep* rowPointers);
   void handleGray(Tyra::TextureBuilderData* result, png_structp pngPtr,
                   png_infop infoPtr, png_bytep* rowPointers);
 
   void handlePalletized(Tyra::TextureBuilderData* result, png_structp pngPtr,
                         png_infop infoPtr, png_bytep* rowPointers,
                         const int& bitDepth);
 
   void handle8bppPalletized(Tyra::TextureBuilderData* result, png_structp pngPtr,
                             png_infop infoPtr, png_bytep* rowPointers,
                             png_colorp palette, png_bytep trans,
                             const int& numPallete, const int& numTrans);
 
   void handle4bppPalletized(Tyra::TextureBuilderData* result, png_structp pngPtr,
                             png_infop infoPtr, png_bytep* rowPointers,
                             png_colorp palette, png_bytep trans,
                             const int& numPallete, const int& numTrans);
 };

class PNGImageScale {
 public:
  static BigTexture load(Tyra::Texture* texture, const TextureScale sWidth,
                           const TextureScale sHeight, const int TextureComponent);
  static BigTexture loadOne(Tyra::Texture* texture, const TextureScale sWidth,
                           const TextureScale sHeight, const int TextureComponent);
};

class JPGLoaderUnlimited {
  public:
  static Tyra::TextureBuilderData* load(const char* fullPath);
};

int getTextureSize(const unsigned int& width, const unsigned int& height,
                   const Tyra::TextureBpp& bpp);
unsigned char* RotateClut(Tyra::PngPixel4* data);
void SetAlphaFrom8BppToJPG(Tyra::PngPixel3* jpgData, Tyra::PngPixel4* clutData,
                           unsigned char* clutPos, int width, int height);
void Shader_SetAlphaToImage(const int textureAlphaID, const int textureImageID);
