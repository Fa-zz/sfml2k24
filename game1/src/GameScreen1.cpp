#include "MainMenuState.hpp"
#include "GameScreen1.hpp"
#include <SFML/Window/Event.hpp>

GameScreen1::GameScreen1(std::shared_ptr<Context> &context)
    : m_context(context), window_(*(m_context->m_window)), player_(*(m_context->m_player)) {
        cout << "GameScreen1 constructor called" << endl;
        width_ = 50;
        height_ = 25;
        m_context->m_world->genTiles(height_, width_);
        view_ = m_context->m_window->getView();
        view_.setSize(view_.getSize().x / 6, view_.getSize().y / 6);
        m_context->m_gui->setDrawingHighlight(true);
        m_context->m_gui->setDrawingTopBar(true);
}

void GameScreen1::pause() {
    isPaused_ = true;
}

void GameScreen1::start() {
    cout << " Game screen 1 start called " << endl;
    isPaused_ = false;
    view_ = m_context->m_window->getView();
    view_.setSize(view_.getSize().x / 6, view_.getSize().y / 6);
    m_context->m_gui->setDrawingHighlight(true);
    m_context->m_gui->setDrawingTopBar(true);
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

        // Update mouse position for both GUI and game states
        sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
        mousePosF_ = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        sf::Vector2f worldPos = window_.mapPixelToCoords(mousePos);
        highlightX_ = worldPos.x / 16;
        highlightY_ = worldPos.y / 16;

        if (m_context->m_gui->getGUIStackEmpty()) {
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::D:
                        m_context->m_player->addDir(sf::Vector2f{Data::playerSpeed, 0.f});
                        break;
                    case sf::Keyboard::A:
                        m_context->m_player->addDir(sf::Vector2f{-Data::playerSpeed, 0.f});
                        break;
                    case sf::Keyboard::W:
                        m_context->m_player->addDir(sf::Vector2f{0.f, -Data::playerSpeed});
                        break;
                    case sf::Keyboard::S:
                        m_context->m_player->addDir(sf::Vector2f{0.f, Data::playerSpeed});
                        break;
                    case sf::Keyboard::Enter:
                        reset();
                        m_context->m_states->Add(std::make_unique<MainMenuState>(m_context), false);
                        break;
                    case sf::Keyboard::P:
                        view_ = m_context->m_window->getDefaultView();
                        break;
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                m_context->m_gui->setHighlightPos(highlightX_, highlightY_);
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                m_context->m_gameMaster->initInfobox(highlightX_, highlightY_);
            }
        } else {
            if (event.type == sf::Event::MouseMoved) {
                m_context->m_gameMaster->infoboxMaster(mousePosF_.x, mousePosF_.y, false);
            } else if (event.type == sf::Event::MouseButtonPressed) {
                // Ensure mouse position is updated before processing click
                m_context->m_gameMaster->infoboxMaster(mousePosF_.x, mousePosF_.y, true);
            }
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
    window_.clear(sf::Color(134, 192, 108));
    float clampedCenterX;
    float clampedCenterY;
    Data::updateView(player_.getPos().x, player_.getPos().y, view_.getSize().x, view_.getSize().y, 16, 16, width_, height_, &clampedCenterX, &clampedCenterY);
    view_.setCenter(sf::Vector2f(clampedCenterX, clampedCenterY));
    
    // Set the view for the game objects (zoomed-in view)
    window_.setView(view_);

    // Render game objects
    sf::Vector2f center = view_.getCenter();
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
    m_context->m_gui->renderGUIElems(window_);

    // Set the view for HUD elements (default view)
    window_.setView(window_.getDefaultView());
    m_context->m_gui->renderHUDElems(window_);
    window_.setView(view_);

    window_.display();
}

void GameScreen1::reset() {
    view_ = m_context->m_window->getDefaultView();
    m_context->m_window->setView(view_);
    m_context->m_gui->setDrawingHighlight(false);
    m_context->m_gui->setDrawingTopBar(false);
}