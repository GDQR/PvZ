#include "components.hpp"
#include "renderSprite/textures.hpp"
#include "entities/plants.hpp"

using Tyra::FileUtils;

Tyra::Texture* projectilePea;

void loadSprite(Sprite* sprite) {
  sprite->mode = Tyra::MODE_STRETCH;
  sprite->position = Tyra::Vec2(0, 0);
  sprite->size = Tyra::Vec2(64, 64);
}

void loadSprite(Sprite* sprite, Vec2 size) {
  sprite->mode = Tyra::MODE_STRETCH;
  sprite->position = Tyra::Vec2(0, 0);
  sprite->size = size;
}

void loadSprite(Sprite* sprite, Tyra::SpriteMode mode, Vec2 position,
                Vec2 size) {
  sprite->mode = mode;
  sprite->position = position;
  sprite->size = size;
}

int createTexture(int id, std::string fileImage) {
  TYRA_ASSERT(!(spriteArray.find(id) == spriteArray.end()), "Entitie id: ", id,
              "Is NULL, use <<CreateSprite>> function");
  std::string findTexture = FileUtils::getFilenameFromPath(fileImage);

  for (u32 i = 0; i < texRepo->getTexturesCount(); i++) {
    if ((*texRepo->getAll())[i]->name == findTexture) {
      (*texRepo->getAll())[i]->addLink(spriteArray[id].id);
      return 1;
    }
  }
  Tyra::Texture* texture = loadTexture(fileImage);
  texture->addLink(spriteArray[id].id);
  return 0;
}

void createTextureRotate(int id, std::string fileImage) {
  Tyra::Texture* texture = loadTexture(fileImage);
  TYRA_ASSERT(!(rotationSprite.find(id) == rotationSprite.end()),
              "Entitie id: ", id, "Is NULL, use <<CreateSprite>> function");
  texture->addLink(rotationSprite[id].sprite.id);
}

void loadTexture(Sprite* sprite, std::string fileImage) {
  /**
   * TextureRepository is a repository of textures.
   * It is a singleton class, with all game textures.
   * We are linking these textures with sprite's (2D) and mesh (3D) materials.
   */
  auto& textureRepository = renderer->getTextureRepository();

  /**
   * Texture is stored in "res" directory.
   * Content of "res" directory is automatically copied into
   * "bin" directory, which contains our final game.
   *
   * File utils automatically add's device prefix to the path,
   * based on current working directory.
   *
   * In PS2 world:
   * - USB has a "mass:" prefix
   * - Our PC in PS2Link has a "host:" prefix
   * - Our PC in PCSX2 has a "host:" prefix
   */
  auto filepath = FileUtils::fromCwd(fileImage);

  /**
   * Tyra supports following PNG formats:
   * 32bpp (RGBA)
   * 24bpp (RGB)
   * 8bpp, palletized (RGBA)
   * 4bpp, palletized (RGBA)
   *
   * 8bpp and 4bpp are the fastest.
   * All of these formats can be easily exported via GIMP.
   */
  auto* texture = textureRepository.add(filepath);

  /** Let's assign this texture to sprite. */
  texture->addLink(sprite->id);

  TYRA_LOG("Texture loaded!");
}

void loadTexture(int spriteID, std::string fileImage) {
  auto& textureRepository = renderer->getTextureRepository();

  auto filepath = FileUtils::fromCwd(fileImage);

  auto* texture = textureRepository.add(filepath);

  texture->addLink(spriteArray[spriteID].id);

  TYRA_LOG("Texture loaded!");
}

Tyra::Texture* loadTexture(std::string fileImage) {
  auto& textureRepository = renderer->getTextureRepository();

  auto filepath = FileUtils::fromCwd(fileImage);

  Tyra::Texture* texture = textureRepository.add(filepath);

  return texture;
}

void copyTexture(Sprite* sprite1, Sprite* sprite2) {
  auto& textureRepository = renderer->getTextureRepository();

  auto* texture = textureRepository.getBySpriteId(sprite1->id);

  /** Let's assign this texture to sprite. */
  texture->addLink(sprite2->id);

  TYRA_LOG("Texture loaded!");
}

void loadProjectile() {
  projectilePea = loadTexture("particles/ProjectilePea.png");
}