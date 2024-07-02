#include "CharacterManager.hpp"

CharacterManager::CharacterManager(int width, int height, int tileSizeX, int tileSizeY)
:width_(width),height_(height),tileSizeX_(tileSizeX),tileSizeY_(tileSizeY) {
    if (loadCharacterTextures() != 0)
        cerr << "Failed to load character textures" << endl;
    loadCharacters();
    // inputHandler_ = new InputHandler();
}

CharacterManager::CharacterManager() { }

CharacterManager::~CharacterManager() {
    for (Character* actor : characters_) {
        delete actor;
    }
    // delete inputHandler_;
}

int CharacterManager::loadCharacterTextures() {
    if (!characterTexture_.loadFromFile("assets/characters.png")) {
        return -1;
    }
    return 0;
}

int CharacterManager::loadCharacters() {
    characters_.push_back(new Character(0, 32, 16, 16, characterTexture_, sf::Vector2f{3.f * 16, 6.f * 16}));
    characters_.push_back(new Character(0, 48, 16, 16, characterTexture_, sf::Vector2f{16.f * 16, 10.f * 16}));
    return 0;
}

void CharacterManager::drawCharacters(sf::RenderTarget& rt) {
    for(const Character* actor : characters_) 
        actor->draw(rt);
}

sf::Vector2f CharacterManager::getPlayerCenter() {
    return sf::Vector2f(characters_[0]->getSprite().getPosition().x, characters_[0]->getSprite().getPosition().y);
}

sf::Vector2f CharacterManager::getCenter(Character& actor) {
    return sf::Vector2f(actor.getSprite().getPosition().x, actor.getSprite().getPosition().y);
}

// Takes in dispatched commands and handles them, depending on what they are.
// If movement, uses helper function to determine result of movement, then allows command to execute on desired actor
// Characters are updated and have direction stuff every cycle.
void CharacterManager::updateCharacters(float dt, vector<vector<int>> colTiles) {
    // cout << "Character pos x: " << characters_[0]->getPos().x << " char pos y: " << characters_[0]->getPos().y << endl;
    // Command* command = inputHandler_->handleInput();
    // if (command) {
    //     if ((command->getCommandsKey() == sf::Keyboard::Right) || (command->getCommandsKey() == sf::Keyboard::Left) || (command->getCommandsKey() == sf::Keyboard::Up) || (command->getCommandsKey() == sf::Keyboard::Down)) {
    //         sf::Vector2f result = handleMovementCollision(*characters_[0], dt, colTiles);
    //         command->execute(*characters_[0]);
    //         characters_[0]->setPos(result);
    //     }
    // }
    // characters_[0]->update(dt);
    // characters_[0]->setDirection();
    // characters_[0]->resetDir();

    // 
    // if (inputHandler_->specifiedOutput(AI.overworldNPCMeandering()))
    //  NPCCommandBuffer.push_back(inputHandler_->specifiedOutput(AI.overworldNPCMeandering()))
}

// Potential position is old position + velocity * dt. Checks if new position violates game boundaries, or a game collision tile
// Without violation, returns the potential position. With violation returns old character position (character's pos does not change)
void CharacterManager::setPosWithoutCollisionTiles(Character& actor, float dt, int width, int height) {
    sf::Vector2f newPos = actor.getPos() + actor.getVel() * dt;
    if (newPos.x >= 0 && newPos.x < (width * 16) && newPos.y >= 0 && newPos.y < (height * 16)) {
        actor.setPos(newPos);
    }
}

sf::Vector2f CharacterManager::handleMovementCollision(Character& actor, float dt, vector<vector<int>> colTiles) {
    sf::Vector2f newPos = actor.getPos() + actor.getVel() * dt;
    // cout << "New pos: " << newPos.x << " " << newPos.y << endl;
    if (newPos.x >= 0 && newPos.x < (width_ * tileSizeX_) && newPos.y >= 0 && newPos.y < (height_ * tileSizeY_)) {
        int tileX = static_cast<int>(newPos.x) / tileSizeX_;
        int tileY = static_cast<int>(newPos.y) / tileSizeY_;
        cout << "tileX:" << tileX << " tileY:" << tileY << endl;
        int colTile = colTiles[tileY][tileX];
        if (colTile == -1) {
            return newPos;
        } else {
            return actor.getPos();
        }
    } else {
        return actor.getPos();
    }
}