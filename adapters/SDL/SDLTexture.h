#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ITexture.h"
#include "TexturePort.h"
#include <string>
#include <memory>
#include <map>

class SDLTexture : public ITexture, public TexturePort {
public:
    SDLTexture(SDL_Renderer* renderer);
    ~SDLTexture() override;

    // Métodos de ITexture
    int getWidth() const override;
    int getHeight() const override;
    void bind() const override;
    void setSourceRect(int x, int y, int w, int h) override;
    void render(RendererPort* renderer, int x, int y) override;
    int getId() const override;
    std::shared_ptr<ITexture> __loadTexture_thunk(const std::string& filePath);
    std::shared_ptr<ITexture> __getTexture_thunk(const std::string& filePath);
    void __unloadTexture_thunk(const std::string& filePath);
    void __unloadAllTextures_thunk();

    // Métodos de TexturePort
    std::shared_ptr<ITexture> loadTexture(const std::string& filePath) override;
    std::shared_ptr<ITexture> getTexture(const std::string& filePath) override;
    void unloadTexture(const std::string& filePath) override;
    void unloadAllTextures() override;

    SDL_Texture* getInternalTexture() const { return texture; }

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect sourceRect;
    int textureId;
    static int nextTextureId;
    std::map<std::string, std::shared_ptr<ITexture>> textureCache;
};

#endif // SDLTEXTURE_H