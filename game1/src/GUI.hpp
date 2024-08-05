#pragma once
#include "SFML/Graphics.hpp"
#include "Data.hpp"
// #include "StateMachine.hpp"
// #include "State.hpp"
#include "Infobox.hpp"
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// struct GUIContext {
//     std::unique_ptr<Engine::StateMachine> stateMachine_;
//     GUIContext() {
//         stateMachine_ = std::make_unique<Engine::StateMachine>();
//     }
// };

class GUI {
public:
    GUI();
    // GUI(sf::Vector2u windowSize, int initChoice);
    ~GUI();
    void initAll();
    void initMainMenuElems();
    void initHighlight();
    void initTopBar();
    // void addIntroInfobox(string tileType);
    // void addTileInfobox(string tileStatus, string tileType, int* tileStats, int* tileMissions);
    // void addInfobox(string boxType, unordered_map<int, Person*>& personMap);
    void pushInfobox(Infobox* infobox);
    void popInfobox();
    void setWindowSize(sf::Vector2u windowSize);
    void setDrawingTopAndBottomWindow(bool drawing);
    void setDrawingMainMenu(bool drawing);
    void setDrawingHighlight(bool drawing);
    void setHighlightPos(int x, int y);
    void setDrawingTopBar(bool drawing);
    void setPopNum(int popNum);
    // void passInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp);
    // void passMissionsToInfobox(int* missionsArr);
    // void passLocToInfobox(string loc);
    // void passPopulationToInfobox(unordered_map<int, Person*>& personMap);
    // void sendData();
    // void createInfobox();
    // string getClickData();
    // bool getGUIStackEmpty();
    // void popCurrentState();
    int getCharSize();
    sf::Font getFont();
    bool hoveringOverMMPlayB(sf::Vector2f mouseCords);
    void hoveringOverTopBar(sf::Vector2f mouseCords);
    // void hoveringOverObject(sf::Vector2i drawCords);
    void renderGUIElems(sf::RenderTarget& rt);
    void renderHUDElems(sf::RenderTarget& rt);
private:
    // std::shared_ptr<GUIContext> gui_context_;
    // std::shared_ptr<Engine::StateMachine> stateMachine_;
    // std::unique_ptr<Engine::StateMachine> stateMachine_;
    sf::Vector2u windowSize_;
    sf::Font font_;
    int charSize_;
    int personCount_ = 0, foodCount_ = 100, moodCount_ = 100, dayCount_ = 0;
    sf::Text topWindowText_;
    // string cityName_, population_, food_, mood_, days_;
    // sf::Text tBCityName_, tBPopulation_, tBFood_, tBMood_, tBDays_, 
    sf::Text topBarText_;
    // vector<sf::Text> topBarTexts_;
    // sf::Texture windowTexture_;
    // sf::Sprite topWindowLeft_;
    // sf::Sprite topWindowRight_;
    sf::RectangleShape* topWindow_;
    sf::RectangleShape* topWindowPortrait_;
    sf::RectangleShape* bottomWindow_;
    sf::Text mainMenuPlayButtonText_;
    sf::RectangleShape* mainMenuPlayButton_;
    sf::RectangleShape* highlightedObject_;
    sf::RectangleShape* topBar_;
    unordered_map<string, sf::RectangleShape*> guiMap_;
    vector<sf::RectangleShape*> guiElems_;
    vector<Infobox*> infoboxStack_;
    // Infobox* currInfobox_ = nullptr;

    // bool drawTopAndBottomWindow_;
    bool drawMainMenu_;
    // bool hoveringMMStartB_;
    bool drawHighlight_;
    bool drawTopBar_;

    void initFont();
    // void initGUIElems();
    // void initTopAndBottomWindow();
};