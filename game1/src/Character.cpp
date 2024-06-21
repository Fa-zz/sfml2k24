#include "Character.hpp"
#include <iostream>
using namespace std;

Character::Character(int x, int y, int tileSizeX, int tileSizeY, const sf::Texture& texture, const sf::Vector2f& pos) 
    : x_(x), y_(y), tileSizeX_(tileSizeX), tileSizeY_(tileSizeY), pos_(pos) {
    sprite_.setTexture(texture);
    sprite_.setTextureRect({x, y, tileSizeX, tileSizeY});
    setPos(pos);

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

void Character::setDirection() {
    vel_ = dir_ * speed_;
    if (dir_.x == 0.0f && dir_.y == 0.0f) {
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
        if (dir_.x > 0.0f) {
            curAnimation_ = AnimationIndex::WalkingHoriz;
            walkingLeft_ = false;
        } else if (dir_.x < 0.0f) {
            curAnimation_ = AnimationIndex::WalkingHoriz;
            walkingLeft_ = true;
        } else if (dir_.y < 0.0f) {
            curAnimation_ = AnimationIndex::WalkingUp;
            walkingLeft_ = false;
        } else if (dir_.y > 0.0f) {
            curAnimation_ = AnimationIndex::WalkingDown;
            walkingLeft_ = false;
        }
    }
}

void Character::update(float dt) {
    animations_[int(curAnimation_)].update(dt);
    animations_[int(curAnimation_)].applyToSprite(sprite_, walkingLeft_);
}

void Character::setPos(sf::Vector2f newPos) {
    pos_ = newPos;
    sprite_.setPosition(pos_);
}
sf::Sprite Character::getSprite() { return sprite_; }

sf::Vector2f Character::getPos() { return pos_; }

sf::Vector2f Character::getVel() { return vel_; }

sf::Vector2f Character::getDir() { return dir_; }

void Character::addDir(sf::Vector2f newDir) { 
    dir_ += newDir;
}

void Character::resetDir() { dir_ = sf::Vector2f{0,0}; }
