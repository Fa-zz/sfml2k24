#include "GUI.hpp"
#include "Infobox.hpp"
#include <iostream>

void GUI::initFont() {
    if (!font_.loadFromFile(Data::fontAssetPath)) {
        std::cerr << "Did Not Load Font" << std::endl;
    } else {
        topWindowText_.setFont(font_);
        mainMenuPlayButtonText_.setFont(font_);
        topBarText_.setFont(font_);
    }
    if (Data::useResX == Data::res1x && Data::useResY == Data::res1y) {
        charSize_ = 20;
    } else {
        charSize_ = 15;
    }
}

// void GUI::initTopAndBottomWindow() {
//     topWindow_ = new sf::RectangleShape();
//     topWindow_->setOutlineThickness(10);
//     topWindow_->setFillColor(sf::Color(32, 178, 170, 225));
//     topWindow_->setOutlineColor(sf::Color(70, 90, 70));

//     // topWindowPortrait_ = new sf::RectangleShape();
//     // topWindowPortrait_->setFillColor(sf::Color(255, 255, 255));

//     bottomWindow_ = new sf::RectangleShape();
//     bottomWindow_->setOutlineThickness(10);
//     bottomWindow_->setFillColor(sf::Color(32, 178, 170, 225));
//     bottomWindow_->setOutlineColor(sf::Color(143, 188, 143));

//     float windowWidth = windowSize_.x;
//     float windowHeight = windowSize_.y;
//     topWindow_->setSize(sf::Vector2f(windowWidth * 0.8f, windowHeight * 0.4f));
//     topWindow_->setPosition(windowWidth * 0.1f, windowHeight * 0.05f);
//     bottomWindow_->setSize(sf::Vector2f(topWindow_->getSize().x, topWindow_->getSize().y));
//     bottomWindow_->setPosition(windowWidth * 0.1f, windowHeight * 0.55f);

//     guiMap_["topWindow"] = topWindow_;
//     guiMap_["bottomWindow"] = bottomWindow_;
// }

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
    guiElems_.push_back(highlightedObject_);
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
    
    guiElems_.push_back(mainMenuPlayButton_);
    guiMap_["mainMenuPlayButton"] = mainMenuPlayButton_;
    // cout << windowSize_.x << " " << windowSize_.y << endl;
    // cout << mainMenuPlayButton_->getPosition().x << " " << mainMenuPlayButton_->getPosition().y << endl;
}

void GUI::initTopBar() {
    topBar_ = new sf::RectangleShape();
    topBar_->setFillColor(sf::Color(0,0,128));
    topBar_->setPosition(sf::Vector2f(0.f,0.f));
    // topBar_->setSize(sf::Vector2f( static_cast<float>(windowSize_.x) , static_cast<float>(windowSize_.y * 0.111f) )); // On 1440x900, this is 1440x100
    auto topBarLiterals = Data::calculateLiterals(1440, 100);
    topBar_->setSize(sf::Vector2f(windowSize_.x * topBarLiterals.first, windowSize_.x * topBarLiterals.second));
    {
    // x=30, y=30
    // int x = 15;
    // int offset = 0;
    // int increaseXBy = 150;
    // int y = 50;
    // cityName_ = "Baltimore";
    // population_ = "Pop: " + to_string(personCount_);
    // food_ = "Food: " + to_string(foodCount_);
    // mood_ = "Mood: " + to_string(moodCount_);
    // days_ = "Days: " + to_string(dayCount_);
    // tBCityName_.setFont(font_);
    // tBCityName_.setCharacterSize(charSize_);
    // tBCityName_.setString(cityName_);
    // tBPopulation_.setString(population_);
    // // tBPopulation_.setCharacterSize(charSize_);
    // // tBPopulation_.setFont(font_);
    // tBFood_.setString(food_);
    // // tBFood_.setCharacterSize(charSize_);
    // // tBFood_.setFont(font_);
    // tBMood_.setString(mood_);
    // // tBMood_.setCharacterSize(charSize_);
    // // tBMood_.setFont(font_);
    // tBDays_.setString(days_);
    // // tBDays_.setCharacterSize(charSize_);
    // // tBDays_.setFont(font_);

    // topBarTexts_.push_back(tBCityName_);
    // topBarTexts_.push_back(tBPopulation_);
    // topBarTexts_.push_back(tBFood_);
    // topBarTexts_.push_back(tBMood_);
    // topBarTexts_.push_back(tBDays_);
    // for (int i = 0; i < 4; i++) {
    //     auto literals = Data::calculateLiterals(x+=offset,y);
    //     topBarTexts_[i].setFont(font_);
    //     topBarTexts_[i].setCharacterSize(charSize_);
    //     topBarTexts_[i].setPosition(sf::Vector2f(windowSize_.x * literals.first, windowSize_.y * literals.second));
    //     offset+=increaseXBy;
    // }

    // auto cityNameLiterals = Data::calculateLiterals(x, y);
    // auto popLiterals = Data::calculateLiterals(x+=increaseXBy, y);
    // auto foodLiterals = Data::calculateLiterals(x+=increaseXBy, y);
    // auto moodLiterals = Data::calculateLiterals(x+=increaseXBy, y);
    // auto dayLiterals = Data::calculateLiterals(x+=increaseXBy, y);
    // tBCityName_.setPosition(sf::Vector2f(windowSize_.x * cityNameLiterals.first, windowSize_.x * cityNameLiterals.second));
    }

    topBarText_.setString("Baltimore   [P]op:" + to_string(personCount_) + "   [F]d:" + to_string(foodCount_) + "   [M]ood:" + to_string(moodCount_) + "   Day:" + to_string(dayCount_));
    // topBarText_.setString("placeholder");
    topBarText_.setCharacterSize(charSize_);
    topBarText_.setOrigin(topBarText_.getGlobalBounds().getSize() / 2.f + topBarText_.getLocalBounds().getPosition());
    topBarText_.setPosition(topBar_->getPosition() + (topBar_->getSize() / 2.f));
    // topBarText_.setPosition()
    guiElems_.push_back(topBar_);
    guiMap_["topBar"] = topBar_;
}

// void GUI::addIntroInfobox(string tileType) {
//     gui_context_->stateMachine_->Add(std::make_unique<Infobox>(charSize_, font_, windowSize_.x, windowSize_.y, Data::intro, tileType), false);
//     createInfobox();
// }

// void GUI::addTileInfobox(string tileStatus, string tileType, int* tileStats, int* tileMissions) {
//     // Ensure that gui_context_ and stateMachine_ are not null
//     if (!gui_context_ || !gui_context_->stateMachine_) {
//         throw std::runtime_error("GUI context or state machine not initialized");
//     }
//     gui_context_->stateMachine_->Add(std::make_unique<Infobox>(charSize_, font_, windowSize_.x, windowSize_.y, tileStatus, tileType, tileStats, tileMissions));
//     createInfobox();
// }

// void GUI::addInfobox(string boxType, unordered_map<int, Person*>& personMap) {
//     if (!gui_context_ || !gui_context_->stateMachine_) {
//         throw std::runtime_error("GUI context or state machine not initialized");
//     }
//     if (boxType == "") {
//         throw std::runtime_error("infobox type not set");
//     }
//     gui_context_->stateMachine_->Add(std::make_unique<Infobox>(charSize_, font_, windowSize_.x, windowSize_.y, boxType), false);
//     createInfobox();
// }

void GUI::initAll() {
    initFont();
    // initTopAndBottomWindow();
    initHighlight();
    initMainMenuElems();
    initTopBar();
    // stateMachine_ = std::make_unique<Engine::StateMachine>();

}
// CONSTRUCTOR AND DESTRUCTOR
// GUI::GUI():gui_context_(std::make_shared<GUIContext>()) {
//     initAll();
// }
GUI::GUI() {
    initAll();
}

// GUI::GUI(sf::Vector2u windowSize, int initChoice): windowSize_(windowSize) {
//     initFont();
//     if (initChoice == 0)
//         initMainMenuElems();
//     // initGUIElems();
// }

GUI::~GUI() {
    // for (auto& pair : guiMap_) {
    //     delete pair.second;
    // }
    // guiMap_.clear();
    for (int i = 0; i < guiElems_.size(); i++) {
        delete guiElems_[i];
    }
}

void GUI::pushInfobox(Infobox* infobox) { infoboxStack_.push_back(infobox); }

void GUI::popInfobox() { infoboxStack_.pop_back(); }

// void GUI::setDrawingTopAndBottomWindow(bool drawing) { drawTopAndBottomWindow_ = drawing; }
void GUI::setDrawingMainMenu(bool drawing) { drawMainMenu_ = drawing; }
void GUI::setDrawingHighlight(bool drawing) { drawHighlight_ = drawing; }
void GUI::setWindowSize(sf::Vector2u windowSize) { windowSize_ = sf::Vector2u{windowSize.x, windowSize.y}; }
void GUI::setHighlightPos(int x, int y) {
    // highlightedObject_->setPosition(x, y);
    highlightedObject_->setPosition(x * 16.f, y * 16.f);
    // cout << "new position: " << x * 16.f << " " << y * 16.f << endl;
}

int GUI::getCharSize() { return charSize_; }
sf::Font GUI::getFont() { return font_; }

bool GUI::hoveringOverMMPlayB(sf::Vector2f mouseCords) {
    if (mainMenuPlayButton_->getGlobalBounds().contains(mouseCords)) {
        mainMenuPlayButton_->setFillColor(sf::Color(75, 0, 110));
        return true;
    } else {
        mainMenuPlayButton_->setFillColor(sf::Color(255,223,0));
        return false;
    }
}
void GUI::hoveringOverTopBar(sf::Vector2f mouseCords) {
    // if (it->second->getGlobalBounds().contains(mouseCords)) {
    //     std::cout << "hovering over topBar" << std::endl;
    // }
}
void GUI::setDrawingTopBar(bool drawing) { drawTopBar_ = drawing; }
void GUI::setPersonCount(int personCount) { 
    personCount_ = personCount;
    if (guiMap_["topBar_"])
        delete guiMap_["topBar_"];
    initTopBar();
}
// void GUI::passInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp) {
//     gui_context_->stateMachine_->GetCurrent()->handleInput(x, y, clicked, scrollDown, scrollUp);

// }
// void GUI::passMissionsToInfobox(int* missionsArr) {
//     auto currentState = gui_context_->stateMachine_->GetCurrent();
//     if (currentState) {
//         if (Infobox* infoboxState = dynamic_cast<Infobox*>(currentState)) {
//             infoboxState->setMissions(missionsArr);
//         } else {
//             std::cerr << "Current state is not an Infobox" << std::endl;
//         }
//     } else {
//         std::cerr << "No current state" << std::endl;
//     }
// }
// void GUI::passLocToInfobox(string loc) {
//     auto currentState = gui_context_->stateMachine_->GetCurrent();
//     if (currentState) {
//         if (Infobox* infoboxState = dynamic_cast<Infobox*>(currentState)) {
//             infoboxState->setLoc(loc);
//         } else {
//             std::cerr << "Current state is not an Infobox" << std::endl;
//         }
//     } else {
//         std::cerr << "No current state" << std::endl;
//     }
// }
// void GUI::sendData() {
//     auto currentState = gui_context_->stateMachine_->GetCurrent();
//     if (currentState) {
//         if (Infobox* infoboxState = dynamic_cast<Infobox*>(currentState)) {
//             // infoboxState->helloWorld(42); // or whatever argument you need to pass
//         } else {
//             std::cerr << "Current state is not an Infobox" << std::endl;
//         }
//     } else {
//         std::cerr << "No current state" << std::endl;
//     }
// }
// void GUI::createInfobox() {
//     gui_context_->stateMachine_->ProcessStateChange(); // stateMan needs to process state change (i.e. push new state onto stack) b4 creating Ibox
//     auto currentState = gui_context_->stateMachine_->GetCurrent();
//     if (currentState) {
//         if (Infobox* infoboxState = dynamic_cast<Infobox*>(currentState)) {
//             infoboxState->createInfobox();
//         } else {
//             std::cerr << "Current state is not an Infobox" << std::endl;
//         }
//     } else {
//         std::cerr << "No current state" << std::endl;
//     }
// }
// void GUI::passPopulationToInfobox(unordered_map<int, Person*>& personMap) {
//     auto currentState = gui_context_->stateMachine_->GetCurrent();
//     if (currentState) {
//         if (Infobox* infoboxState = dynamic_cast<Infobox*>(currentState)) {
//             infoboxState->setPopulation(personMap); // or whatever argument you need to pass
//         } else {
//             std::cerr << "Current state is not an Infobox" << std::endl;
//         }
//     } else {
//         std::cerr << "No current state" << std::endl;
//     }
// }
// string GUI::getClickData() {
//     return gui_context_->stateMachine_->GetCurrent()->getData();
// }

// bool GUI::getGUIStackEmpty() {
//     return gui_context_->stateMachine_->IsEmpty();
// }

// void GUI::popCurrentState() {
//     gui_context_->stateMachine_->PopCurrent();
// }

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
        // for (int i = 0; i < topBarTexts_.size(); i++) {
        //     rt.draw(topBarTexts_[i]);
        // }
    }
    // if (drawTopAndBottomWindow_) {
    //     rt.draw(*topWindow_);
    //     //rt.draw(*topWindowPortrait_);
    //     rt.draw(*bottomWindow_);
    // }

    // gui_context_->stateMachine_->ProcessStateChange();

    // if (!gui_context_->stateMachine_->IsEmpty()) {
    //     gui_context_->stateMachine_->GetCurrent()->loop(rt);
    if (!(infoboxStack_.empty()))
        infoboxStack_.back()->loop(rt);
}

