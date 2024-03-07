class TelaController : public TelaControllerInterface{
    private:
    Tela* tela;
    SDL_Renderer* renderizador;

    
    public:
    TelaController(Tela* tela, SDL_Renderer* renderizador) : tela(tela) {}
    virtual ~TelaController() {}
    void processarEventos() override {
        std::cout << "Tela Controller: Processando eventos." << std::endl;
        Sq
    }

    void preparaCenario() override {
        tela->preparaCenario();
    }

    void copiarBlocoPixel() override {
        tela->copiarBlocoPixel();
    }
}