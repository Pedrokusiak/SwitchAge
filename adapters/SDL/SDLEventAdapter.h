#ifndef SDLEVENTADAPTER_HPP
#define SDLEVENTADAPTER_HPP

#include <SDL2/SDL.h>
#include <ports/EventPort.h>

class SDLEventAdapter : public EventPort {
public:
    SDLEventAdapter();
    ~SDLEventAdapter();
    bool pollEvent() override;
    bool isQuitEvent() const override;
    bool isKeyDownEvent() const override;
    int getKey() const override;

private:
    SDL_Event event;
};

#endif // SDLEVENTADAPTER_HPP
