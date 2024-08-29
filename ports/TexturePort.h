// Arquivo ITexturePort.h
#pragma once
#include "ITexture.h"
#include <string>

class TexturePort {
public:
    virtual ~TexturePort() {}
    virtual ITexture* loadTexture(const std::string& filePath) = 0;
    virtual ITexture* getTexture(int textureId) = 0;
};
