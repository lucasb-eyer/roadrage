template<class State>
StateMachine<State>::StateMachine(State initial)
    : m_state(initial)
{
}

template<class State>
StateMachine<State>::~StateMachine()
{
}

template<class State>
State StateMachine<State>::state() const
{
    return m_state;
}

template<class State>
State StateMachine<State>::state(State next)
{
    // If we are already in that state, just don't change.
    if(m_state == next)
        return m_state;

    // First, check if we may leave this state.
    if(!this->onLeavingCurrentState())
        return m_state;

    // Then, check if we can enter the new state.
    if(!this->onEnteringNewState(next))
        return m_state;

    // If all this worked, change the state.
    State old = m_state;
    m_state = next;
    return old;
}

template<class State>
bool StateMachine<State>::onLeavingCurrentState()
{
    return true;
}

template<class State>
bool StateMachine<State>::onEnteringNewState(State next)
{
    return true;
}
