#include "Animation.hpp"

Animation::Animation() = default;

Animation::Animation(int x, int y, int width, int height, const sf::Texture& texture, bool still) : texture_(&texture) {
    for (int i = 0; i < nFrames_; i++) {
        if (still) {
            frames_[i] = {x, y, width, height};
        } else {
            frames_[i] = {x + i * width, y, width, height};
        }
    }
}

void Animation::applyToSprite(sf::Sprite& s, bool left) const {
    s.setTexture(*texture_);
    s.setTextureRect(frames_[iFrame_]);

    // Set the origin to the center of the sprite to handle flipping
    if (left) {
        s.setOrigin(frames_[iFrame_].width, 0);
        s.setScale(-1.0f, 1.0f);
    } else {
        s.setOrigin(0, 0);
        s.setScale(1.0f, 1.0f);
    }
}

void Animation::update(float dt) {
    time_ += dt;
    while (time_ >= holdTime_) {
        time_ -= holdTime_;
        Advance();
    }
}

void Animation::Advance() {
    if (++iFrame_ >= nFrames_) {
        iFrame_ = 0;
    }
}
