#include "SDLTexture.h"
#include "SDLRendererAdapter.h"
#include <iostream>

int SDLTexture::nextTextureId = 0;

SDLTexture::SDLTexture(SDL_Renderer* renderer) 
    : renderer(renderer), texture(nullptr), textureId(nextTextureId++) {
    sourceRect = {0, 0, 0, 0};
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    }
}

SDLTexture::~SDLTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    IMG_Quit();
}

int SDLTexture::getWidth() const {
    int w;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, nullptr);
    return w;
}

int SDLTexture::getHeight() const {
    int h;
    SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &h);
    return h;
}

void SDLTexture::bind() const {
    // SDL não tem um conceito direto de "bind", então este método pode ficar vazio
    // ou você pode implementar alguma lógica específica se necessário
}

void SDLTexture::setSourceRect(int x, int y, int w, int h) {
    sourceRect = {x, y, w, h};
}

void SDLTexture::render(RendererPort* renderer, int x, int y) {
    SDL_Rect destRect = {x, y, sourceRect.w, sourceRect.h};
    if (sourceRect.w == 0 || sourceRect.h == 0) {
        SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
    }
    SDL_RenderCopy(static_cast<SDLRendererAdapter*>(renderer)->getRenderer(), texture, &sourceRect, &destRect);
}

int SDLTexture::getId() const {
    return textureId;
}

std::shared_ptr<ITexture> SDLTexture::loadTexture(const std::string& filePath) {
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        return it->second;
    }

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Unable to load image " << filePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!newTexture) {
        std::cerr << "Unable to create texture from " << filePath << "! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    auto texture = std::make_shared<SDLTexture>(renderer);
    texture->texture = newTexture;
    textureCache[filePath] = texture;

    return texture;
}

std::shared_ptr<ITexture> SDLTexture::getTexture(const std::string& filePath) {
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        return it->second;
    }
    return nullptr;
}

void SDLTexture::unloadTexture(const std::string& filePath) {
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        textureCache.erase(it);
    }
}

void SDLTexture::unloadAllTextures() {
    textureCache.clear();
}

// Implementações dos métodos de thunk
// Estes são necessários devido à herança múltipla

std::shared_ptr<ITexture> SDLTexture::__loadTexture_thunk(const std::string& filePath) {
    return loadTexture(filePath);
}

std::shared_ptr<ITexture> SDLTexture::__getTexture_thunk(const std::string& filePath) {
    return getTexture(filePath);
}

void SDLTexture::__unloadTexture_thunk(const std::string& filePath) {
    unloadTexture(filePath);
}

void SDLTexture::__unloadAllTextures_thunk() {
    unloadAllTextures();
}