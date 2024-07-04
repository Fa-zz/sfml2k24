#include "TileInfobox.hpp"

// TileInfobox::TileInfobox(sf::Font font, float windowSizeX, float windowSizeY, unordered_map<string,int> data) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data) {
TileInfobox::TileInfobox(sf::Font font, float windowSizeX, float windowSizeY, int data) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data) {

}

void TileInfobox::pause() {
    isPaused_ = true;
}

void TileInfobox::start() {
    isPaused_ = false;
}

void TileInfobox::init() {
    // infotxt_.setFont(font_);
    Infobox_ = new sf::RectangleShape();
    Infobox_->setOutlineThickness(10);
    Infobox_->setFillColor(sf::Color(32, 178, 170));
    Infobox_->setOutlineColor(sf::Color(70, 90, 70));

    Infobox_->setSize(sf::Vector2f(windowSizeX_ * .6944f, windowSizeY_ * .6667f));
    Infobox_->setPosition(windowSizeX_ * .1388f, windowSizeY_ * .111f);

}

void TileInfobox::loop(sf::RenderTarget& rt) {
    if (!isPaused_) {
        render(rt);
        processInput();
        update();
    }
}

TileInfobox::~TileInfobox() {
    if (Infobox_)
        delete Infobox_;
    for (auto & element : optionstxt_) {
        delete element;
    }
}

void TileInfobox::processInput() {

}

void TileInfobox::update() {

}

void TileInfobox::render(sf::RenderTarget& rt) {
    rt.draw(*Infobox_);
}

void TileInfobox::loop(const sf::Time& deltaTime) { }
void TileInfobox::update(const sf::Time& deltaTime) { }
void TileInfobox::render() { }
