#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ObjectGame.h"
#include "ports/EventPort.h"
#include "Camera.h"
#include "MixerManager.h"

class Player : public ObjectGame
{
public:
    Player(Vector2D pos, Vector2D size, Vector2D gravity, float mass, bool hibernate,
           std::shared_ptr<ITexture> texture, RendererPort *renderer, int frameWidth, int frameHeight, GameAudio::MixerManager *mixerManager);
    virtual ~Player() override = default; // Destruidor virtual
    void handleEvent(EventPort *event);
    void render(RendererPort *renderer, const Camera &camera) const override;
    void update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>> &gameObjects) override; // Adicione esta linha
    void addAnimation(const std::string &name, const std::vector<int> &frameIndices);
    void playAnimation(const std::string &name, bool loop = true);

    void flipGravity()
    {
        Vector2D currentGravity = physicsComponent.getGravity();
        Vector2D newGravity = Vector2D(0, currentGravity.y > 0 ? -GRAVITY_MAGNITUDE : GRAVITY_MAGNITUDE);
        physicsComponent.setGravity(newGravity);
        physicsComponent.applyForce(newGravity * 0.5f);
        isUpsideDown = !isUpsideDown;

        if (!animation->isPlayingAnimation("jumpUp"))
        {
            animation->playAnimation("jumpUp", false);
        }
    }

private:
    GameAudio::MixerManager *mixerManager; // Adiciona um ponteiro para o MixerManager
    float lastGravityFlip;
    Vector2D calculateCollisionNormal(const ObjectGame &other) const;
    void handleGroundedState(const Vector2D &normal);
    bool isUpsideDown;
};

#endif // PLAYER_HPP