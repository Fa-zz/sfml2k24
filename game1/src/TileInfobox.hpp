#pragma once

// #include "Infobox.hpp"
#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TileInfobox : public Engine::State {
public:
    TileInfobox(sf::Font font, float windowSizeX, float windowSizeY, int data);

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
    sf::Font font_;
    float windowSizeX_;
    float windowSizeY_;
    int data_;
    float mousePosX_;
    float mousePosY_;
    bool isPaused_ = false;

    sf::RectangleShape* Infobox_;
    std::vector<sf::Text*> optionstxt_;
};
