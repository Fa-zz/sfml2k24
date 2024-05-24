#pragma once
#include "Terrain.hpp"
#include "Character.hpp"
#include <vector>
#include <unordered_map>
using namespace std;

class World {
public:
    World();
    ~World();
    int genTiles(int height, int width);
    Terrain* getGroundTileAtPos(int y, int x);
    Terrain* getBuildingTileAtPos(int y, int x);
    void drawCharacters(sf::RenderTarget& rt);
    sf::Vector2f getMCCenter();
    void updateCharacters(sf::Vector2f dir, float dt);
private:
    vector<Terrain*> allTerrains_; // allTerrains_: Every vector we create from the loaded textures is added to this vector
    // NOTE: If allTerrains_ is just used for destructor, I think we can just iterate over groundMap_ and delete each, making it obsolete
    unordered_map<string, Terrain*> groundMap_; // groundMap_: This maps every terrain object to an ID provided from Tiled. Used to determine ground tile at every location of the game board. See genTiles()
    unordered_map<string, Terrain*> buildingMap_; // groundMap_: This maps every terrain object to an ID provided from Tiled. Used to determine ground tile at every location of the game board. See genTiles()

    sf::Texture groundTexture_; // groundTexture_: Tex for ground tiles, loaded in from assets
    sf::Texture buildingTexture_; // buildingTexture_: Tex for building tiles, loaded in from assets
    sf::Texture characterTexture_;
    vector<vector<Terrain*>> groundTiles_; // groundTiles_: All ground tiles present for every location of the game board. Rendered first
    vector<vector<Terrain*>> buildingTiles_; // buildingTiles_: All building tiles present for every location of the game board. Rendered second
    vector<Character*> characters_;
    int loadTerrainTextures(); // Loads ground, building, and other textures
    int loadCharacterTextures(); // Loads char textures
    int loadTerrainMap(); // Loads pieces of terrains
    int loadCharacters(); // 
    //void updateMC();

};