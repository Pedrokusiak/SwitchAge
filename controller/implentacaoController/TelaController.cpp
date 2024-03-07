class TelaController : public TelaControllerInterface{
    private:
    Tela* tela;
    RenderizadorController* renderizador;

    
    public:
    TelaController(Tela* tela, SDL_Renderer* renderizador) : tela(tela) {}
    virtual ~TelaController() {}
    void processarEventos() override {
        std::cout << "Tela Controller: Processando eventos." << std::endl;
    }

    void preparaCenario() override {
        renderizador->preparaCenario();
    }

    void copiarBlocoPixel() override {
        renderizador->copiarBlocoPixel();
    }
}