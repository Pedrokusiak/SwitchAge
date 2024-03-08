lass InterfaceExemplo{
    public:
        virtual void teclaParaCima(){
            jogo->teclaParaCima(); 
        }
        virtual void processarEventos() = 0;
};

class ImplementacaoExemplo : public InterfaceExemplo{
    public:
        void processarEventos() override{
             SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;
            case SDL_KEYUP:
                teclaParaCima(); // Call doKeyUp function here
                break;
            default:
                break;
             }
            }
        };
};