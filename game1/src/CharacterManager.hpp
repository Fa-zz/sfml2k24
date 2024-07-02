#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Character.hpp"
#include "World.hpp"
#include "InputHandler.hpp"
using namespace std;

/*
    Handles stuff for actors/characters, including PC and NPCs
    Loads character textures and creates characters. 
    Takes in dispatched commands.
    Handles commands, updates characters being mindful of collision
*/

class CharacterManager {
public:
    // todo: load characters is public and setters for private member vars
    CharacterManager();
    CharacterManager(int width, int height, int tileSizeX, int tileSizeY);  // Loads textures and characters
    ~CharacterManager();
    void drawCharacters(sf::RenderTarget& rt);
    sf::Vector2f getPlayerCenter(); // NOTE: not properly centered on the exact character center
    sf::Vector2f getCenter(Character& actor);
    void setPosWithoutCollisionTiles(Character& actor, float dt, int width, int height);
    void updateCharacters(float dt, vector<vector<int>> colTiles);
private:
    sf::Texture characterTexture_;
    vector<Character*> characters_;
    int width_, height_, tileSizeX_, tileSizeY_; // used for collision checking
    // InputHandler *inputHandler_;
    int loadCharacterTextures(); // Loads char textures
    int loadCharacters();
    sf::Vector2f handleMovementCollision(Character& actor, float dt, vector<vector<int>> colTiles);
};