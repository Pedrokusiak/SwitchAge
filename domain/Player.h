#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ObjectGame.h"
#include "ports/EventPort.h"

class Player : public ObjectGame {
public:
    Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hibernate, 
           std::shared_ptr<ITexture> texture, RendererPort* renderer, int frameWidth, int frameHeight);
    virtual ~Player() override = default; // Destruidor virtual
    void handleEvent(EventPort* event);
    void render(RendererPort* renderer) const override;
    void update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) override; // Adicione esta linha
    void addAnimation(const std::string& name, const std::vector<int>& frameIndices);
    void playAnimation(const std::string& name, bool loop = true);
};

#endif // PLAYER_HPP
