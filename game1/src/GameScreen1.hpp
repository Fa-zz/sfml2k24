#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "GUI.hpp"
#include "Character.hpp"
#include "Data.hpp"

class GameScreen1 : public Engine::State {
public:
    GameScreen1(std::shared_ptr<Context> &context);
    ~GameScreen1();

    void init() override;
    void pause() override;
    void start() override;
    void processInput() override;
    void update(const sf::Time& deltaTime) override;
    void render() override;
private:
    std::shared_ptr<Context> m_context;
    sf::RenderWindow& window_;
    Character& player_;
    sf::View view_;
    int width_, height_;
    bool isPaused_;
};