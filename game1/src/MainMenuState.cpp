#include "MainMenuState.hpp"
#include "GameScreen1.hpp"
#include <SFML/Window/Event.hpp>

MainMenuState::MainMenuState(std::shared_ptr<Context> &context)
    : m_context(context), window_(*(m_context->m_window)) { 
        m_context->m_gui->setWindowSize(m_context->m_window->getSize());
        m_context->m_gui->initMainMenuElems();
        m_context->m_gui->setDrawingMainMenu(true);
}

void MainMenuState::pause() {
    isPaused_ = true;
}

void MainMenuState::start() {
    isPaused_ = false;
}

MainMenuState::~MainMenuState() { }

void MainMenuState::init() { }

void MainMenuState::processInput() {
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_context->m_states->PopAll();
        }
        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition( window_ );
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
            m_context->m_gui->hoveringOverMMPlayB(mousePosF);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition( window_ );
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
            if (m_context->m_gui->hoveringOverMMPlayB(mousePosF)) {
                m_context->m_states->Add(std::make_unique<GameScreen1>(m_context), true);
            }
        }
      }
    //     else if (event.type == sf::Event::KeyPressed)
    //     {
    //         switch (event.key.code)
    //         {
    //         case sf::Keyboard::Up:
    //         {
    //             if (!m_isPlayButtonSelected)
    //             {
    //                 m_isPlayButtonSelected = true;
    //                 m_isExitButtonSelected = false;
    //             }
    //             break;
    //         }
    //         case sf::Keyboard::Down:
    //         {
    //             if (!m_isExitButtonSelected)
    //             {
    //                 m_isPlayButtonSelected = false;
    //                 m_isExitButtonSelected = true;
    //             }
    //             break;
    //         }
    //         case sf::Keyboard::Return:
    //         {
    //             m_isPlayButtonPressed = false;
    //             m_isExitButtonPressed = false;

    //             if (m_isPlayButtonSelected)
    //             {
    //                 m_isPlayButtonPressed = true;
    //             }
    //             else
    //             {
    //                 m_isExitButtonPressed = true;
    //             }

    //             break;
    //         }
    //         default:
    //         {
    //             break;
    //         }
    //         }
    //     }
    // }
}

void MainMenuState::update(const sf::Time &deltaTime) {
}

void MainMenuState::render() {
    m_context->m_window->clear(sf::Color::Cyan);
    m_context->m_gui->renderGUIElems(window_);
    m_context->m_window->display();
}