CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lSDL2

all: directories bin/meu_programa

bin/meu_programa: build/main.o build/TelaController.o build/Tela.o build/RenderizadorController.o
	g++ $^ -o $@ $(LDFLAGS)

build/main.o: src/main.cpp | directories
	g++ $(CXXFLAGS) -c $< -o $@

build/TelaController.o: src/controller/implentacaoController/TelaController.cpp | directories
	g++ $(CXXFLAGS) -c $< -o $@

build/Tela.o: src/models/implentacao/Tela.cpp | directories
	g++ $(CXXFLAGS) -c $< -o $@

build/RenderizadorController.o: src/controller/implentacaoController/RenderizadorController.cpp | directories
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -r build/* bin/*

directories:
	mkdir -p build bin

