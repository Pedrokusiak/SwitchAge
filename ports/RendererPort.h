

#ifndef RENDERERPORT_H
#define RENDERERPORT_H

class RendererPort {
public:
    virtual ~RendererPort() = default;
    virtual void draw() const = 0;
};

#endif 
