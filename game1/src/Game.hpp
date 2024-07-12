/*
    Game class creates and populates the Context structure which is a shared ptr to a series of unique ptrs
    that contain "modules" that can be accessed in each of the game's states

    Seeds random, contains the main game loop, calculates game time

    Creates the landing state, calls process state change and loop functions for each state
*/

#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "StateMachine.hpp"
#include "GUI.hpp"
#include "World.hpp"
#include "GameMaster.hpp"
#include "Character.hpp"
#include "CharacterManager.hpp"
#include "Data.hpp"
#include <iostream>
#include <cstdlib> 
#include <time.h> 
using namespace std;

struct Context {
    std::unique_ptr<Engine::StateMachine> m_states;
    std::unique_ptr<sf::RenderWindow> m_window;
    std::unique_ptr<GUI> m_gui;
    // std::unique_ptr<World> m_world;
    std::unique_ptr<Character> m_player;
    std::unique_ptr<CharacterManager> m_cManager;
    std::unique_ptr<GameMaster> m_gameMaster;

    Context() {
        m_states = std::make_unique<Engine::StateMachine>();
        m_window = std::make_unique<sf::RenderWindow>();
        m_gui = std::make_unique<GUI>();
        // m_world = std::make_unique<World>();
        m_player = std::make_unique<Character>(0,0,16,16,sf::Vector2f(20,20));
        m_cManager = std::make_unique<CharacterManager>();
        m_gameMaster = std::make_unique<GameMaster>(*m_gui);

    }
};

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    std::shared_ptr<Context> m_context;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
};