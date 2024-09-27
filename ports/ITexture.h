#ifndef ITEXTURE_H
#define ITEXTURE_H

#include "ports/RendererPort.h"  
#include <vector> // Inclua RendererPort antes de declarar ITexture

class ITexture {
public:
    virtual ~ITexture() {}

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual void bind() const = 0;
    virtual void setSourceRect(int x, int y, int w, int h) = 0;
    virtual void render(RendererPort* renderer, int x, int y) = 0;
    virtual int getId() const = 0;  // Adicione este método para obter o ID da textura
};
#endif // ITEXTURE_H