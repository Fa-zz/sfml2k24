#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "MainMenuState.hpp"

Game::Game():m_context(std::make_shared<Context>()) {
    m_context->m_window->create(sf::VideoMode(DataSettings::res2x,DataSettings::res2y), "game", sf::Style::Close);
    m_context->m_states->Add(std::make_unique<MainMenuState>(m_context));
    m_context->m_gui->initAll();
}

Game::~Game() { }

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;
    while (m_context->m_window->isOpen()) {
        timeSinceLastFrame += clock.restart();
        // cout << "time since last frame: " << timeSinceLastFrame.asMilliseconds() << endl;
        while (timeSinceLastFrame > TIME_PER_FRAME) {
            timeSinceLastFrame -= TIME_PER_FRAME;

            m_context->m_states->ProcessStateChange();

            if (!m_context->m_states->IsEmpty()) {
                m_context->m_states->GetCurrent()->loop(TIME_PER_FRAME);
                // m_context->m_states->GetCurrent()->processInput();
                // m_context->m_states->GetCurrent()->update(TIME_PER_FRAME);
                // m_context->m_states->GetCurrent()->render();
            } else {
                m_context->m_window->close();
            }
        }
    }
}