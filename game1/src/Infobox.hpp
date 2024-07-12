#pragma once
#include <memory>
#include "Data.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
#include "GUI.hpp"
#include "Textlink.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Infobox : public Engine::State {
public:
    // Infobox(sf::Font font, float windowSizeX, float windowSizeY, int data, std::shared_ptr<GUIContext> &gui_context);
    Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxStatus);
    Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxStatus, string infoboxType, int* tileStats, int* tileMissions);

    void init() override;
    void loop(const sf::Time& deltaTime);
    void loop(sf::RenderTarget& rt);
    void processInput() override;
    void update(const sf::Time& deltaTime);
    void update();
    void render() override;
    void render(sf::RenderTarget& rt);
    void pause() override;
    void start() override;
    void handleInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp);
    string getData();

    ~Infobox();

private:
    // std::shared_ptr<GUIContext> gui_context_;
    string infoboxStatus_, infoboxType_;
    int* tileStats_;
    int* tileMissions_;
    int charSize_;
    sf::Font font_;
    float windowSizeX_;
    float windowSizeY_;
    // int data_;
    float mousePosX_;
    float mousePosY_;
    bool clicked_ = false;
    bool isPaused_ = false;
    bool scrollable_ = false;
    bool scrollDown_ = false;
    bool scrollUp_ = false;

    sf::RectangleShape* infoboxRect_;
    sf::Text closeText_;
    sf::Text bodyText_;
    sf::Text scrollText_;
    // sf::Text optionText_;
    // std::vector<sf::Text*> optionsText_;
    vector<Textlink*> links_;
    string clickedLink_;
    string clickedOnClick_;
    // int clickedIndex_;
    int selectedIndex_;
    string linkData_;
    vector<string> bodyTextBackend_;
    int startingLine_ = 0;
    int endingLine_ = 9;

    void initClose(); 
    void createInfobox();
    void createCloseLink();
    void createMissionsLink();
    void initBodyText();
    void createScrollText();
    string replaceBodyText(string replaceLoc, string replaceFood, string replaceSurvivors, string replaceZombies);
    sf::String wrapText(sf::String string);
    void makeScrollable(string scrollMe);
    string getBoundedString(int upd);
};
