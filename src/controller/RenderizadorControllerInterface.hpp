class RenderizadorControllerInterface {
public:
    virtual ~Renderizador() {}
    virtual void copiarBlocoPixel(void* texture, int x, int y) = 0;
    virtual void preparaCenario();                
    virtual void cenaPresente(); 
};