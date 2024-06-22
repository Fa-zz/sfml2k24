#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "MainMenuState.hpp"

Game::Game():m_context(std::make_shared<Context>()) {
    sf::Vector2i res1 = {1440, 900};
    sf::Vector2i res2 = {800, 600};
    m_context->m_window->create(sf::VideoMode(res2.x,res2.y), "game", sf::Style::Close);
    m_context->m_states->Add(std::make_unique<MainMenuState>(m_context));
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
                m_context->m_states->GetCurrent()->processInput();
                m_context->m_states->GetCurrent()->update(TIME_PER_FRAME);
                m_context->m_states->GetCurrent()->render();
            } else {
                m_context->m_window->close();
            }
        }
    }
}