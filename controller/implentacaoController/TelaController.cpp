class TelaController : public TelaControllerInterface{
    private:
    Tela* tela;
    RenderizadorController* renderizador;

    
    public:
    TelaController(Tela* tela, RenderizadorController* renderizador) : tela(tela, renderizador) {}
    virtual ~TelaController() {}
    
    

    void processarEventos() override {
        std::cout << "Tela Controller: Processando eventos." << std::endl;
    }

    void preparaCenario() override {
        std::cout << "Tela Controller: Preparando Cenario." << std::endl;
        renderizador->preparaCenario();
    }

    void copiarBlocoPixel() override {
        std::cout << "Tela Controller: copiarBlocoPixel." << std::endl;
        renderizador->copiarBlocoPixel();
    }
}