#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
// #include "AssetMan.hpp"
#include "StateMachine.hpp"
#include "GUI.hpp"
#include <iostream>
using namespace std;

struct Context {
    // std::unique_ptr<Engine::AssetMan> m_assets;
    std::unique_ptr<Engine::StateMachine> m_states;
    std::unique_ptr<sf::RenderWindow> m_window;
    std::unique_ptr<GUI> m_gui;

    Context()
    {
        // m_assets = std::make_unique<Engine::AssetMan>();
        m_states = std::make_unique<Engine::StateMachine>();
        m_window = std::make_unique<sf::RenderWindow>();
        m_gui = std::make_unique<GUI>();
    }
};

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    std::shared_ptr<Context> m_context;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
};