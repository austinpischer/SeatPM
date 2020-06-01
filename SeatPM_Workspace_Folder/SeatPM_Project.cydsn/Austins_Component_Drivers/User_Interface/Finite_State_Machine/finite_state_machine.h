// TODO: File header

// https://barrgroup.com/embedded-systems/how-to/state-machines-event-driven-systems

// Multiple Inlusion Protection
#ifndef AUSTIN_FINITE_STATE_MACHINE_H
#define AUSTIN_FINITE_STATE_MACHINE_H

//-----------------------------------------------------------------------------
// Typedefs

// Note: These must come before any of the Data Member structures
//       so that the types may be used within those structures.
    
// Defining "struct <tag>" as type "<tag>"
typedef struct FiniteStateMachine FiniteStateMachine;
typedef struct Event Event;
    
typedef short int Signal;
    
// Define state as a function pointer with parent and event parameters
typedef void (*State)(FiniteStateMachine *FSM, Event const *MyEvent);

// ----------------------------------------------------------------------------
// Event Struct -- Finite State Machine (should only contain the event signal)
struct Event
{
    Signal EventSignal;
};

//=============================================================================
// Data Members -- Finite State Machine (User Interface Base Class)
//=============================================================================
struct FiniteStateMachine
{
    State CurrentState;
};
// NOTE: In a finite state machine implementation,
// All possible signals to the state machine should be
// enumerated in an "enum" such that each signal has a
// descriptive name associated with a unique short int.

//=============================================================================
// Method Members -- Finite State Machine (User Interface Base Class)
//=============================================================================

// Note: these are Preprocessor function definitions

// "FSM_Constructor" initializes the first state 
// by casting passed initialState function pointer to a State 
#define FSM_Constructor(FSM, initialState) \
        ((FSM)->CurrentState = (State)(initialState))

// "FSM_ExecuteInitialState" triggers the transition from the initial state.
#define FSM_ExecuteInitialState(FSM, initialEvent) \
        (*(FSM)->CurrentState)((FSM), (initialEvent))

// "FSM_Dispatch" executes the function that the FSM's state points to.
#define FSM_Dispatch(FSM, dispatchEvent) \
        (*(FSM)->CurrentState)((FSM), (dispatchEvent))

// "FSM_Transtion" changes the state (function pointer) of the FSM
//      to a new target state (function pointer)
//      (points state to new function).
#define FSM_Transition(FSM, targetState) \
        ((FSM)->CurrentState = (State)(targetState))

// End of Multiple Inlusion Protection
#endif
/* [] END OF FILE */
