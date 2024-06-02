#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

class Character {
public:
    Character(int x_, int y_, int tileSizeX_, int tileSizeY_, const sf::Texture& texture, const sf::Vector2f& pos);
    void draw(sf::RenderTarget& rt) const;
    void setDirection();
    void update(float dt);
    void setPos(sf::Vector2f newPos);
    sf::Sprite getSprite();
    sf::Vector2f getPos();
    sf::Vector2f getVel();
    sf::Vector2f getDir();
    void addDir(sf::Vector2f addDir);
    void resetDir();

private:
    int x_; // x: x coordinate of sprite on texture png
    int y_; // y: y coordinate of sprite on texture png
    int tileSizeX_; // tileSizeX: Size of tile in x direction
    int tileSizeY_; // tileSizeY: Size of tile in y direction

    enum class AnimationIndex {
        StandingStillUp,
        StandingStillDown,
        StandingStillHoriz,
        WalkingUp,
        WalkingDown,
        WalkingHoriz,
        Count
    };

    static constexpr float speed_ = 100.0f;
    sf::Vector2f dir_ = {0.f, 0.f};
    sf::Vector2f pos_;
    sf::Vector2f vel_ = {0.0f, 0.0f};
    sf::Sprite sprite_;
    Animation animations_[int(AnimationIndex::Count)];
    AnimationIndex curAnimation_ = AnimationIndex::StandingStillDown;
    bool standingStill_ = true; // Properly initialize
    bool walkingLeft_ = false;  // Properly initialize
};