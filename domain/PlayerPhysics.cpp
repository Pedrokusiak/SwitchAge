#include "PlayerPhysics.h"
#include "GroundSegment.h"

PlayerPhysics::PlayerPhysics(float gravity, float maxFallSpeed, float jumpForce)
    : gravity(gravity), maxFallSpeed(maxFallSpeed), jumpForce(jumpForce) {}

void PlayerPhysics::applyPhysics(Vector2D& position, Vector2D& velocity, bool& onGround, const Vector2D& size, const std::vector<GroundSegment>& groundSegments) {
    velocity.y += gravity;
    if (velocity.y > maxFallSpeed) {
        velocity.y = maxFallSpeed;
    }
    position += velocity;
    onGround = false;
    for (const auto& segment : groundSegments) {
        if (position.y + size.y > segment.getPosition().y &&
            position.x < segment.getPosition().x + segment.getWidth() &&
            position.x + size.x > segment.getPosition().x) {
            position.y = segment.getPosition().y - size.y;
            velocity.y = 0;
            onGround = true;
            break;
        }
    }
}
