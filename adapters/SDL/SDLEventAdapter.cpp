#include "SDLEventAdapter.h"


SDLEventAdapter::SDLEventAdapter() {}

SDLEventAdapter::~SDLEventAdapter() {}

bool SDLEventAdapter::pollEvent() {
    return SDL_PollEvent(&event);
}

bool SDLEventAdapter::isQuitEvent() const {
    return event.type == SDL_QUIT;
}

bool SDLEventAdapter::isKeyDownEvent() const {
    return event.type == SDL_KEYDOWN;
}

int SDLEventAdapter::getKey() const {
    return event.key.keysym.sym;
}
