all:
	g++ -g -I src/include -I src/include/SDL2 -I . -I ports -I domain -L src/lib -L src/lib/sdl_image -o main main.cpp \
domain/Position.cpp domain/ObjectGame.cpp domain/Animation.cpp domain/Camera.cpp domain/VisualElement.cpp \
domain/GroundSegment.cpp domain/Hitbox.cpp domain/Player.cpp domain/Game.cpp domain/Physics.cpp domain/MixerManager.cpp \
adapters/SDL/SDLRendererAdapter.cpp adapters/SDL/SDLEventAdapter.cpp adapters/SDL/SDLTexture.cpp \
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

clean:
	rm -f *.o main

.PHONY: all clean
