#include "TileInfobox.hpp"

// TileInfobox::TileInfobox(sf::Font font, float windowSizeX, float windowSizeY, unordered_map<string,int> data) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data) {
TileInfobox::TileInfobox(sf::Font font, float windowSizeX, float windowSizeY, int data, std::shared_ptr<GUIContext> &gui_context_) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data), gui_context_(gui_context_) {

}

void TileInfobox::pause() {
    isPaused_ = true;
}

void TileInfobox::start() {
    isPaused_ = false;
}

void TileInfobox::init() {
    infoText_.setFont(font_);
    infoBox_ = new sf::RectangleShape();
    infoBox_->setOutlineThickness(10);
    infoBox_->setFillColor(sf::Color(32, 178, 170));
    infoBox_->setOutlineColor(sf::Color(70, 90, 70));

    infoBox_->setSize(sf::Vector2f(windowSizeX_ * .6944f, windowSizeY_ * .6667f));
    infoBox_->setPosition(windowSizeX_ * .1388f, windowSizeY_ * 0.2222f);

    infoText_.setCharacterSize(20);
    infoText_.setString("This is a Church.\nFood: Low\nSurvivors: Medium\nZombies: High\n");
    infoText_.setPosition(windowSizeX_ * .277, windowSizeY_ * 0.30555);
    optionText_.setFont(font_);
    optionText_.setCharacterSize(20);
    optionText_.setString("See missions");
    optionText_.setPosition(windowSizeX_ * .309027f, windowSizeY_ * .7055f);
}

void TileInfobox::loop(sf::RenderTarget& rt) {
    if (!isPaused_) {
        render(rt);
        processInput();
        update();
    }
}

TileInfobox::~TileInfobox() {
    if (infoBox_)
        delete infoBox_;
    for (auto & element : optionsText_) {
        delete element;
    }
}

void TileInfobox::processInput() {

}

void TileInfobox::update() {

}

void TileInfobox::render(sf::RenderTarget& rt) {
    rt.draw(*infoBox_);
    rt.draw(infoText_);
    rt.draw(optionText_);
}

void TileInfobox::loop(const sf::Time& deltaTime) { }
void TileInfobox::update(const sf::Time& deltaTime) { }
void TileInfobox::render() { }
