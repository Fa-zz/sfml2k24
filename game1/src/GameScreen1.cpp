#include "MainMenuState.hpp"
#include "GameScreen1.hpp"
#include <SFML/Window/Event.hpp>

GameScreen1::GameScreen1(std::shared_ptr<Context> &context)
    : m_context(context), window_(*(m_context->m_window)), player_(*(m_context->m_player)) {
        cout << "GameScreen1 constructor called" << endl;
        // m_context->m_gui->initHighlight();
        width_ = 50;
        height_ = 25;
        m_context->m_world->genTiles(height_, width_);
        // view.setCenter((5) * 16, (5) * 16);
        view_ = m_context->m_window->getView();
        view_.setSize(view_.getSize().x / 8, view_.getSize().y / 8);
        // window_.setView(view_);
        // m_context->m_gui->setWindowSize(m_context->m_window->getSize());
        // m_context->m_gui->initMainMenuElems();
        // m_context->m_gui->setDrawingMainMenu(true);
}

void GameScreen1::pause() {
    isPaused_ = true;
}

void GameScreen1::start() {
    isPaused_ = false;
    view_ = m_context->m_window->getView();
    view_.setSize(view_.getSize().x / 8, view_.getSize().y / 8);
}

GameScreen1::~GameScreen1() { }

void GameScreen1::init() { }

void GameScreen1::loop(const sf::Time& deltaTime) {
    if (!isPaused_) {
        render();
        processInput();
        update(deltaTime);
    }
}

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
                    reset();
                    m_context->m_states->Add(std::make_unique<MainMenuState>(m_context), false);
                    break;
                // case sf::Keyboard::P:
                //     break;
            }
        }

        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition( window_ );
            // mousePosF_ = sf::Vector2f( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
            sf::Vector2f worldPos = window_.mapPixelToCoords(mousePos);
            // m_context->m_gui->hoveringOverObject(sf::Vector2f(mousePosF.x / 16, mousePosF.x / 16));
            // cout << "World pos x: " << worldPos.x << " world pos y: " << worldPos.y << endl;
            highlightX_ = worldPos.x / 16;
            highlightY_ = worldPos.y / 16;
            // cout << "high x: " << highlightX_ << " high y: " << highlightY_ << endl;
            m_context->m_gui->setHighlightPos(highlightX_, highlightY_);


        }
    }
}

void GameScreen1::update(const sf::Time &deltaTime) {
        float dt = deltaTime.asSeconds();
        m_context->m_cManager->setPosWithoutCollisionTiles(player_, dt, width_, height_);
        m_context->m_player->setDirection();
        m_context->m_player->resetDir();
}

void GameScreen1::render() {
    cout << "In game screen1 render" << endl;
    m_context->m_gui->setDrawingHighlight(true);
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
            // currX_ = x;
            // currY_ = y;
            if (groundTile != nullptr) {
                groundTile->setSpritePos(x, y);
                window_.draw(groundTile->getSprite());
                // if (groundTile->getSprite().getGlobalBounds().contains( mousePosF_ )) {
                //     m_context->m_gui->setHighlightPos(currX_, currY_);
                // }
            }
        }
    }
    m_context->m_gui->renderGUIElems(window_);
    window_.display();

}

void GameScreen1::reset() {
    view_ = m_context->m_window->getDefaultView();
    m_context->m_window->setView(view_);
    m_context->m_gui->setDrawingHighlight(false);
}