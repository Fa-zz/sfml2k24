#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation();
    Animation(int x, int y, int width, int height, const sf::Texture& texture, bool still);
    void applyToSprite(sf::Sprite& s, bool left) const;
    void update(float dt);

private:
    void Advance();

    static constexpr int nFrames_ = 2;
    static constexpr float holdTime_ = 0.1f;
    const sf::Texture* texture_; // Store as pointer
    sf::IntRect frames_[nFrames_];
    int iFrame_ = 0;
    float time_ = 0.0f;
};