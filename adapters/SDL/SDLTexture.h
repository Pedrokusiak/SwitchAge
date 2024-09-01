#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SDLTexture : public ITexture {
private:
    SDL_Texture* texture;
    int width, height, id;  // Adicionando ID

public:
    SDLTexture(SDL_Texture* texture, int id) : texture(texture), id(id) {
        SDL_QueryTexture(texture, NULL, NULL, &this->width, &this->height);
    }

    ~SDLTexture() override {
        SDL_DestroyTexture(texture);
    }

    int getWidth() const override { return width; }
    int getHeight() const override { return height; }
    void bind() const override {}  
    int getId() const override { return id; }  
    SDL_Texture* getInternalTexture() const {
        return texture;
    }
};
