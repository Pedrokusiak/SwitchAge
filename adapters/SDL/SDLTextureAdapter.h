#include <SDL2/SDL.h>
#include <ports/EventPort.h>

class SDLTextureManager : public TexturePort {
private:
    SDL_Renderer* renderer;
    std::unordered_map<int, SDLTexture*> textures;
    int nextId = 0;

public:
    SDLTextureManager(SDL_Renderer* renderer) : renderer(renderer) {}

    TexturePort* loadTexture(const std::string& filePath) override {
        SDL_Texture* sdlTexture = IMG_LoadTexture(renderer, filePath.c_str());
        SDLTexture* texture = new SDLTexture(sdlTexture);
        textures[nextId] = texture;
        return texture;
    }

    TexturePort* getTexture(int textureId) override {
        return textures[textureId];
    }
};