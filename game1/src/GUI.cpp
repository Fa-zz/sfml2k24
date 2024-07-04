#include "GUI.hpp"
#include <iostream>

void GUI::initFont() {
    if (!font_.loadFromFile("assets/prstartk.ttf")) {
        std::cerr << "Did Not Load Font" << std::endl;
    } else {
        topWindowText_.setFont(font_);
        mainMenuPlayButtonText_.setFont(font_);
        topBarText_.setFont(font_);
    }
}

void GUI::initTopAndBottomWindow() {
    topWindow_ = new sf::RectangleShape();
    topWindow_->setOutlineThickness(10);
    topWindow_->setFillColor(sf::Color(32, 178, 170, 225));
    topWindow_->setOutlineColor(sf::Color(70, 90, 70));

    // topWindowPortrait_ = new sf::RectangleShape();
    // topWindowPortrait_->setFillColor(sf::Color(255, 255, 255));

    bottomWindow_ = new sf::RectangleShape();
    bottomWindow_->setOutlineThickness(10);
    bottomWindow_->setFillColor(sf::Color(32, 178, 170, 225));
    bottomWindow_->setOutlineColor(sf::Color(143, 188, 143));

    float windowWidth = windowSize_.x;
    float windowHeight = windowSize_.y;
    topWindow_->setSize(sf::Vector2f(windowWidth * 0.8f, windowHeight * 0.4f));
    topWindow_->setPosition(windowWidth * 0.1f, windowHeight * 0.05f);
    bottomWindow_->setSize(sf::Vector2f(topWindow_->getSize().x, topWindow_->getSize().y));
    bottomWindow_->setPosition(windowWidth * 0.1f, windowHeight * 0.55f);

    guiMap_["topWindow"] = topWindow_;
    guiMap_["bottomWindow"] = bottomWindow_;
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

    // guiContainer_.push_back(highlightedObject_);
    guiMap_["highlightedObject"] = highlightedObject_;
}

void GUI::initMainMenuElems() {
    mainMenuPlayButton_ = new sf::RectangleShape();
    
    mainMenuPlayButton_->setFillColor(sf::Color(255,223,0));
    mainMenuPlayButton_->setSize(sf::Vector2f(windowSize_.x * 0.25f, windowSize_.y * 0.09f));
    mainMenuPlayButton_->setPosition(windowSize_.x * 0.375f, windowSize_.y * 0.59f);

    mainMenuPlayButtonText_.setString("Play!");
    mainMenuPlayButtonText_.setCharacterSize(24);
    mainMenuPlayButtonText_.setOrigin(mainMenuPlayButtonText_.getGlobalBounds().getSize() / 2.f + mainMenuPlayButtonText_.getLocalBounds().getPosition());
    mainMenuPlayButtonText_.setPosition(mainMenuPlayButton_->getPosition() + (mainMenuPlayButton_->getSize() / 2.f));
    
    // guiContainer_.push_back(mainMenuPlayButton_);
    guiMap_["mainMenuPlayButton"] = mainMenuPlayButton_;
    // cout << windowSize_.x << " " << windowSize_.y << endl;
    // cout << mainMenuPlayButton_->getPosition().x << " " << mainMenuPlayButton_->getPosition().y << endl;
}

void GUI::initTopBar() {
    topBar_ = new sf::RectangleShape();
    topBar_->setFillColor(sf::Color(0,0,0));
    topBar_->setPosition(sf::Vector2f(0.f,0.f));
    topBar_->setSize(sf::Vector2f( static_cast<float>(windowSize_.x) , static_cast<float>(windowSize_.y * 0.111f) )); // On 1440x900, this is 1440x100
    
    topBarText_.setString("Baltimore   Pop:0   Fd:100   Mood:100   Day:0");
    topBarText_.setCharacterSize(12);
    topBarText_.setOrigin(topBarText_.getGlobalBounds().getSize() / 2.f + topBarText_.getLocalBounds().getPosition());
    topBarText_.setPosition(topBar_->getPosition() + (topBar_->getSize() / 2.f));

    guiMap_["topBar"] = topBar_;
}

void GUI::initInfobox(int data) {
    stateMachine_->Add(std::make_unique<TileInfobox>(font_, windowSize_.x, windowSize_.y, data));
}

void GUI::initAll() {
    initFont();
    initTopAndBottomWindow();
    initHighlight();
    initMainMenuElems();
    initTopBar();
    stateMachine_ = std::make_unique<Engine::StateMachine>();

}
// CONSTRUCTOR AND DESTRUCTOR
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
    for (auto& pair : guiMap_) {
        delete pair.second;
    }
    guiMap_.clear();
}

void GUI::createTopAndBottomWindow() {
    // float windowWidth = windowSize_.x;
    // float windowHeight = windowSize_.y;
    // topWindow_->setSize(sf::Vector2f(windowWidth * 0.8f, windowHeight * 0.4f));
    // topWindow_->setPosition(windowWidth * 0.1f, windowHeight * 0.05f);
    // bottomWindow_->setSize(sf::Vector2f(topWindow_->getSize().x, topWindow_->getSize().y));
    // bottomWindow_->setPosition(windowWidth * 0.1f, windowHeight * 0.55f);
    // topWindowPortrait_->setSize(sf::Vector2f(windowWidth * 0.15f, windowHeight * 0.3f));
    // topWindowPortrait_->setPosition(windowWidth * 0.9f - topWindowPortrait_->getSize().x, windowHeight * 0.05f);
    return;
}

void GUI::setDrawingTopAndBottomWindow(bool drawing) { drawTopAndBottomWindow_ = drawing; }
void GUI::setDrawingMainMenu(bool drawing) { drawMainMenu_ = drawing; }
void GUI::setDrawingHighlight(bool drawing) { drawHighlight_ = drawing; }
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
void GUI::setDrawingTopBar(bool drawing) { drawTopBar_ = drawing; }

void GUI::renderGUIElems(sf::RenderTarget& rt) {
    if (drawMainMenu_) {
        rt.draw(*guiMap_["mainMenuPlayButton"]);
        rt.draw(mainMenuPlayButtonText_);
    }
    if (drawHighlight_) {
        rt.draw(*guiMap_["highlightedObject"]);
    }
}

void GUI::renderHUDElems(sf::RenderTarget& rt) {
    if (drawTopBar_) {
        rt.draw(*guiMap_["topBar"]);
        rt.draw(topBarText_);
    }
    if (drawTopAndBottomWindow_) {
        rt.draw(*topWindow_);
        //rt.draw(*topWindowPortrait_);
        rt.draw(*bottomWindow_);
    }

    stateMachine_->ProcessStateChange();

    if (!stateMachine_->IsEmpty()) {
        stateMachine_->GetCurrent()->loop(rt);
    }
}

