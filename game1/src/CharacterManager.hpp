#pragma once
#include "Character.hpp"
#include "World.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
using namespace std;

class CharacterManager {
public:
    CharacterManager();
    ~CharacterManager();
    void drawCharacters(sf::RenderTarget& rt);
    sf::Vector2f getPlayerCenter(); // NOTE: not properly centered
    void updateCharacters(sf::Vector2f dir, float dt, int width, int height, World* world);
private:
    sf::Texture characterTexture_;
    vector<Character*> characters_;
    int loadCharacterTextures(); // Loads char textures
    int loadCharacters(); // 
};