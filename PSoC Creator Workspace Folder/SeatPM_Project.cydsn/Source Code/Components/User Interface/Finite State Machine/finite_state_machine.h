/*==============================================================================
Project: SeatPM
Team: Joint Effort
School: Seattle Pacific University
Class: CatalyzeU Senior Design

File Name: finite_state_machine.h
Author: Austin Pischer
File Description:
This file contains all the code for the finite state machine base class.
There is no finite_state_machine.c file because all of the "functions" for
the FSM base class are macros.

A finite state machine is a way to systematize the flow of control through a
program. A state defines the possible events that can be occur and the
results of each possible event occuring. There is only one active state at a
time, and one state transitions to another state only after a certain set of
conditions are met.

This file is mostly adopted from the following link:
https://barrgroup.com/embedded-systems/how-to/state-machines-event-driven-systems

A state is a function that handles the event passed to it by FSM_Dispatch()
A finite state machine "object" only holds the current state.
The current state should transition to another state by calling FSM_Transition()

For the purposes of the SeatPM, the finite state machine is only used as the
user interface derived class.

A derived event class can hold more than a signal.
==============================================================================*/

// Start Multiple Inclusion Protection
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

// End of Multiple Inclusion Protection
#endif
/* [] END OF FILE */
