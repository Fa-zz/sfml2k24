#pragma once
#include <memory>
#include "Data.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
// #include "GUI.hpp"
#include "Textlink.hpp"
#include "Person.hpp"
// #include "GameMaster.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class Infobox : public Engine::State {
public:
    // Infobox(sf::Font font, float windowSizeX, float windowSizeY, int data, std::shared_ptr<GUIContext> &gui_context);
    Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxType);
    // Infobox(int charSize, sf::Font font, unordered_map<int, Person*>* personMap_);
    Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxType, string locType);
    Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxType, string locType, int* tileStats, int* tileMissions);

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
    void createInfobox();
    void setInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp);
    vector<string> getData();
    void setPopulation(string people);
    void setMissions(int* missionsArr);
    void setMissionInfo(string mission, string danger, string days);
    void setLoc(string loc);
    // void setDangerInfo(string danger);
    // void helloWorld(int x);

    ~Infobox();

private:
    // std::shared_ptr<GUIContext> gui_context_;
    string infoboxType_, locType_, currMission_ = "Placeholder";
    int* tileStats_;
    int* tileMissions_;
    // unordered_map<int, Person*>& personMap_;
    int charSize_;
    sf::Font font_;
    float windowSizeX_;
    float windowSizeY_;
    // int data_;
    float mousePosX_, mousePosY_;
    bool clicked_ = false;
    bool isPaused_ = false;
    bool scrollableBody_ = false, reachedEndOfScroll_ = false, scrollableLinks_ = false;
    bool scrollDown_ = false;
    bool scrollUp_ = false;
    string danger_, days_, peopleString_;

    sf::RectangleShape* infoboxRect_;
    sf::Text headerText_, bodyText_, scrollText_;
    // sf::Text optionText_;
    // std::vector<Textlink*> options_;
    vector<Textlink*> links_;
    string clickedLink_;
    string clickedOnClick_;
    // int clickedIndex_;
    int selectedIndex_;
    vector<string> linkData_;
    // string linkData_;
    vector<string> scrollTextVec_;
    vector<Textlink*> scrollLinksVec_;
    int startingLine_ = 0;
    int endingLine_ = 9;
    int startingLink_ = 0;
    int endingLink_ = 9;

    bool drawScrollText_ = false, readyToDraw_ = false;
    void initClose(); 
    void createBox();
    void createCloseLink();
    void initHeaderText();
    void createMissionsLink();
    void initBodyText();
    void createScrollText();
    string replaceIntroText();
    string replaceText(string stringToReplace, string placeHolderText, string replaceWith);
    string replaceBodyText(string replaceLoc, string replaceFood, string replaceSurvivors, string replaceZombies);
    sf::String wrapText(sf::String string);
    void makeScrollableBody(string scrollMe);
    void makeScrollableLinks(string links);
    string getBoundedString(int upd);
    void bindLinksVec(int upd);
};
