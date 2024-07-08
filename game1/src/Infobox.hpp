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
#include <iostream>
using namespace std;

class Infobox : public Engine::State {
public:
    Infobox(sf::Font font, float windowSizeX, float windowSizeY, int data, std::shared_ptr<GUIContext> &gui_context);

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
    void mouseInfo(float x, float y, bool clicked, string data[]);
    void getData(string data[]);

    ~Infobox();

private:
    string infoboxType;
    std::shared_ptr<GUIContext> gui_context_;
    sf::Font font_;
    float windowSizeX_;
    float windowSizeY_;
    int data_;
    float mousePosX_;
    float mousePosY_;
    bool clicked_ = false;
    bool isPaused_ = false;

    sf::RectangleShape* infoBox_;
    sf::Text closeText_;
    sf::Text infoText_;
    // sf::Text optionText_;
    // std::vector<sf::Text*> optionsText_;
    vector<Textlink*> links_;
    string clickedLink_;
    string clickedOnClick_;
    // int clickedIndex_;
    int selectedIndex_;
    string linkData_[2];

    void initClose();
};
