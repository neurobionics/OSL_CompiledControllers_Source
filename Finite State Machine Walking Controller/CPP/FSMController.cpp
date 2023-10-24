#include "FSMStructs.hpp"
#include "FSMController.hpp"



/**
 * This function implements a finite state machine (FSM) controller for the
 * OSL. The FSM has four states: ESTANCE, LSTANCE, ESWING, and LSWING. FINISH!
 * 
*/
FSM_Outputs FSMController(FSM_Inputs inputs) {

    // If this is the first function call, initialize the current state to ESTANCE
    Sensors sensors = inputs.sensors;
    FSMParameters params = inputs.parameters;
    
    static State currentState = ESTANCE;
    static double currentTimeInState = 0.0;
    static double time_last;

    double dt = inputs.time - time_last;
    time_last = inputs.time;

    // When in ESTANCE
    if (currentState == ESTANCE) {
        
        // Conditions to transition to LSTANCE
        if ((sensors.Fz < params.transitionParameters.loadLStance) &&
            (sensors.ankleAngle > params.transitionParameters.ankleThetaEStanceToLStance) &&
            (currentTimeInState > params.transitionParameters.minTimeInState)) {
                // Update to LSTANCE
                currentState = LSTANCE;
                currentTimeInState = 0.0;

        // Otherwise, remain in ESTANCE
        } else {
            currentState = ESTANCE;
            currentTimeInState += dt;
        }
    
    // When in LSTANCE
    } else if (currentState == LSTANCE) {
        
        // Conditions to transition to ESWING
        if ((sensors.Fz > params.transitionParameters.loadLStance) &&
            (currentTimeInState > params.transitionParameters.minTimeInState)) {
                // Update to ESWING
                currentState = ESWING;
                currentTimeInState = 0.0;
            
        // Otherwise, remain in LSTANCE
        } else {
            currentState = LSTANCE;
            currentTimeInState += dt;
        }
    
    // When in ESWING
    } else if (currentState == ESWING) {

        // Conditions to transition to LSWING
        if ((sensors.kneeAngle > params.transitionParameters.kneeThetaESwingToLSwing) &&
            (sensors.kneeVelocity < params.transitionParameters.kneeDThetaESwingToLSwing) &&
            (currentTimeInState > params.transitionParameters.minTimeInState)) {
                // Update to LSWING
                currentState = LSWING;
                currentTimeInState = 0.0;
        
        // Otherwise, remain in ESWING
        } else {
            currentState = ESWING;
            currentTimeInState += dt;
        }

    // When in LSWING
    } else if (currentState == LSWING) {

        // Conditions to transition to ESTANCE
        if ((sensors.Fz < params.transitionParameters.loadEStance) &&
            (sensors.kneeAngle < params.transitionParameters.kneeThetaLSwingToEStance) &&
            (currentTimeInState > params.transitionParameters.minTimeInState)) {
                // Update to ESTANCE
                currentState = ESTANCE;
                currentTimeInState = 0.0;
        
        // Otherwise, remain in LSWING
        } else {
            currentState = LSWING;
            currentTimeInState += dt;
        }

    // If the current state is not one of the four states, set the current state to ESTANCE
    } else {
        currentState = ESTANCE;
        currentTimeInState += dt;
    }

    // Select the impedance parameters for the current state
    ImpedanceParameters kneeImpedance;
    ImpedanceParameters ankleImpedance;

    if (currentState == ESTANCE) {
        kneeImpedance = params.kneeImpedance.earlyStance;
        ankleImpedance = params.ankleImpedance.earlyStance;
    } else if (currentState == LSTANCE) {
        kneeImpedance = params.kneeImpedance.lateStance;
        ankleImpedance = params.ankleImpedance.lateStance;
    } else if (currentState == ESWING) {
        kneeImpedance = params.kneeImpedance.earlySwing;
        ankleImpedance = params.ankleImpedance.earlySwing;
    } else if (currentState == LSWING) {
        kneeImpedance = params.kneeImpedance.lateSwing;
        ankleImpedance = params.ankleImpedance.lateSwing;
    } else {
        kneeImpedance = params.kneeImpedance.earlyStance;
        ankleImpedance = params.ankleImpedance.earlyStance;
    }


    // Set outputs
    FSM_Outputs outputs;

    outputs.currentState = currentState;
    outputs.timeInCurrentState = currentTimeInState;
    outputs.kneeImpedance = kneeImpedance;
    outputs.ankleImpedance = ankleImpedance;

    return outputs;

}
