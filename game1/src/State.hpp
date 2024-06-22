#pragma once

#include <SFML/System/Time.hpp>

namespace Engine {
    class State {
    public:
        State(){};
        virtual ~State(){};

        virtual void init() = 0;
        virtual void processInput() = 0;
        virtual void update(const sf::Time& deltaTime) = 0;
        virtual void render() = 0;

        virtual void pause(){};
        virtual void start(){};
    };
}