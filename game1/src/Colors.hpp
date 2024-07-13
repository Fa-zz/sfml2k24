
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace DefinedColors {
    // 1.  Food: Low: rgb(124, 252, 0), Medium: rgb(0, 128, 0), High: rgb(53, 94, 59)
    // 2. Zombies Low: rgb(238, 75, 43), Medium: rgb(165, 42, 42), High: rgb(128, 0, 32)
    // 3. Blue Low: rgb(0, 255, 255), Medium: rgb(137, 207, 240), High: rgb(0, 0, 255)
    inline const sf::Color foodLow(124,252,0);
    inline const sf::Color foodMed(0,128,0);
    inline const sf::Color foodHigh(53,94,59);
    inline const sf::Color zombLow(238,75,43);
    inline const sf::Color zombMed(165,42,42);
    inline const sf::Color zombHigh(128,0,32);
    inline const sf::Color survLow(0,255,255);
    inline const sf::Color survMed(137,207,240);
    inline const sf::Color survHigh(0,0,255);
}