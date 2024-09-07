all:
	g++ -g -I src/include -I . -I ports -I domain -L src/lib -L src/lib/sdl_image -o main main.cpp domain/Position.cpp domain/ObjectGame.cpp domain/VisualElement.cpp domain/GroundSegment.cpp domain/Hitbox.cpp domain/Player.cpp domain/Game.cpp domain/Physics.cpp domain/Animation.cpp domain/PlayerAnimation.cpp adapters/SDL/SDLRendererAdapter.cpp adapters/SDL/SDLEventAdapter.cpp  -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

clean:
	rm -f *.o main

.PHONY: all clean
