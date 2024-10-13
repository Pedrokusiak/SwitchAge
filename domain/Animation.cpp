// Animation.cpp
#include "Animation.h"
#include <iostream>

Animation::Animation(RendererPort *ren, std::shared_ptr<ITexture> sheet, int fWidth, int fHeight)
    : renderer(ren), spritesheet(sheet), frameWidth(fWidth), frameHeight(fHeight),
      currentFrameIndex(0), frameTimer(0), frameDuration(0.5f), looping(false)
{

    if (spritesheet)
    {
        spritesheetCols = spritesheet->getWidth() / frameWidth;
    }
    else
    {
        std::cerr << "Error: Spritesheet is null in Animation constructor." << std::endl;
        spritesheetCols = 1;
    }
}

void Animation::addAnimation(const std::string &name, const std::vector<int> &frameIndices)
{
    animations[name] = frameIndices;
}

bool  Animation::isPlayingAnimation(const std::string &name) const
{
    return currentAnimation == name;
}

void Animation::playAnimation(const std::string &name, bool loop)
{
    auto it = animations.find(name);
    if (it != animations.end())
    {
        currentAnimation = name;
        currentFrameIndex = 0;
        frameTimer = 0;
        looping = loop;
    }
    else
    {
        std::cerr << "Error: Animation '" << name << "' not found." << std::endl;
    }
}

void Animation::update(float deltaTime)
{
    if (currentAnimation.empty() || animations[currentAnimation].empty())
    {
        return;
    }

    std::cout << "TESTE - Frame Atual: " << currentFrameIndex << " na animacao: " << currentAnimation << std::endl;
    std::cout << "TESTE - Frame Timer: " << frameTimer << " deltaTime " << deltaTime << std::endl;

    std::cout << "TESTE - Frame Timer: " << frameTimer << " na FrameDuration: " << frameDuration << std::endl;
    frameTimer += deltaTime;
    if (frameTimer >= frameDuration)
    {
        frameTimer -= frameDuration;
        currentFrameIndex++;

        if (currentFrameIndex >= animations[currentAnimation].size())
        {
            if (looping)
            {
                currentFrameIndex = 0;
            }
            else
            {
                currentFrameIndex = animations[currentAnimation].size() - 1;
            }
        }

        std::cout << "Frame Atualizado para: " << currentFrameIndex << " na animação: " << currentAnimation << std::endl;
    }
}

void Animation::render(int x, int y)
{
    if (currentAnimation.empty() || animations[currentAnimation].empty())
    {
        std::cerr << "Error: No current animation or animation is empty." << std::endl;
        return;
    }

    int frameIndex = animations[currentAnimation][currentFrameIndex];

    // Cálculo correto da linha e coluna
    int row = frameIndex / spritesheetCols;
    int col = frameIndex % spritesheetCols;

    // Verificar se spritesheetCols está correto e frames estão sendo acessados corretamente
    if (spritesheetCols == 0)
    {
        std::cerr << "Error: spritesheetCols is zero, possibly due to incorrect spritesheet dimensions." << std::endl;
        return;
    }

    int srcX = col * frameWidth;
    int srcY = row * frameHeight;

    // Debug: Mostrar a posição de renderização
    std::cout << "Rendering frame: " << frameIndex << " at position (" << srcX << ", " << srcY << ")" << std::endl;

    renderer->drawTexturePart(spritesheet, x, y, frameWidth, frameHeight, srcX, srcY, frameWidth, frameHeight);
}