#include "GUI.hpp"
#include <iostream>

void GUI::initFont() {
    if (!font_.loadFromFile("assets/prstartk.ttf")) {
        std::cerr << "Did Not Load Font" << std::endl;
    } else {
        topWindowText_.setFont(font_);
        mainMenuPlayButtonText_.setFont(font_);
    }
}

void GUI::initTopAndBottomWindow() {
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

// void GUI::initGUIElems() {
//     initTopAndBottomWindow();
// }

void GUI::initHighlight() {
    highlightedObject_ = new sf::RectangleShape();
    highlightedObject_->setSize(sf::Vector2f(16.f,16.f));
    highlightedObject_->setOutlineThickness(1);
    highlightedObject_->setFillColor(sf::Color(0,0,0,0));
    highlightedObject_->setOutlineColor(sf::Color(255,255,0));

    guiContainer_.push_back(highlightedObject_);
    guiMap_["highlightedObject"] = highlightedObject_;
}

void GUI::initMainMenuElems() {
    mainMenuPlayButton_ = new sf::RectangleShape();
    mainMenuPlayButton_->setFillColor(sf::Color(255,223,0));
    mainMenuPlayButtonText_.setString("Play!");
    cout << "Windowsize x: " << windowSize_.x << " windowSize y: " << windowSize_.y << endl;
    mainMenuPlayButton_->setSize(sf::Vector2f(windowSize_.x * 0.25f, windowSize_.y * 0.09f));
    mainMenuPlayButton_->setPosition(windowSize_.x * 0.375f, windowSize_.y * 0.59f);
    mainMenuPlayButtonText_.setCharacterSize(24);

    mainMenuPlayButtonText_.setOrigin(mainMenuPlayButtonText_.getGlobalBounds().getSize() / 2.f + mainMenuPlayButtonText_.getLocalBounds().getPosition());
    mainMenuPlayButtonText_.setPosition(mainMenuPlayButton_->getPosition() + (mainMenuPlayButton_->getSize() / 2.f));
    
    guiContainer_.push_back(mainMenuPlayButton_);
    guiMap_["mainMenuPlayButton"] = mainMenuPlayButton_;
    // cout << windowSize_.x << " " << windowSize_.y << endl;
    // cout << mainMenuPlayButton_->getPosition().x << " " << mainMenuPlayButton_->getPosition().y << endl;

}

void GUI::initAll() {
    initFont();
    initHighlight();
    initMainMenuElems();
}

GUI::GUI() {
    initAll();
}

GUI::GUI(sf::Vector2u windowSize, int initChoice): windowSize_(windowSize) {
    initFont();
    if (initChoice == 0)
        initMainMenuElems();
    // initGUIElems();
}

GUI::~GUI() {
    cout << " GUI destructor called " << endl;
    // if (topWindow_)
    //     delete topWindow_;
    // if (topWindowPortrait_)
    //     delete topWindowPortrait_;
    // if (bottomWindow_)
    //     delete bottomWindow_;
    // for (sf::Text* text : textContainer_) {
    //     delete text;
    // }
    // for (sf::RectangleShape* rectangle : guiContainer_) {
    //     delete rectangle;
    // }
    for (auto& pair : guiMap_) {
        delete pair.second;
    }
    guiMap_.clear();
}

void GUI::createTopAndBottomWindow() {
    float windowWidth = windowSize_.x;
    float windowHeight = windowSize_.y;
    topWindow_->setSize(sf::Vector2f(windowWidth * 0.8f, windowHeight * 0.4f));
    topWindow_->setPosition(windowWidth * 0.1f, windowHeight * 0.05f);
    bottomWindow_->setSize(sf::Vector2f(topWindow_->getSize().x, topWindow_->getSize().y));
    bottomWindow_->setPosition(windowWidth * 0.1f, windowHeight * 0.55f);
    // topWindowPortrait_->setSize(sf::Vector2f(windowWidth * 0.15f, windowHeight * 0.3f));
    // topWindowPortrait_->setPosition(windowWidth * 0.9f - topWindowPortrait_->getSize().x, windowHeight * 0.05f);
}

void GUI::setDrawingTopAndBottomWindow(bool drawing) { drawTopAndBottomWindow_ = drawing; }
void GUI::setDrawingMainMenu(bool drawing) { drawMainMenu_ = drawing; }
void GUI::setDrawingHighlight(bool drawing) { 
    cout << "Highlight has been set to " << drawing << endl;
    drawHighlight_ = drawing; 
}
void GUI::setWindowSize(sf::Vector2u windowSize) { windowSize_ = sf::Vector2u{windowSize.x, windowSize.y}; }
void GUI::setHighlightPos(int x, int y) {
    // highlightedObject_->setPosition(x, y);
    highlightedObject_->setPosition(x * 16.f, y * 16.f);
    // cout << "new position: " << x * 16.f << " " << y * 16.f << endl;
}
bool GUI::hoveringOverMMPlayB(sf::Vector2f mouseCords) {
    if (mainMenuPlayButton_->getGlobalBounds().contains(mouseCords)) {
        mainMenuPlayButton_->setFillColor(sf::Color(75, 0, 110));
        return true;
    } else {
        mainMenuPlayButton_->setFillColor(sf::Color(255,223,0));
        return false;
    }
}

// void GUI::hoveringOverObject(sf::Vector2i drawCords) {
//     // cout << mouseCords.x << mouseCords.y << endl;
//     highlightedObject_->
// }

void GUI::renderGUIElems(sf::RenderTarget& rt) {
    if (drawMainMenu_) {
        // cout << "GUI.cpp: Drawing main menu" << endl;
        // cout << "button pos x: " << mainMenuPlayButton_->getPosition().x << endl;
        rt.draw(*guiMap_["mainMenuPlayButton"]);
        // rt.draw(*guiContainer_[0]);
        rt.draw(mainMenuPlayButtonText_);
    }
    if (drawHighlight_) {
        // cout << "GUI.cpp: drawing highlight" << endl;
        // rt.draw(*guiContainer_[1]);
        rt.draw(*guiMap_["highlightedObject"]);
    }
    if (drawTopAndBottomWindow_) {
        rt.draw(*topWindow_);
        //rt.draw(*topWindowPortrait_);
        rt.draw(*bottomWindow_);
    }
}

