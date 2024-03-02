class MovimentacaoController {
private:
    TecladoInterface* teclado;
public:
    virtual void teclaParaCima(SDL_KeyboardEvent *event);
    virtual void teclaParaBaixo(SDL_KeyboardEvent *event);
    virtual void leEntrada(void);
    virtual void movimentaObjeto(Objeto objeto, Direcao direcao, int quantidade);
};