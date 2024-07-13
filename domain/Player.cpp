#include "Player.h"
#include <iostream> // Para depuração

const float PLAYER_ACC = 1000.0f;
const float PLAYER_JUMP_FORCE = 15.0f;

Player::Player(Vector2D pos, Vector2D size, Physics* physicsComponent)
    : ObjectGame(pos, size, physicsComponent), velocity(0, 0), onGround(false) {}

void Player::handleEvent(EventPort* event) {
    if (event->isKeyDownEvent()) {
        switch (event->getKey()) {
            case SDLK_LEFT: physicsComponent->applyForce(Vector2D(-PLAYER_ACC, 0)); break;
            case SDLK_RIGHT: physicsComponent->applyForce(Vector2D(PLAYER_ACC, 0)); break;
            case SDLK_UP:
                if (onGround) {
                    physicsComponent->applyForce(Vector2D(0, -PLAYER_JUMP_FORCE));
                    onGround = false;
                }
                break;
        }
    }
}

void Player::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    // Aplicar a gravidade
    physicsComponent->applyForce(physicsComponent->getVelocity() * physicsComponent->getVelocity().y);
    
    // Atualizar a física
    physicsComponent->update(deltaTime);
    Vector2D newVelocity = physicsComponent->getVelocity();

    // Atualizar a posição do jogador
    position += newVelocity * deltaTime;

    // Verificar colisões e resolver
    onGround = false;
    for (const auto& object : gameObjects) {
        if (this != object.get() && checkCollision(*object)) {
            if (newVelocity.y > 0 && object->getPosition().y > position.y) {
                onGround = true;
            }
        }
    }

    // Atualizar a hitbox
    hitbox.update(position);

    // Imprimir informações de depuração
    std::cout << "Player Position: (" << position.x << ", " << position.y << ")" << std::endl;
    std::cout << "Player Velocity: (" << newVelocity.x << ", " << newVelocity.y << ")" << std::endl;
}

void Player::render(RendererPort* renderer) const {
    renderer->drawPlayer(position.x, position.y, size.x, size.y, 0xFF, 0x00, 0x00, 0xFF);
}
