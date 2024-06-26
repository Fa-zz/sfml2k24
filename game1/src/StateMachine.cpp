#include "StateMachine.hpp"

Engine::StateMachine::StateMachine() : m_add(false), m_replace(false), m_remove(false), m_removeAll(false)
{
}

Engine::StateMachine::~StateMachine()
{
}

void Engine::StateMachine::Add(std::unique_ptr<State> toAdd, bool replace)
{
    m_add = true;
    m_newState = std::move(toAdd);

    m_replace = replace;
}

void Engine::StateMachine::PopCurrent()
{
    m_remove = true;
}

void Engine::StateMachine::PopAll()
{
    m_removeAll = true;
    m_remove = false;
}

void Engine::StateMachine::ProcessStateChange()
{
    if (m_removeAll)
    {
        while (!m_stateStack.empty())
        {
            m_stateStack.pop();
        }
        m_removeAll = false;
    }
    else if (m_remove && (!m_stateStack.empty()))
    {
        m_stateStack.pop();

        if (!m_stateStack.empty())
        {
            m_stateStack.top()->start();
        }

        m_remove = false;
    }

    if (m_add)
    {
        if (m_replace && (!m_stateStack.empty()))
        {
            m_stateStack.pop();
            m_replace = false;
        }

        if (!m_stateStack.empty())
        {
            m_stateStack.top()->pause();
        }

        m_stateStack.push(std::move(m_newState));
        m_stateStack.top()->init();
        m_stateStack.top()->start();
        m_add = false;
    }
}

std::unique_ptr<Engine::State> &Engine::StateMachine::GetCurrent()
{
    return m_stateStack.top();
}

bool Engine::StateMachine::IsEmpty() const
{
    return m_stateStack.empty();
}