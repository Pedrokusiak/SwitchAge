// Animation.cpp
#include "Animation.h"
#include <iostream>

Animation::Animation(RendererPort* ren, std::shared_ptr<ITexture> sheet, int fWidth, int fHeight)
    : renderer(ren), spritesheet(sheet), frameWidth(fWidth), frameHeight(fHeight),
      currentFrameIndex(0), frameTimer(0), frameDuration(0.1f), looping(false) {
    
    if (spritesheet) {
        spritesheetCols = spritesheet->getWidth() / frameWidth;
    } else {
        std::cerr << "Error: Spritesheet is null in Animation constructor." << std::endl;
        spritesheetCols = 1;
    }
}

void Animation::addAnimation(const std::string& name, const std::vector<int>& frameIndices) {
    animations[name] = frameIndices;
}

void Animation::playAnimation(const std::string& name, bool loop) {
    auto it = animations.find(name);
    if (it != animations.end()) {
        currentAnimation = name;
        currentFrameIndex = 0;
        frameTimer = 0;
        looping = loop;
    } else {
        std::cerr << "Error: Animation '" << name << "' not found." << std::endl;
    }
}

void Animation::update(Uint32 deltaTime) {
    if (currentAnimation.empty() || animations[currentAnimation].empty()) {
        return;
    }

    frameTimer += deltaTime;
    if (frameTimer >= frameDuration) {
        frameTimer -= frameDuration;
        currentFrameIndex++;

        if (currentFrameIndex >= animations[currentAnimation].size()) {
            if (looping) {
                currentFrameIndex = 0;
            } else {
                currentFrameIndex = animations[currentAnimation].size() - 1;
            }
        }

        std::cout << "Updated to frame: " << currentFrameIndex << " in animation: " << currentAnimation << std::endl;
    }
}

void Animation::render(int x, int y) {
    if (currentAnimation.empty() || animations[currentAnimation].empty()) {
        std::cerr << "Error: No current animation or animation is empty." << std::endl;
        return;
    }

    int frameIndex = animations[currentAnimation][currentFrameIndex];
    int row = frameIndex / spritesheetCols;
    int col = frameIndex % spritesheetCols;

    int srcX = col * frameWidth;
    int srcY = row * frameHeight;

    std::cout << "Rendering frame: " << frameIndex << " at position (" << srcX << ", " << srcY << ")" << std::endl;

    renderer->drawTexturePart(spritesheet, x, y, frameWidth, frameHeight, srcX, srcY, frameWidth, frameHeight);
}
