#ifndef RENDERIZADORCONTROLLER_H
#define RENDERIZADORCONTROLLER_H


class RenderizadorControllerInterface {
public:
    virtual ~RenderizadorControllerInterface(){}
    virtual void copiarBlocoPixel(void* texture, int x, int y) = 0;	
    virtual void preparaCenario();                
    virtual void cenaPresente(); 
};

#endif
