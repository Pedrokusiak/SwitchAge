// Arquivo SDLTexture.h
#pragma once
#include "ITexture.h"
#include <SDL2/SDL.h>

class SDLTexture : public ITexture {
private:
    SDL_Texture* texture; // Ponteiro para a textura SDL
    SDL_Renderer* renderer; // Ponteiro para o renderer SDL

public:
    SDLTexture(SDL_Renderer* renderer, SDL_Texture* texture)
        : renderer(renderer), texture(texture) {}

    ~SDLTexture() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

    void render(int x, int y, void* clip = nullptr) {
        SDL_Rect dstRect = { x, y, 0, 0 };
        SDL_Rect* clipRect = static_cast<SDL_Rect*>(clip);

        if (clipRect) {
            dstRect.w = clipRect->w;
            dstRect.h = clipRect->h;
        } else {
            SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);
        }

        SDL_RenderCopy(renderer, texture, clipRect, &dstRect);
    }

    // Proibir cópia e atribuição para evitar problemas com gerenciamento de recursos
    SDLTexture(const SDLTexture&) = delete;
    SDLTexture& operator=(const SDLTexture&) = delete;

    // Permitir mover
    SDLTexture(SDLTexture&& other) noexcept : renderer(other.renderer), texture(other.texture) {
        other.texture = nullptr; // Garante que a textura não seja destruída pelo destruidor do objeto movido
    }

    SDLTexture& operator=(SDLTexture&& other) noexcept {
        if (this != &other) {
            SDL_DestroyTexture(texture);  // Destruir a textura existente
            texture = other.texture;      // Transferir a propriedade
            renderer = other.renderer;    // Transferir o renderer
            other.texture = nullptr;      // Impedir que a textura original seja destruída
        }
        return *this;
    }
};
