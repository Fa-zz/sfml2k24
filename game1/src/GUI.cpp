#include "GUI.hpp"
#include <iostream>

void GUI::initFont() {
    if (!font_.loadFromFile("assets/prstart.ttf")) {
        std::cerr << "Did Not Load Font" << std::endl;
    } else {
        topWindowText_.setFont(font_);
    }
}

void GUI::initGUIElems() {
    topWindow_ = new sf::RectangleShape();
    topWindow_->setOutlineThickness(10);
    topWindow_->setFillColor(sf::Color(32, 178, 170, 225));
    topWindow_->setOutlineColor(sf::Color(70, 90, 70));

    topWindowPortrait_ = new sf::RectangleShape();
    topWindowPortrait_->setFillColor(sf::Color(255, 255, 255));

    bottomWindow_ = new sf::RectangleShape();
    bottomWindow_->setOutlineThickness(10);
    bottomWindow_->setFillColor(sf::Color(32, 178, 170, 225));
    bottomWindow_->setOutlineColor(sf::Color(143, 188, 143));
}

GUI::GUI() {
    initFont();
    initGUIElems();
}

GUI::~GUI() {
    delete topWindow_;
    delete topWindowPortrait_;
    delete bottomWindow_;
}

void GUI::renderGUIElems(sf::RenderTarget& rt, const sf::Vector2u& windowSize) {
    float windowWidth = windowSize.x;
    float windowHeight = windowSize.y;

    topWindow_->setSize(sf::Vector2f(windowWidth * 0.8f, windowHeight * 0.4f));
    topWindow_->setPosition(windowWidth * 0.1f, windowHeight * 0.05f);

    bottomWindow_->setSize(sf::Vector2f(topWindow_->getSize().x, topWindow_->getSize().y));
    bottomWindow_->setPosition(windowWidth * 0.1f, windowHeight * 0.55f);

    // topWindowPortrait_->setSize(sf::Vector2f(windowWidth * 0.15f, windowHeight * 0.3f));
    // topWindowPortrait_->setPosition(windowWidth * 0.9f - topWindowPortrait_->getSize().x, windowHeight * 0.05f);

    rt.draw(*topWindow_);
    //rt.draw(*topWindowPortrait_);
    rt.draw(*bottomWindow_);
}
