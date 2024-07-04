#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

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

        virtual void pause() {};
        virtual void start() {};
    };
}
