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
    void updateAnimationBasedOnState();

      void flipGravity() {
        Vector2D currentGravity = physicsComponent.getGravity();
        Vector2D newGravity = Vector2D(0, currentGravity.y > 0 ? -GRAVITY_MAGNITUDE : GRAVITY_MAGNITUDE);
        physicsComponent.setGravity(newGravity);
        physicsComponent.applyForce(newGravity * 0.5f);
        isUpsideDown = !isUpsideDown;
        
        updateAnimationBasedOnState();

        if (mixerManager) {
            mixerManager->playSound("jump");
        }
    }



private:
    GameAudio::MixerManager *mixerManager; // Adiciona um ponteiro para o MixerManager
    float lastGravityFlip;
    Vector2D calculateCollisionNormal(const ObjectGame &other) const;
    void handleGroundedState(const Vector2D &normal);
    std::string getCurrentStateSuffix() const { return isUpsideDown ? "Inverted" : ""; }
    bool isUpsideDown;

    const float PLAYER_FORCE = 1000.0f;
    const float PLAYER_MOVEMENT_FORCE = 800.0f;
    const float GRAVITY_MAGNITUDE = 1000.0f;
    const float GRAVITY_FLIP_COOLDOWN = 0.5f;
};

#endif // PLAYER_HPP