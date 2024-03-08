CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lSDL2

EXEC = meu_programa

SRCDIR = src
BUILDDIR = build
TARGETDIR = bin

SRCS = main.cpp \
       controller/implentacaoController/TelaController.cpp \
       models/implentacao/Tela.cpp \
       controller/implentacaoController/RenderizadorController.cpp

OBJS = $(SRCS:%.cpp=$(BUILDDIR)/%.o)

all: $(TARGETDIR)/$(EXEC)

$(TARGETDIR)/$(EXEC): $(OBJS) | directories
    $(CXX) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: %.cpp | directories
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    $(RM) -r $(BUILDDIR)/* $(TARGETDIR)/*

# Regra para criar diretórios necessários
directories:
    @mkdir -p $(BUILDDIR) $(TARGETDIR)

# Define as regras que não geram arquivos de saída
.PHONY: all clean directories
