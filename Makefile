CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lSDL2

SRCDIR = src
BUILDDIR = build
TARGETDIR = bin

SRCS = src/main.cpp src/controller/implentacaoController/TelaController.cpp src/models/implentacao/Tela.cpp src/controller/implentacaoController/RenderizadorController.cpp
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

EXEC = bin/SwitchAge

all: directories $(EXEC)

$(EXEC): $(OBJS)
    g++ $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
    g++ $(CXXFLAGS) -c $< -o $@

clean:
    rm -r $(BUILDDIR)/* $(TARGETDIR)/*

directories:
    mkdir -p $(BUILDDIR) $(TARGETDIR)

.PHONY: all clean directories
