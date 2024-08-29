// Arquivo SDLTexturePort.h
#pragma once
#include "TexturePort.h"
#include <SDL2/SDL_image.h>
#include <unordered_map>

class SDLTexturePort : public TexturePort {
private:
    SDL_Renderer* renderer;
    std::unordered_map<int, SDLTexture*> textures;

public:
    SDLTexturePort(SDL_Renderer* renderer) : renderer(renderer) {}
    ~SDLTexturePort() {
        for (auto& pair : textures) {
            delete pair.second;
        }
    }

    ITexture* loadTexture(const std::string& filePath) override {
        SDL_Texture* sdlTexture = IMG_LoadTexture(renderer, filePath.c_str());
        if (!sdlTexture) return nullptr;
        SDLTexture* texture = new SDLTexture(renderer, sdlTexture);
        textures.insert(std::make_pair(textures.size(), texture));
        return texture;
    }

    ITexture* getTexture(int textureId) {
        auto it = textures.find(textureId);
        return it != textures.end() ? it->second : nullptr;
    }
};
