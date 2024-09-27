#ifndef TEXTURE_PORT_H
#define TEXTURE_PORT_H

#include "ITexture.h"
#include <string>
#include <unordered_map>
#include <memory>

class RendererPort;

class TexturePort {
public:
    virtual ~TexturePort() = default;
    virtual std::shared_ptr<ITexture> loadTexture(const std::string& filePath) = 0;
    virtual std::shared_ptr<ITexture> getTexture(const std::string& filePath) = 0;
    virtual void unloadTexture(const std::string& filePath) = 0;
    virtual void unloadAllTextures() = 0;
};

#endif