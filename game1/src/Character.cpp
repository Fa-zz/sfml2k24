#include "Character.hpp"

Character::Character(int x, int y, int tileSizeX, int tileSizeY, const sf::Texture& texture, const sf::Vector2f& pos):
x_(x), y_(y), tileSizeX_(tileSizeX), tileSizeY_(tileSizeY), pos_(pos) {
    sprite_.setTexture(texture);
    sprite_.setTextureRect(sf::IntRect(x, y, tileSizeX, tileSizeY));
    sprite_.setPosition(pos);

}

void Character::draw(sf::RenderTarget& rt) const {
    rt.draw(sprite_);
}
void Character::setDirection(const sf::Vector2f& dir) {
    vel_ = dir * speed_;
}
    
void Character::update(float dt) {
    pos_ += vel_ * dt;
    sprite_.setPosition(pos_);
}

sf::Sprite Character::getSprite() {
    return sprite_;
}
