#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "GroundSegment.h"
#include "Physics.h"
#include "ports/RendererPort.h"
#include "ports/EventPort.h"
#include "ports/TexturePort.h"
#include "ports/PlayerRenderPort.h"
#include <vector>
#include <memory>
#include "MixerManager.h" // Inclui o MixerManager

class Game {
public:
    Game(RendererPort *renderer, EventPort *eventPort, TexturePort *texturePort);
    void run();
    void processEvents(bool running);
    void updateGameObjects(float deltaTime);
    void renderGameObjects();
    void controlFrameRate(Uint32 frameStart, float frameDelay);

private:
    RendererPort *renderer;
    EventPort *eventPort;
    TexturePort *texturePort;
    std::vector<std::unique_ptr<ObjectGame>> gameObjects;

    // Adicionando MixerManager da GameAudio
    GameAudio::MixerManager mixerManager; // Usando o namespace correto para evitar conflitos
};

#endif // GAME_H
