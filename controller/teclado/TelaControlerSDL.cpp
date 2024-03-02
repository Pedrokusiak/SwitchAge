class TecladoSDL : public TecladoInterface {
private:
    SDL_KeyboardEvent* event; 
public:
    TecladoSDL(SDL_KeyboardEvent* event) : event(event) {}

    void teclaParaCima() override {}

    void teclaParaBaixo() override {}
};