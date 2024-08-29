#pragma once

class ITexture {
public:
    virtual ~ITexture() {}

    // Métodos virtuais puros que devem ser implementados pelas classes concretas
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual void bind() const = 0;  // Método para "bindar" a textura
};
