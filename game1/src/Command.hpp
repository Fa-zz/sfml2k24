// #pragma once
// #include <vector>
// #include <iostream>
// #include "SFML/Graphics.hpp"
// #include "Character.hpp"

// /*
//     Part of the "command" pattern. Represents a keystroke. Can be created after pushing a key, or as an object
//     Commands are dispatched from InputHandler. Each command has its own functionality after executing. Functionality is
//     performed on actor/character, including PC and NPCs.
// */

// class Command {
// public:
//     virtual ~Command() {}
//     virtual void setCommandsKey(sf::Keyboard::Key key) = 0;  // bind the command to a certain key
//     virtual sf::Keyboard::Key getCommandsKey() = 0;          // get the key the command has been bound to
//     virtual void execute(Character& actor) = 0;              // execute the desired function on an actor/character
// };