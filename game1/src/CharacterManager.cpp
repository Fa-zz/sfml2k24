#include "CharacterManager.hpp"

CharacterManager::CharacterManager(int width, int height, int tileSizeX, int tileSizeY)
:width_(width),height_(height),tileSizeX_(tileSizeX),tileSizeY_(tileSizeY) {
    if (loadCharacterTextures() != 0)
        cerr << "Failed to load character textures" << endl;
    loadCharacters();
    inputHandler_ = new InputHandler();
}

CharacterManager::~CharacterManager() {
    for (Character* actor : characters_) {
        delete actor;
    }
    delete inputHandler_;
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

void CharacterManager::updateCharacters(float dt, vector<vector<Terrain*>> buildingTiles) {
    Command* command = inputHandler_->handleInput();
    if (command) {
        if ((command->getCommandsKey() == sf::Keyboard::Right) ||
        (command->getCommandsKey() == sf::Keyboard::Left) ||
        (command->getCommandsKey() == sf::Keyboard::Up) ||
        (command->getCommandsKey() == sf::Keyboard::Down)) {
            sf::Vector2f result = handleMovementCollision(*characters_[0], dt, buildingTiles);
            command->execute(*characters_[0]);
            characters_[0]->setPos(result);
        }
    }
    characters_[0]->update(dt);
    characters_[0]->setDirection();
    characters_[0]->resetDir();
}

sf::Vector2f CharacterManager::handleMovementCollision(Character& actor, float dt, vector<vector<Terrain*>> buildingTiles) {
    sf::Vector2f newPos = actor.getPos() + actor.getVel() * dt;
    if (newPos.x >= 0 && newPos.x < (width_ * tileSizeX_) && newPos.y >= 0 && newPos.y < (height_ * tileSizeY_)) {
        int tileX = static_cast<int>(newPos.x) / tileSizeX_;
        int tileY = static_cast<int>(newPos.y) / tileSizeY_;
        cout << "tileX:" << tileX << " tileY:" << tileY << endl;
        Terrain* buildingTile = buildingTiles[tileY][tileX];
        if (buildingTile == nullptr) {
            return newPos;
        } else {
            return actor.getPos();
        }
    }
}