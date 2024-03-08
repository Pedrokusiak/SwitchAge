class TelaControllerInterface{
    private:
        Tela* tela
    public:
        virtual void processarEventos() = 0;
        void setTela(Tela* tela){
            this->tela = tela;
        };
        Tela* getTela(){
            return tela;
        }
    
} 