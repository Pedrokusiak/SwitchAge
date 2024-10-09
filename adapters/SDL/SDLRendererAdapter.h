
#ifndef SDLRENDERERADAPTER_H
#define SDLRENDERERADAPTER_H
#include <SDL2/SDL.h>
#include "ports/RendererPort.h"
#include "ITexture.h"
#include <memory>
#include "SDLTexture.h" 

class SDLRendererAdapter : public RendererPort {
public:
    SDLRendererAdapter();
    ~SDLRendererAdapter();
    void draw() const;
    void drawPlayer(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) override;
    void drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) override;
    virtual void drawTexture(const std::shared_ptr<ITexture>& texture, int x, int y, int width, int height) override;
    void drawTexturePart(const std::shared_ptr<ITexture>& texture, 
                                 int destX, int destY, int destW, int destH, 
                                 int srcX, int srcY, int srcW, int srcH) override; 
    void present() const override;
    
    void quit() const override;

    void delay(Uint32 ms) const override;
    // void drawText(const std::string& text, int x, int y, SDL_Color color, TTF_Font* font) override;

    Uint32 getTicks() const override;
    SDL_Renderer *getRenderer() const;



private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
