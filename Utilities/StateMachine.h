#pragma once

namespace RoadRage {

template<typename State>
class StateMachine {
public:
    StateMachine(State initial);
    virtual ~StateMachine();

    State state() const;
    State state(State next);

protected:
    virtual bool onLeavingCurrentState();
    virtual bool onEnteringNewState(State next);

private:
    State m_state;
};

#include "StateMachine.inl"

}
