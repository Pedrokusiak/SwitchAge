#ifndef ITEXTURE_H
#define ITEXTURE_H

class ITexture {
public:
    virtual ~ITexture() {}

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual void bind() const = 0;
    virtual int getId() const = 0;  // Adicione este método para obter o ID da textura
};
#endif // ITEXTURE_H