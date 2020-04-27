// https://barrgroup.com/embedded-systems/how-to/state-machines-event-driven-systems

#ifndef AUSTIN_FINITE_STATE_MACHINE_H
#define AUSTIN_FINITE_STATE_MACHINE_H

// Define "struct <tag>" as type "<tag>"
typedef struct FiniteStateMachine FiniteStateMachine;
typedef struct Event Event;
typedef short int Signal;

// Define state as a function pointer with parent and event parameters
typedef void (*State)(FiniteStateMachine *FSM, Event const *MyEvent);

// Finite State Machine Base Class 
//  should only contain the current state
struct FiniteStateMachine
{
    State currentState;
};

// Event Base Class
//  should only contain the event signal
struct Event
{
    Signal EventSignal;
};

// NOTE:
// In a finite state machine implementation,
// All possible signals to the state machine should be
// enumerated in an "enum" such that each signal has a
// descriptive name associated with a unique short int.



//=============================================================================
// Preprocessor function definitions

// "FSM_Constructor" initializes the first state 
// by casting passed initialState function pointer to a State 
#define FSM_Constructor(FSM, initialState) \
        ((FSM)->currentState = (State)(initialState))

// "FSM_ExecuteInitialState" triggers the transition from the initial state.
#define FSM_ExecuteInitialState(FSM, initialEvent) \
        (*(FSM)->currentState)((FSM), (initialEvent))

// "FSM_Dispatch" executes the function that the FSM's state points to.
#define FSM_Dispatch(FSM, dispatchEvent) \
        (*(FSM)->currentState)((FSM), (dispatchEvent))

// "FSM_Transtion" changes the state (function pointer) of the FSM
//      to a new target state (function pointer)
//      (points state to new function).
#define FSM_Transition(FSM, targetState) \
        ((FSM)->currentState = (State)(targetState))
        
#endif
/* [] END OF FILE */
