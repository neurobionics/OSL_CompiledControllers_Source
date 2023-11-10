#include "FSMController.hpp"

/**
 * This function implements a finite state machine (FSM) controller for the
 * OSL. The FSM has four states: ESTANCE, LSTANCE, ESWING, and LSWING. 
 * 
 * Jace Derosia, Kevin Best
 * October 2023
*/
extern "C" void FSMController(FSM_Inputs *inputs, FSM_Outputs *outputs) {

    // If this is the first function call, initialize the current state to ESTANCE
    Sensors sensors = inputs->sensors;
    FSMParameters params = inputs->parameters;
    
    static State currentState = ESTANCE;
    static State previousState = ESTANCE;
    static double currentTimeInState = 0.0;
    static double time_last;

    double dt = inputs->time - time_last;
    time_last = inputs->time;

    // When in ESTANCE
    if (currentState == ESTANCE) {
        // Conditions to transition to LSTANCE
        if ((sensors.Fz < params.transitionParameters.loadLStance) &&
            (sensors.ankleAngle > params.transitionParameters.ankleThetaEStanceToLStance) &&
            (currentTimeInState > params.transitionParameters.minTimeInState)) {
                // Update to LSTANCE
                currentState = LSTANCE;
        // Otherwise, remain in ESTANCE
        } else {
            currentState = ESTANCE;
        }
    
    // When in LSTANCE
    } else if (currentState == LSTANCE) {
        // Conditions to transition to ESWING
        if ((sensors.Fz > params.transitionParameters.loadLStance) &&
            (currentTimeInState > params.transitionParameters.minTimeInState)) {
                // Update to ESWING
                currentState = ESWING;
        // Otherwise, remain in LSTANCE
        } else {
            currentState = LSTANCE;
        }
    
    // When in ESWING
    } else if (currentState == ESWING) {
        // Conditions to transition to LSWING
        if ((sensors.kneeAngle > params.transitionParameters.kneeThetaESwingToLSwing) &&
            (sensors.kneeVelocity < params.transitionParameters.kneeDThetaESwingToLSwing) &&
            (currentTimeInState > params.transitionParameters.minTimeInState)) {
                // Update to LSWING
                currentState = LSWING;
        // Otherwise, remain in ESWING
        } else {
            currentState = ESWING;
        }

    // When in LSWING
    } else if (currentState == LSWING) {
        // Conditions to transition to ESTANCE
        if (((sensors.Fz < params.transitionParameters.loadEStance) ||
            (sensors.kneeAngle < params.transitionParameters.kneeThetaLSwingToEStance)) &&
            (currentTimeInState > params.transitionParameters.minTimeInState)) {
                // Update to ESTANCE
                currentState = ESTANCE;        
        // Otherwise, remain in LSWING
        } else {
            currentState = LSWING;
        }

    // If the current state is not one of the four states, set the current state to ESTANCE
    } else {
        currentState = ESTANCE;
    }

    // Select the impedance parameters for the current state
    ImpedanceParameters kneeImpedance;
    ImpedanceParameters ankleImpedance;

    switch(currentState) {
        case ESTANCE:
            kneeImpedance = params.kneeImpedance.earlyStance;
            ankleImpedance = params.ankleImpedance.earlyStance;
            break;
        case LSTANCE:
            kneeImpedance = params.kneeImpedance.lateStance;
            ankleImpedance = params.ankleImpedance.lateStance;
            break;
        case ESWING:
            kneeImpedance = params.kneeImpedance.earlySwing;
            ankleImpedance = params.ankleImpedance.earlySwing;
            break;
        case LSWING:
            kneeImpedance = params.kneeImpedance.lateSwing;
            ankleImpedance = params.ankleImpedance.lateSwing;
            break;
        default:
            kneeImpedance = params.kneeImpedance.earlyStance;
            ankleImpedance = params.ankleImpedance.earlyStance;
    }

    // Track time in state
    if (currentState == previousState) {
        currentTimeInState += dt;
    } else {
        currentTimeInState = 0.0;
    }

    // Update previous state
    previousState = currentState;

    // Set outputs
    outputs->currentState = currentState;
    outputs->timeInCurrentState = currentTimeInState;
    outputs->kneeImpedance = kneeImpedance;
    outputs->ankleImpedance = ankleImpedance;
}

// Placeholder init and terminate functions
extern "C" void FSMController_initialize(void){};
extern "C" void FSMController_terminate(void){};