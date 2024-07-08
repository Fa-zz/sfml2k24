#include "Textlink.hpp"

Textlink::Textlink(string stringText, sf::Font font, int size, string onClick): font_(font), onClick_(onClick) {
    text_.setFont(font_);
    text_.setCharacterSize(size);
    text_.setString(stringText);
    // text_.setFillColor(sf::Color::Red);
    text_.setStyle(sf::Text::Underlined);
}

Textlink::~Textlink() {

}

sf::Text Textlink::getText() {
    return text_;
}

string Textlink::getOnClick() {
    return onClick_;
}

void Textlink::setPosition(float x, float y) {
    text_.setPosition(x, y);
}

void Textlink::setUnderline() { text_.setStyle(sf::Text::Underlined); }
void Textlink::setColor(int i) { 
    if (i == 1) {
        text_.setFillColor(sf::Color::Blue); 
        selected_ = true;
    } else if (i == 0) {
        text_.setFillColor(sf::Color::White);
        selected_ = false;
    }
    }