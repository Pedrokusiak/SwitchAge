all:
	g++ -g -I src/include -I . -I ports -I domain -L src/lib -o main main.cpp domain/Position.cpp domain/ObjectGame.cpp  domain/VisualElement.cpp domain/ObjectGameStatic.cpp domain/GroundSegment.cpp domain/Hitbox.cpp domain/Player.cpp domain/Game.cpp adapters/SDL/SDLRendererAdapter.cpp adapters/SDL/SDLEventAdapter.cpp -lmingw32 -lSDL2main -lSDL2

clean:
	rm -f *.o main

.PHONY: all clean
