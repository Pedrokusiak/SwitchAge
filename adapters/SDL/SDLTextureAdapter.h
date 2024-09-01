#include "TexturePort.h"
#include "SDLTexture.h"
#include <unordered_map>
#include <iostream>

class SDLTextureAdapter : public TexturePort {
private:
    std::unordered_map<int, ITexture*> textures;
    SDL_Renderer* renderer;
    int nextId = 0;  // Contador de ID

public:
    SDLTextureAdapter(SDL_Renderer* renderer) : renderer(renderer) {}
    virtual ~SDLTextureAdapter() {
        for (auto& pair : textures) {
            delete pair.second;
        }
    }

    ITexture* loadTexture(const std::string& filePath) override {
        SDL_Surface* surface = IMG_Load(filePath.c_str());
        if (!surface) {
            std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
        
            return nullptr;
        }
        SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!sdlTexture) {
            std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        int id = ++nextId;  // Incrementa o ID para cada nova textura
        ITexture* texture = new SDLTexture(sdlTexture, id);
        textures[id] = texture;
        return texture;
    }

    ITexture* getTexture(int textureId) override {
        auto it = textures.find(textureId);
        if (it != textures.end()) {
            return it->second;
        } else {
            std::cerr << "Texture ID not found: " << textureId << std::endl;
            return nullptr;
        }
    }
};
