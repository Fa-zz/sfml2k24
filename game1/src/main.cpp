#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "Terrain.hpp"
#include "World.hpp"
#include "GUI.hpp"

void updateView(sf::View& view, const sf::RenderWindow& window, World& world, int tileWidth, int tileHeight, int worldWidth, int worldHeight) {
    sf::Vector2f playerCenter = world.getPlayerCenter();
    sf::Vector2f viewSize = view.getSize();
    float halfViewWidth = viewSize.x / 2.0f;
    float halfViewHeight = viewSize.y / 2.0f;

    // Define the view's bounds in the tile map
    float viewMinX = halfViewWidth;
    float viewMinY = halfViewHeight;
    float viewMaxX = worldWidth * tileWidth - halfViewWidth;
    float viewMaxY = worldHeight * tileHeight - halfViewHeight;

    // Clamp the view center to ensure it doesn't go outside the tile boundaries
    float clampedCenterX = std::max(viewMinX, std::min(playerCenter.x, viewMaxX));
    float clampedCenterY = std::max(viewMinY, std::min(playerCenter.y, viewMaxY));

    // Update the view center
    view.setCenter(clampedCenterX, clampedCenterY);
}

int main() {
    int tileWidth = 16;
    int tileHeight = 16;
    const int width = 50;
    const int height = 25;
    bool drawGUI = false;
    int res1x = 1440;
    int res1y = 900;
    int res2x = 600;
    int res2y = 800;
    sf::RenderWindow window(sf::VideoMode(res1x, res1y), "SFML game");

    World world;
    GUI gui;
    world.genTiles(height, width);

    sf::View view = window.getView();
    // cout << " view b4 division: " << view.getSize().x << " view y: " << view.getSize().y << endl;
    // view.setCenter((5) * 16, (5) * 16);
    view.setSize(view.getSize().x / 4, view.getSize().y / 4);
    // cout << " view after division: " << view.getSize().x << " view y: " << view.getSize().y << endl;
    window.setView(view);

    auto tp = chrono::steady_clock::now();

    // MAIN LOOP
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
                drawGUI = !drawGUI;
            }
        }

        float dt;
        const auto new_tp = std::chrono::steady_clock::now();
        dt = std::chrono::duration<float>( new_tp - tp ).count();
        tp = new_tp;
        
        sf::Vector2f dir = {0.f, 0.f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            dir.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            dir.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            dir.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dir.x += 1.0f;
        }
        world.updateCharacters(dir, dt);

        window.clear(sf::Color (134,192,108));

        window.setView(view); // Set the view before drawing

        sf::Vector2f center = view.getCenter();
        sf::Vector2f playerCenter = world.getPlayerCenter();
        sf::Vector2f size = view.getSize();
        float halfWidth = size.x / 2;
        float halfHeight = size.y / 2;

        int startX = std::max(0, static_cast<int>((center.x - halfWidth) / 16));
        int endX = std::min(width, static_cast<int>((center.x + halfWidth) / 16) + 1);
        int startY = std::max(0, static_cast<int>((center.y - halfHeight) / 16));
        int endY = std::min(height, static_cast<int>((center.y + halfHeight) / 16) + 1);
        
        // Update the view to center on the player
        updateView(view, window, world, tileWidth, tileHeight, width, height);

        // todo: use 1 for loop by increasing endY and endX
        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                Terrain* groundTile = world.getGroundTileAtPos(y, x);
                if (groundTile != nullptr) {
                    groundTile->setSpritePos(x, y);
                    window.draw(groundTile->getSprite());
                }
            }
        }

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Terrain* buildingTile = world.getBuildingTileAtPos(y, x);
                if (buildingTile != nullptr) {
                    buildingTile->setSpritePos(x, y);
                    window.draw(buildingTile->getSprite());
                }
            }
        }

        world.drawCharacters(window);
        if (drawGUI){
            window.setView(window.getDefaultView());
            gui.renderGUIElems(window, window.getSize());
        }

        window.display();
    }

    return 0;
}
