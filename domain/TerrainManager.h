#ifndef TERRAIN_MANAGER_H
#define TERRAIN_MANAGER_H

#include <memory>
#include <vector>
#include "Camera.h"
#include "ports/RendererPort.h"
#include "ports/TexturePort.h"
#include "GroundSegment.h"

class TerrainManager {
private:
    RendererPort* renderer;
    TexturePort* texturePort;
    std::shared_ptr<ITexture> groundTexture;
    int tileSize;
    int levelWidth;
    int levelHeight;
    std::vector<int> vectorListTerrain;
    std::vector<std::unique_ptr<GroundSegment>> segments;
    
public:
    TerrainManager(RendererPort* renderer, TexturePort* texturePort, int tileSize = 32) 
        : renderer(renderer), texturePort(texturePort), tileSize(tileSize) {
        groundTexture = texturePort->loadTexture("asserts/Tiny Swords (Update 010)/Terrain/Ground/Tilemap_Flat.png");
    }

    void initializeLevel(int width, int height) {
        // Define a lista de terreno (você pode modificar isso conforme necessário)
        vectorListTerrain = {0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
        
        levelWidth = width * tileSize;
        levelHeight = height * tileSize;
        
        // Cria o terreno baseado na lista
        createTerrainFromList();
        createSuperficeFromList();
    }

    const std::vector<std::unique_ptr<GroundSegment>>& getSegments() const {
        return segments;
    }

private:
    void createTerrainFromList() {
        const int SEGMENT_WIDTH = 200; // Largura fixa de 100 pixels para cada segmento
        
        for (size_t i = 0; i < vectorListTerrain.size(); i++) {
            if (vectorListTerrain[i] == 1) {
                // Calcula a posição X baseada no índice
                int posX = i * SEGMENT_WIDTH;
                
                // Cria um segmento de chão
                auto segment = std::make_unique<GroundSegment>(
                    Vector2D(posX, levelHeight - tileSize), // Posição (y é a parte inferior do nível)
                    Vector2D(SEGMENT_WIDTH, tileSize),      // Tamanho (100 pixels de largura)
                    Vector2D(0, 0),                         // Gravidade
                    1000.0f,                               // Massa
                    true,                                  // Hibernate
                    groundTexture,                         // Textura
                    renderer,                              // Renderer
                    tileSize,                              // Frame width
                    tileSize                               // Frame height
                );
                
                segments.push_back(std::move(segment));
            }
        }
    }

    void createSuperficeFromList(){
        const int SEGMENT_WIDTH = 100; // Largura fixa de 100 pixels para cada segmento
        
        for (size_t i = 0; i < vectorListTerrain.size(); i++) {
            if (vectorListTerrain[i] == 0) {
                // Calcula a posição X baseada no índice
                int posX = i * SEGMENT_WIDTH;
                
                // Cria um segmento de chão
                auto segment = std::make_unique<GroundSegment>(
                    Vector2D(posX, (levelHeight + 250) - tileSize), // Posição (y é a parte inferior do nível)
                    Vector2D(SEGMENT_WIDTH, tileSize),      // Tamanho (100 pixels de largura)
                    Vector2D(0, 0),                         // Gravidade
                    1000.0f,                               // Massa
                    true,                                  // Hibernate
                    groundTexture,                         // Textura
                    renderer,                              // Renderer
                    tileSize,                              // Frame width
                    tileSize                               // Frame height
                );
                
                segments.push_back(std::move(segment));
            }
        }
    }

 
};

#endif // TERRAIN_MANAGER_H