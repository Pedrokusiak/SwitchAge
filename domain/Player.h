#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ObjectGame.h"
#include "ports/EventPort.h"
#include "MixerManager.h" // Inclua o MixerManager

class Player : public ObjectGame {
public:
    Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hiberate, ITexture* texture, GameAudio::MixerManager* mixerManager);
    virtual ~Player() override = default; // Destruidor virtual
    void handleEvent(EventPort* event);
    void render(RendererPort* renderer) const override;
    void update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) override;

private:
    GameAudio::MixerManager* mixerManager; // Adiciona um ponteiro para o MixerManager
};

#endif // PLAYER_HPP
