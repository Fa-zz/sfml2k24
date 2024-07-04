// TileInfobox.hpp
#pragma once
#include <memory>
#include "State.hpp"
#include "StateMachine.hpp"
#include "GUI.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TileInfobox : public Engine::State {
public:
    TileInfobox(sf::Font font, float windowSizeX, float windowSizeY, int data, std::shared_ptr<GUIContext> &gui_context);

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

    ~TileInfobox();

private:
    std::shared_ptr<GUIContext> gui_context_;
    sf::Font font_;
    float windowSizeX_;
    float windowSizeY_;
    int data_;
    float mousePosX_;
    float mousePosY_;
    bool isPaused_ = false;

    sf::RectangleShape* infoBox_;
    sf::Text closeText_;
    sf::Text infoText_;
    sf::Text optionText_;
    std::vector<sf::Text*> optionsText_;

    void initClose();
};
