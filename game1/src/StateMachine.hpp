/*
    State machine is the main structure used to navigate different game "screens", represented as state objects, as well
    as internal states such as pop up screens. It is a stack that pops, pops all, pushes, or replaces State objects
*/

#pragma once
#include <stack>
#include <memory>
#include "State.hpp"

namespace Engine
{
    class StateMachine
    {
    public:
        StateMachine();
        ~StateMachine();

        void Add(std::unique_ptr<State> toAdd, bool replace = false);
        void PopCurrent();
        void PopAll();
        void ProcessStateChange();
        std::unique_ptr<State> &GetCurrent();
        bool IsEmpty() const;

    private:
        std::stack<std::unique_ptr<State>> m_stateStack;
        std::unique_ptr<State> m_newState;

        bool m_add;
        bool m_replace;
        bool m_remove;
        bool m_removeAll;
    };

}