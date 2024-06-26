#include "MainMenuState.hpp"
#include "GameScreen1.hpp"
#include <SFML/Window/Event.hpp>

GameScreen1::GameScreen1(std::shared_ptr<Context> &context)
    : m_context(context), window_(*(m_context->m_window)), player_(*(m_context->m_player)) {
        width_ = 50;
        height_ = 25;
        m_context->m_gui->setDrawingMainMenu(false);
        m_context->m_world->genTiles(height_, width_);
        view_ = window_.getView();
        // view.setCenter((5) * 16, (5) * 16);
        view_.setSize(view_.getSize().x / 4, view_.getSize().y / 4);
        window_.setView(view_);
        // m_context->m_gui->setWindowSize(m_context->m_window->getSize());
        // m_context->m_gui->initMainMenuElems();
        // m_context->m_gui->setDrawingMainMenu(true);
}

void GameScreen1::pause() {
    isPaused_ = true;
}

void GameScreen1::start() {
    isPaused_ = false;
}

GameScreen1::~GameScreen1() { }

void GameScreen1::init() { }

void GameScreen1::processInput() {
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_context->m_states->PopAll();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::D:
                    m_context->m_player->addDir(sf::Vector2f{DataSettings::playerSpeed,0.f});
                    break;
                case sf::Keyboard::A:
                    m_context->m_player->addDir(sf::Vector2f{-DataSettings::playerSpeed,0.f});
                    break;
                case sf::Keyboard::W:
                    m_context->m_player->addDir(sf::Vector2f{0.f,-DataSettings::playerSpeed});
                    break;
                case sf::Keyboard::S:
                    m_context->m_player->addDir(sf::Vector2f{0.f,DataSettings::playerSpeed});
                    break;
                case sf::Keyboard::Enter:
                    // DataSettings::myFunct();
                    break;
            }
        }

    //     if (event.type == sf::Event::MouseMoved) {
    //         sf::Vector2i mousePos = sf::Mouse::getPosition( window_ );
    //         sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
    //         m_context->m_gui->hoveringOverMMPlayB(mousePosF);
    //     }
    //     if (event.type == sf::Event::MouseButtonPressed) {
    //         sf::Vector2i mousePos = sf::Mouse::getPosition( window_ );
    //         sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
    //         if (m_context->m_gui->hoveringOverMMPlayB(mousePosF)) {
    //             m_context->m_states->Add(std::make_unique<GameScreen1>(m_context), true);
    //         }
    //     }
    // }
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
}

void GameScreen1::update(const sf::Time &deltaTime) {
    if (!isPaused_) {
        float dt = deltaTime.asSeconds();
        m_context->m_cManager->setPosWithoutCollision(player_, dt);
        m_context->m_player->setDirection();
        m_context->m_player->resetDir();

    }
}

void GameScreen1::render() {
    // m_context->m_window->clear(sf::Color::Cyan);
    // m_context->m_gui->renderGUIElems(window_);
    // m_context->m_window->display();
    window_.clear(sf::Color (134,192,108));
    float clampedCenterX;
    float clampedCenterY;
    DataSettings::updateView(player_.getPos().x, player_.getPos().y, view_.getSize().x, view_.getSize().y, 16, 16, width_, height_, &clampedCenterX, &clampedCenterY);
    view_.setCenter(sf::Vector2f(clampedCenterX, clampedCenterY));
    window_.setView(view_);

    sf::Vector2f center = view_.getCenter();
    // sf::Vector2f playerCenter = cMgr.getPlayerCenter();
    sf::Vector2f size = view_.getSize();
    float halfWidth = size.x / 2;
    float halfHeight = size.y / 2;

    int startX = std::max(0, static_cast<int>((center.x - halfWidth) / 16));
    int endX = std::min(width_, static_cast<int>((center.x + halfWidth) / 16) + 1);
    int startY = std::max(0, static_cast<int>((center.y - halfHeight) / 16));
    int endY = std::min(height_, static_cast<int>((center.y + halfHeight) / 16) + 1);
    
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            Terrain* groundTile = m_context->m_world->getGroundTileAtPos(y, x);
            if (groundTile != nullptr) {
                groundTile->setSpritePos(x, y);
                window_.draw(groundTile->getSprite());
            }
        }
    }
    cout << "Player center x: " << m_context->m_player->getPos().x << " " << m_context->m_player->getPos().y << endl;
    window_.display();

}