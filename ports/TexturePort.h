class TexturePort {
public:
    virtual ~TexturePort() {}
    virtual ITexture* loadTexture(const std::string& filePath) = 0; // Retorna uma interface para a textura
    virtual ITexture* getTexture(int textureId) = 0; // Recupera a interface de textura pelo ID
};