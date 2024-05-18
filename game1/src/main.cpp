#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Tilemap");

    // Load the tilemap texture
    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile("assets/Tiles_FinalLayout.png")) {
        return -1; // Failed to load texture
    }

    // Define the tile size
    const int tileSize = 16;

    // Define the tilemap data
    int num_col = 15; //Number of columns
	int num_row = 10; // Number of rows
	vector<int> row(num_col, 0); // Initializing a single row
	vector<vector<int>> tileMap(num_row, row); // Initializing the 2-D vector

    // int tileMap[10][15] = {
    //     {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    //     {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    //     {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    //     {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    //     {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    //     {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    //     {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    //     {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    //     {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    //     {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}
    // };

    // Create the tilemap sprites
    sf::Sprite tileSprites[1];
    tileSprites[0].setTexture(tileTexture);
    tileSprites[0].setTextureRect(sf::IntRect(64, 0, tileSize, tileSize));
    // tileSprites[1].setTexture(tileTexture);
    // tileSprites[1].setTextureRect(sf::IntRect(tileSize, 0, tileSize, tileSize));

    // Adjust the view to zoom in
    sf::View view = window.getView();
    view.setCenter((num_col/2) * tileSize, (num_row/2) * tileSize);
    view.setSize(view.getSize().x / 4, view.getSize().y / 4);
    window.setView(view);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.move(0, -0.5f);
            cout << "H" << endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.move(0, 0.5f);
            cout << "H" << endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            view.move(-0.5f, 0);
            cout << "H" << endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            view.move(0.5f, 0);
            cout << "H" << endl;
        }

        window.clear();

        // Draw the tilemap
        for (int y = 0; y < num_row; ++y) {
            for (int x = 0; x < num_col; ++x) {
                int tileIndex = tileMap[y][x];
                tileSprites[tileIndex].setPosition(x * tileSize, y * tileSize);
                window.draw(tileSprites[tileIndex]);
            }
        }

        window.display();
        window.setView(view);
    }

    return 0;
}