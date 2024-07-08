#pragma once
#include "SFML/Graphics.hpp"
#include "StateMachine.hpp"
#include "State.hpp"
#include <vector>
#include <unordered_map>
using namespace std;

struct GUIContext {
    std::unique_ptr<Engine::StateMachine> stateMachine_;
    GUIContext() {
        stateMachine_ = std::make_unique<Engine::StateMachine>();
    }
};

class GUI {
public:
    GUI();
    GUI(sf::Vector2u windowSize, int initChoice);
    ~GUI();
    void initAll();
    void initMainMenuElems();
    void initHighlight();
    void initTopBar();
    void initInfobox(int data);
    void setWindowSize(sf::Vector2u windowSize);
    void setDrawingTopAndBottomWindow(bool drawing);
    void setDrawingMainMenu(bool drawing);
    void setDrawingHighlight(bool drawing);
    void setHighlightPos(int x, int y);
    void setDrawingTopBar(bool drawing);
    void setMouseInfo(float x, float y, bool clicked, string linkData[]);
    bool getGUIStackEmpty();
    void popCurrentState();
    bool hoveringOverMMPlayB(sf::Vector2f mouseCords);
    void hoveringOverObject(sf::Vector2i drawCords);
    void renderGUIElems(sf::RenderTarget& rt);
    void renderHUDElems(sf::RenderTarget& rt);
private:
    std::shared_ptr<GUIContext> gui_context_;
    // std::shared_ptr<Engine::StateMachine> stateMachine_;
    std::unique_ptr<Engine::StateMachine> stateMachine_;
    sf::Vector2u windowSize_;
    sf::Font font_;
    sf::Text topWindowText_;
    sf::Text topBarText_;
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

    // bool drawTopAndBottomWindow_;
    bool drawMainMenu_;
    // bool hoveringMMStartB_;
    bool drawHighlight_;
    bool drawTopBar_;

    void initFont();
    // void initGUIElems();
    // void initTopAndBottomWindow();
};