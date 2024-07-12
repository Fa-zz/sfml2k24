/*
    State objects represent different "screens" of the game that the player can switch between. Examples include
    the main menu, different states of the game

    State objects can also be used within states, such as pop up windows within a state.

    States loop among input, update, and render functions
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include "string"
using namespace std;

namespace Engine {
    class State {
    public:
        State() = default;
        virtual ~State() = default;

        virtual void init() = 0;
        virtual void loop(const sf::Time& deltaTime) = 0;
        virtual void loop(sf::RenderTarget& rt) {}

        virtual void processInput() = 0;

        virtual void update(const sf::Time &deltaTime) = 0;
        virtual void update() {}
        virtual void render() = 0;
        virtual void render(sf::RenderTarget& rt) {}

        virtual void handleInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp) {}
        virtual string getData() {}


        virtual void pause() {};
        virtual void start() {};
    };
}
