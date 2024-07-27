

#ifndef PAGERENDERPORT_H
#define PAGERENDERPORT_H
#include <SDL2/SDL.h>


class PageRenderPort {
public:
    virtual void present() const = 0;
    virtual void quit() const = 0; 
};

#endif 
