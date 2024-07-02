#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "GUI.hpp"

class MainMenuState : public Engine::State {
public:
    MainMenuState(std::shared_ptr<Context> &context);
    ~MainMenuState();

    void init() override;
    void loop(const sf::Time &deltaTime) override;
    void pause() override;
    void start() override;
    void processInput() override;
    void update(const sf::Time& deltaTime) override;
    void render() override;
private:
    std::shared_ptr<Context> m_context;
    sf::RenderWindow& window_;
    bool isPaused_;
};