#include "ports/ITexture.h"

class TextureManager {
public:
    static ITexture* getTexture(const std::string& name);
    static void loadTexture(const std::string& name, const std::string& path);
private:
    // static std::unordered_map<std::string, std::shared_ptr<ITexture>> textures;
};
