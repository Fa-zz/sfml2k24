#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "World.hpp"
#include "Terrain.hpp"

int main() {
    const int width = 50;
    const int height = 25;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML game");

    World world;
    world.genTiles(height, width);

    sf::View view = window.getView();
    // view.setCenter((5) * 16, (5) * 16);
    view.setSize(view.getSize().x / 4, view.getSize().y / 4);
    window.setView(view);

    auto tp = chrono::steady_clock::now();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // // catch the resize events
            // if (event.type == sf::Event::Resized) {
            //     // update the view to the new size of the window
            //     sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
            //     window.setView(sf::View(visibleArea));
            // }
        }

        // get dt
        float dt;
        const auto new_tp = std::chrono::steady_clock::now();
        dt = std::chrono::duration<float>( new_tp - tp ).count();
        tp = new_tp;
        
        view.setCenter(world.getPlayerCenter());
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
        // cout << view.getCenter().x << " " << view.getCenter().y << endl;
        world.updateCharacters(dir, dt);

        window.clear(sf::Color (134,192,108));

        window.setView(view); // Set the view before drawing

        sf::Vector2f center = view.getCenter();
        sf::Vector2f size = view.getSize();
        float halfWidth = size.x / 2;
        float halfHeight = size.y / 2;

        int startX = std::max(0, static_cast<int>((center.x - halfWidth) / 16));
        int endX = std::min(width, static_cast<int>((center.x + halfWidth) / 16) + 1);
        int startY = std::max(0, static_cast<int>((center.y - halfHeight) / 16));
        int endY = std::min(height, static_cast<int>((center.y + halfHeight) / 16) + 1);

        // window.clear(sf::Color::Cyan);

        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                Terrain* groundTile = world.getGroundTileAtPos(y, x);
                if (groundTile != nullptr) {
                    groundTile->setSpritePos(x, y);
                    window.draw(groundTile->getSprite());
                }
                Terrain* buildingTile = world.getBuildingTileAtPos(y, x);
                if (buildingTile != nullptr) {
                    buildingTile->setSpritePos(x, y);
                    window.draw(buildingTile->getSprite());
                }
            }
        }

        // for (int y = 0; y < height; ++y) {
        //     for (int x = 0; x < width; ++x) {
        //         Terrain* buildingTile = world.getBuildingTileAtPos(y, x);
        //         if (buildingTile != nullptr) {
        //             buildingTile->setSpritePos(x, y);
        //             window.draw(buildingTile->getSprite());
        //         }
        //     }
        // }

        world.drawCharacters(window);

        window.display();
    }

    return 0;
}
