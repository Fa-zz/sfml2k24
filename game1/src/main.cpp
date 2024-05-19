#include <SFML/Graphics.hpp>
#include <iostream>
#include "World.hpp"
#include "Terrain.hpp"

int main() {
    const int width = 50;
    const int height = 50;

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
            view.move(0, -0.5f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.move(0, 0.5f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            view.move(-0.5f, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            view.move(0.5f, 0);
        }
        cout << view.getCenter().x << " " << view.getCenter().y << endl;

        window.clear(sf::Color::Cyan);

        window.setView(view); // Set the view before drawing

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Terrain& tile = world.getGroundTileAtPos(y, x);
                tile.setSpritePos(x, y);
                window.draw(tile.getSprite());
            }
        }
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Terrain *tile = world.getBuildingTileAtPos(y, x);
                if (tile != nullptr) {
                    tile->setSpritePos(x, y);
                    window.draw(tile->getSprite());
                }
            }
        }

        window.display();
    }

    return 0;
}
