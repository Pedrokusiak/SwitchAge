all:
	g++ -I src/include -I . -I ports -I domain -L src/lib -o main main.cpp adapters/SDL/SDLRendererAdapter.cpp domain/Game.cpp -lmingw32 -lSDL2main -lSDL2
