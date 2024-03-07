class Renderizador {
public:
    virtual ~Renderizador() {}
    virtual void copiarBlocoPixel(void* texture, int x, int y) = 0;
};