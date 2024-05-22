#include <SFML/Graphics.hpp>
#include <iostream>
#include "World.hpp"
#include "Terrain.hpp"

int main() {
    const int width = 50;
    const int height = 25;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML game");

    World world;
    world.genTiles(height, width);

    sf::View view = window.getView();
    view.setCenter((5) * 16, (5) * 16);
    view.setSize(view.getSize().x / 2, view.getSize().y / 2);
    window.setView(view);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.move(0, -1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.move(0, 1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            view.move(-1.f, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            view.move(1.f, 0);
        }
        cout << view.getCenter().x << " " << view.getCenter().y << endl;

        window.clear(sf::Color::Cyan);

        window.setView(view); // Set the view before drawing

        sf::Vector2f center = view.getCenter();
        sf::Vector2f size = view.getSize();
        float halfWidth = size.x / 2;
        float halfHeight = size.y / 2;

        int startX = std::max(0, static_cast<int>((center.x - halfWidth) / 16));
        int endX = std::min(width, static_cast<int>((center.x + halfWidth) / 16) + 1);
        int startY = std::max(0, static_cast<int>((center.y - halfHeight) / 16));
        int endY = std::min(height, static_cast<int>((center.y + halfHeight) / 16) + 1);

        window.clear(sf::Color::Cyan);

        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                Terrain* groundTile = world.getGroundTileAtPos(y, x);
                Terrain* buildingTile = world.getBuildingTileAtPos(y, x);
                if (groundTile != nullptr) {
                    groundTile->setSpritePos(x, y);
                    window.draw(groundTile->getSprite());
                }
                if (buildingTile != nullptr) {
                    buildingTile->setSpritePos(x, y);
                    window.draw(buildingTile->getSprite());
                }
            }
        }

        // for (int y = 0; y < height; ++y) {
        //     for (int x = 0; x < width; ++x) {
        //         Terrain *tile = world.getBuildingTileAtPos(y, x);
        //         if (tile != nullptr) {
        //             tile->setSpritePos(x, y);
        //             window.draw(tile->getSprite());
        //         }
        //     }
        // }

        window.display();
    }

    return 0;
}
