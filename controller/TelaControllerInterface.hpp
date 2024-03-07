class TelaControllerInterface{
    private:
        Tela* tela
    public:
        virtual void processarEventos() = 0;
        virtual void preparaCenario(void) = 0;
        virtual void copiarBlocoPixel();
        void setTela(Tela* tela){
            this->tela = tela;
        };
        Tela* getTela(){
            return tela;
        }
    
} 