#include "ObjectGame.h"
#include <tuple>
#include <set>
#include <vector>
#include <iostream>
#include <memory>

ObjectGame::ObjectGame(Vector2D position, Vector2D size, Vector2D gravity, float mass, bool hiberate)
    : VisualElement(position), size(size), physicsComponent(gravity, mass), hitbox(position, size) {}

void ObjectGame::update(float deltaTime, const std::vector<std::unique_ptr<ObjectGame>>& gameObjects) {
    applyPhysics(deltaTime);
    if(!hibernate){
        hitbox.update(position);
    }
    std::set<std::tuple<int, int>> checkedPairs;
    for (size_t i = 0; i < gameObjects.size(); ++i) {
        for (size_t j = i + 1; j < gameObjects.size(); ++j) {
            auto pair = std::make_tuple(i, j);

            if (checkedPairs.find(pair) == checkedPairs.end()) {
                checkedPairs.insert(pair);

                if (gameObjects[i]->checkCollision(*gameObjects[j])) {
                    gameObjects[i]->resolveCollision(*gameObjects[j]);
                }
            }
        }
    }
}

void ObjectGame::applyPhysics(float deltaTime) {
    if(!hibernate){
        physicsComponent.update(deltaTime);
        if(physicsComponent.getVelocity().y == 0){
            position = position;
        }

        position += physicsComponent.getVelocity() * deltaTime;
    }
  
}

bool ObjectGame::checkCollision(const ObjectGame& other) const {
    return hitbox.intersects(other.getHitbox());
}

void ObjectGame::resolveCollision(ObjectGame& other) {
    Vector2D overlap = hitbox.getOverlap(other.getHitbox());
    if (overlap.x == 0 && overlap.y == 0) return; // Nenhuma sobreposição real

    // Se algum dos objetos estiver em hibernação, a resposta à colisão pode ser ajustada.
    if (this->hibernate || other.hibernate) {
        // Aplica lógica específica para objetos em hibernação
        handleHibernateCollision(other, overlap);
        return;
    }

    // Determina a direção principal da colisão
    bool isHorizontal = overlap.x < overlap.y;

    // Ajusta as posições para resolver a sobreposição
    if (isHorizontal) {
        float correction = overlap.x / 2;
        if (position.x < other.position.x) {
            position.x -= correction;
            other.position.x += correction + 5;
        } else {
            position.x += correction - 10;
            other.position.x -= correction - 10;
        }
    } else {
        float correction = overlap.y / 2;
        if (position.y < other.position.y) {
            position.y -= correction;
            other.position.y += correction;
        } else {
            position.y += correction;
            other.position.y -= correction;
        }
    }

    // Resolvendo a velocidade para simular um impulso em resposta à colisão
    if (!getHibernate() && !other.getHibernate()) {
        if (isHorizontal) {
            // Inverter velocidades horizontais
            float tempVelocityX = physicsComponent.getVelocity().x;
            physicsComponent.setVelocity(Vector2D(other.physicsComponent.getVelocity().x, physicsComponent.getVelocity().y));
            other.physicsComponent.setVelocity(Vector2D(tempVelocityX, other.physicsComponent.getVelocity().y));
        } else {
            // Inverter velocidades verticais
            float tempVelocityY = physicsComponent.getVelocity().y;
            physicsComponent.setVelocity(Vector2D(physicsComponent.getVelocity().x, other.physicsComponent.getVelocity().y));
            other.physicsComponent.setVelocity(Vector2D(other.physicsComponent.getVelocity().x, tempVelocityY));
        }
    }
}

void ObjectGame::handleHibernateCollision(ObjectGame& other, const Vector2D& overlap) {
    // Implementar lógica específica para colisões envolvendo objetos hibernados
    // Exemplo: Evitar alterar a posição ou velocidade do objeto hibernado
    if (this->hibernate && !other.hibernate) {
        other.adjustForCollision(other,overlap);
    } else if (!this->hibernate && other.hibernate) {
        this->adjustForCollision(other,overlap);
    }
}

void ObjectGame::adjustForCollision(ObjectGame& other,const Vector2D& overlap) {

    bool isHorizontal = overlap.x < overlap.y;

    // Ajusta as posições para resolver a sobreposição
    if (isHorizontal) {
        if (position.x < other.getPosition().x) {
            position.x -= overlap.x; // Empurra para a esquerda
        } else {
            position.x += overlap.x; // Empurra para a direita
        }
        physicsComponent.setGravity(Vector2D(0,0));
        physicsComponent.setVelocity(Vector2D(0, physicsComponent.getVelocity().y)); // Anula a velocidade horizontal para evitar que continue movendo-se para dentro do objeto
    } else {
        if (position.y < other.getPosition().y) {
            position.y -= overlap.y; // Empurra para cima
        } 
        physicsComponent.setVelocity(Vector2D(0, 0));
        physicsComponent.setGravity(Vector2D(0,0)); // Anula a velocidade vertical para evitar que continue movendo-se para dentro do objeto
    }
}

