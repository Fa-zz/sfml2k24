#include "Character.hpp"
#include <iostream>
using namespace std;

Character::Character(int x, int y, int tileSizeX, int tileSizeY, const sf::Texture& texture, const sf::Vector2f& pos) 
    : x_(x), y_(y), tileSizeX_(tileSizeX), tileSizeY_(tileSizeY), pos_(pos) {
    sprite_.setTexture(texture);
    sprite_.setTextureRect({x, y, tileSizeX, tileSizeY});

    animations_[int(AnimationIndex::StandingStillDown)] = Animation(x, y, tileSizeX, tileSizeY, texture, true);
    animations_[int(AnimationIndex::StandingStillUp)] = Animation(x + tileSizeX, y, tileSizeX, tileSizeY, texture, true);
    animations_[int(AnimationIndex::StandingStillHoriz)] = Animation(x + tileSizeX * 2, y, tileSizeX, tileSizeY, texture, true);

    animations_[int(AnimationIndex::WalkingDown)] = Animation(64, y, tileSizeX, tileSizeY, texture, false);
    animations_[int(AnimationIndex::WalkingUp)] = Animation(96, y, tileSizeX, tileSizeY, texture, false);
    animations_[int(AnimationIndex::WalkingHoriz)] = Animation(128, y, tileSizeX, tileSizeY, texture, false);
}

void Character::draw(sf::RenderTarget& rt) const {
    rt.draw(sprite_);
}

void Character::setDirection(const sf::Vector2f& dir) {
    vel_ = dir * speed_;
    if (dir.x == 0.0f && dir.y == 0.0f) {
        if (curAnimation_ == AnimationIndex::WalkingHoriz) {
            curAnimation_ = AnimationIndex::StandingStillHoriz;
        } else if (curAnimation_ == AnimationIndex::WalkingUp) {
            curAnimation_ = AnimationIndex::StandingStillUp;
        } else if (curAnimation_ == AnimationIndex::WalkingDown) {
            curAnimation_ = AnimationIndex::StandingStillDown;
        }
        standingStill_ = true;
    } else {
        standingStill_ = false;
        if (dir.x > 0.0f) {
            curAnimation_ = AnimationIndex::WalkingHoriz;
            walkingLeft_ = false;
        } else if (dir.x < 0.0f) {
            curAnimation_ = AnimationIndex::WalkingHoriz;
            walkingLeft_ = true;
        } else if (dir.y < 0.0f) {
            curAnimation_ = AnimationIndex::WalkingUp;
            walkingLeft_ = false;
        } else if (dir.y > 0.0f) {
            curAnimation_ = AnimationIndex::WalkingDown;
            walkingLeft_ = false;
        }
    }
}

void Character::update(float dt, int width, int height, World* world) {
    sf::Vector2f newPos = pos_ + vel_ * dt;

    if (newPos.x >= 0 && newPos.x < (width * tileSizeX_) && newPos.y >= 0 && newPos.y < (height * tileSizeY_)) {
        int tileX = static_cast<int>(newPos.x) / tileSizeX_;
        int tileY = static_cast<int>(newPos.y) / tileSizeY_;
        cout << "tileX:" << tileX << " tileY:" << tileY << endl;
        Terrain* buildingTile = world->getBuildingTileAtPos(tileY, tileX);
        if (buildingTile == nullptr) {
            pos_ = newPos;
            sprite_.setPosition(pos_);
        }
    }

    animations_[int(curAnimation_)].update(dt);
    animations_[int(curAnimation_)].applyToSprite(sprite_, walkingLeft_);
}

sf::Sprite Character::getSprite() {
    return sprite_;
}
