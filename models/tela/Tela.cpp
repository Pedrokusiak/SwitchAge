#include <iostream>
namespace models{
    namespace tela{
        class Tela: public TelaSDL {

        private:
            SDL_Renderer *render;
            SDL_Window *janela;
        public:
            int getCima(){
                return cima;
            }
            int getBaixo(){
                return baixo;
            }
            int getDireita(){
                return direita;
            }
            void setCima(c){
                cima = c;
            }
            void setBaixo(b){
                baixo= b;
            }
            void setDireita(d){
                direita = d;
            }
        void desenhar() override {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
        }
    }
}


