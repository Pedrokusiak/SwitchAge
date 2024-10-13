
    #ifndef ANIMATION_H
    #define ANIMATION_H

#include "ITexture.h"
#include "RendererPort.h"
#include <vector>
#include <map>
#include <string>
#include <memory>

class Animation {
public:
    Animation(RendererPort* renderer, std::shared_ptr<ITexture> spritesheet, int frameWidth, int frameHeight);

    void addAnimation(const std::string& name, const std::vector<int>& frameIndices);
    bool isPlayingAnimation(const std::string& name) const;
    void playAnimation(const std::string& name, bool loop = true);
    void update(float deltaTime);
    
    void render(int x, int y);

    int getFrameWidth() const { return frameWidth; }
    int getFrameHeight() const { return frameHeight; }
    std::string getCurrentAnimation() const { return currentAnimation; }
    void setFrameDuration(float duration) { frameDuration = duration; }

    enum class Direction {
        Left = 0,
        Right = 1,
        Up = 2,
        Down = 3
    };

private:
    RendererPort* renderer;
    std::shared_ptr<ITexture> spritesheet;
    int frameWidth;
    int frameHeight;
    int spritesheetCols;

    std::map<std::string, std::vector<int>> animations;
    std::string currentAnimation;
    int currentFrameIndex;
    float frameTimer;
    float frameDuration;
    bool looping;
};

#endif // ANIMATIO

