all:
	g++ -I src/include -I . -I ports -I domain -L src/lib -o main main.cpp adapters/SDL/SDLRendererAdapter.cpp domain/Game.cpp domain/PlayerPhysics.cpp domain/GroundPhysics.cpp domain/Position.cpp domain/Player.cpp domain/Ground.cpp -lmingw32 -lSDL2main -lSDL2
