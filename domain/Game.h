#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "GroundSegment.h"
#include "Physics.h"
#include "ports/RendererPort.h"
#include "ports/EventPort.h"
#include "ports/TexturePort.h"
#include "ports/PlayerRenderPort.h"
#include "Camera.h"
#include <vector>
#include <memory>
#include "MixerManager.h" // Inclui o MixerManager

class Game {
public:
   Game(RendererPort *renderer, EventPort *eventPort, TexturePort *texturePort, Camera camera);
    void run();
    void processEvents(bool running);
    void updateGameObjects(float deltaTime);
    void renderGameObjects();
    void controlFrameRate(Uint32 frameStar, float frameDelay);
    void renderScore(int score); 
    

private:
    RendererPort *renderer;
    EventPort *eventPort;
    TexturePort *texturePort;
    std::vector<std::unique_ptr<ObjectGame>> gameObjects;
    Camera camera;

    GameAudio::MixerManager mixerManager; 
    int score = 0; 
};

#endif // GAME_H
