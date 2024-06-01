#include "CharacterManager.hpp"

CharacterManager::CharacterManager() {
    if (loadCharacterTextures() != 0)
        cerr << "Failed to load character textures" << endl;
    loadCharacters();
}

CharacterManager::~CharacterManager() {
    for (Character* actor : characters_) {
        delete actor;
    }
}

int CharacterManager::loadCharacterTextures() {
    if (!characterTexture_.loadFromFile("assets/characters.png")) {
        return -1;
    }
    return 0;
}

int CharacterManager::loadCharacters() {
    characters_.push_back(new Character(0, 32, 16, 16, characterTexture_, sf::Vector2f{0.f, 0.f}));
    return 0;
}

void CharacterManager::drawCharacters(sf::RenderTarget& rt) {
    for(const Character* actor : characters_) 
        actor->draw(rt);
}

sf::Vector2f CharacterManager::getPlayerCenter() {
    return sf::Vector2f(characters_[0]->getSprite().getPosition().x, characters_[0]->getSprite().getPosition().y);
}

void CharacterManager::updateCharacters(sf::Vector2f dir, float dt, int width, int height, World* world) {
    characters_[0]->setDirection(dir);

    characters_[0]->update(dt, width, height, world);
}