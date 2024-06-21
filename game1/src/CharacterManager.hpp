#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Character.hpp"
#include "World.hpp"
#include "InputHandler.hpp"
using namespace std;

class CharacterManager {
public:
    CharacterManager(int width, int height, int tileSizeX, int tileSizeY);
    ~CharacterManager();
    void drawCharacters(sf::RenderTarget& rt);
    sf::Vector2f getPlayerCenter(); // NOTE: not properly centered
    void updateCharacters(float dt, vector<vector<int>> colTiles);
private:
    sf::Texture characterTexture_;
    vector<Character*> characters_;
    int width_, height_, tileSizeX_, tileSizeY_; // used for collision checking
    InputHandler *inputHandler_;
    int loadCharacterTextures(); // Loads char textures
    int loadCharacters();
    sf::Vector2f handleMovementCollision(Character& actor, float dt, vector<vector<int>> colTiles);
};