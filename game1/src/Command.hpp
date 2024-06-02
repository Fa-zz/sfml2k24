#pragma once
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Character.hpp"

class Command {
public:
    virtual ~Command() {}
    virtual void setCommandsKey(sf::Keyboard::Key key) = 0;
    virtual sf::Keyboard::Key getCommandsKey() = 0;
    virtual void execute(Character& actor) = 0;
};