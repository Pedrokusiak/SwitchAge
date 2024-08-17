// Arquivo SDLTexture.h
#pragma once
#include <SDL2/SDL.h>

class SDLTexture {
private:
    SDL_Texture* texture; // Ponteiro para a textura SDL
public:
    // Construtor que assume a propriedade do ponteiro SDL_Texture*
    explicit SDLTexture(SDL_Texture* texture) : texture(texture) {}

    // Destruidor que libera a textura SDL
    ~SDLTexture() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

    // Métodos de acesso para a textura SDL
    SDL_Texture* getSDLTexture() const {
        return texture;
    }

    // Proibir cópia e atribuição para evitar problemas com gerenciamento de recursos
    SDLTexture(const SDLTexture&) = delete;
    SDLTexture& operator=(const SDLTexture&) = delete;

    // Permitir mover
    SDLTexture(SDLTexture&& other) noexcept : texture(other.texture) {
        other.texture = nullptr;
    }

    SDLTexture& operator=(SDLTexture&& other) noexcept {
        if (this != &other) {
            SDL_DestroyTexture(texture);  // Destruir a textura existente
            texture = other.texture;      // Transferir a propriedade
            other.texture = nullptr;      // Impedir que a textura original seja destruída
        }
        return *this;
    }
};
