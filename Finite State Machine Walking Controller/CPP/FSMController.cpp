#include "FSMStructs.hpp"
#include "FSMController.hpp"



/**
 * This function implements a finite state machine (FSM) controller for the
 * OSL. The FSM has four states: ESTANCE, LSTANCE, ESWING, and LSWING. The
 * FSM transitions between states based on the current state, the current
 * time in state, and the current hardwarePtr readings. The FSM outputs the
 * desired knee and ankle  equilibrium angles and gains for the current state.
 * 
 * @param currentTimeInStatePtr Pointer to the current time in state
 * @param hardwarePtr Pointer to the hardwarePtr struct which has a knee joint, ankle joint and loadcell struct as attributes
 * @param paramsPtr Pointer to the paramsPtr struct which has a body weight and four structs for the four states as attributes
 * @param currentStateOutPtr Pointer to the current state
 * @param kneeThetaPtr Pointer to the desired knee equilibrium angle
 * @param kneeKPtr Pointer to the desired knee gain
 * @param kneeBPtr Pointer to the desired knee damping
 * @param ankleThetaPtr Pointer to the desired ankle equilibrium angle
 * @param ankleKPtr Pointer to the desired ankle gain
 * @param ankleBPtr Pointer to the desired ankle damping
 * 
 * @return void
 * 
 * @see FSMStructs.hpp
 * 
 * @note See FSMController_tb.cpp to see how this function is called
 * @note This function modifies the values of the pointers passed to it
 * 
*/
void FSMController(Hardware *hardwarePtr,
                   const FSMParameters *paramsPtr, State *currentStateOutPtr,
                   double *kneeThetaPtr, double *kneeKPtr, double *kneeBPtr,
                   double *ankleThetaPtr, double *ankleKPtr, double *ankleBPtr) {

    // If this is the first function call, initialize the current state to ESTANCE
    static State currentState = ESTANCE;

    // When in ESTANCE
    if (currentState == ESTANCE) {
        
        // Conditions to transition to LSTANCE
        if ((hardwarePtr->osl.loadcell.fz > paramsPtr->eStanceParams.loadLStance) &&
        (hardwarePtr->osl.ankle.outputPosition > paramsPtr->eStanceParams.ankleThetaEStanceToLStance) &&
        (hardwarePtr->currentTimeInState > paramsPtr->minTimeInState)) {

            // Update to LSTANCE
            currentState = LSTANCE;
            *kneeThetaPtr = paramsPtr->lStanceParams.kneeTheta;
            *kneeKPtr = paramsPtr->lStanceParams.kneeK;
            *kneeBPtr = paramsPtr->lStanceParams.kneeB;
            *ankleThetaPtr = paramsPtr->lStanceParams.ankleTheta;
            *ankleKPtr = paramsPtr->lStanceParams.ankleK;
            *ankleBPtr = paramsPtr->lStanceParams.ankleB;
            hardwarePtr->currentTimeInState = 0.0;

        // Otherwise, remain in LSTANCE
        } else {
            currentState = ESTANCE;
            *kneeThetaPtr = paramsPtr->eStanceParams.kneeTheta;
            *kneeKPtr = paramsPtr->eStanceParams.kneeK;
            *kneeBPtr = paramsPtr->eStanceParams.kneeB;
            *ankleThetaPtr = paramsPtr->eStanceParams.ankleTheta;
            *ankleKPtr = paramsPtr->eStanceParams.ankleK;
            *ankleBPtr = paramsPtr->eStanceParams.ankleB;
            hardwarePtr->currentTimeInState += hardwarePtr->time;
        }
    
    // When in LSTANCE
    } else if (currentState == LSTANCE) {
        
        // Conditions to transition to ESWING
        if ((hardwarePtr->osl.loadcell.fz > paramsPtr->lStanceParams.loadESwing) &&
        (hardwarePtr->currentTimeInState > paramsPtr->minTimeInState)) {
            
            // Update to ESWING
            currentState = ESWING;
            *kneeThetaPtr = paramsPtr->eSwingParams.kneeTheta;
            *kneeKPtr = paramsPtr->eSwingParams.kneeK;
            *kneeBPtr = paramsPtr->eSwingParams.kneeB;
            *ankleThetaPtr = paramsPtr->eSwingParams.ankleTheta;
            *ankleKPtr = paramsPtr->eSwingParams.ankleK;
            *ankleBPtr = paramsPtr->eSwingParams.ankleB;
            hardwarePtr->currentTimeInState = 0.0;
        
        // Otherwise, remain in LSTANCE
        } else {
            currentState = LSTANCE;
            *kneeThetaPtr = paramsPtr->lStanceParams.kneeTheta;
            *kneeKPtr = paramsPtr->lStanceParams.kneeK;
            *kneeBPtr = paramsPtr->lStanceParams.kneeB;
            *ankleThetaPtr = paramsPtr->lStanceParams.ankleTheta;
            *ankleKPtr = paramsPtr->lStanceParams.ankleK;
            *ankleBPtr = paramsPtr->lStanceParams.ankleB;
            hardwarePtr->currentTimeInState += hardwarePtr->time;
        }
    // When in ESWING
    } else if (currentState == ESWING) {

        // Conditions to transition to LSWING
        if ((hardwarePtr->osl.knee.outputPosition >
        paramsPtr->eSwingParams.kneeThetaESwingToLSwing) &&
        (hardwarePtr->osl.knee.outputVelocity <
         paramsPtr->eSwingParams.kneeDThetaESwingToLSwing) &&
        (hardwarePtr->currentTimeInState > paramsPtr->minTimeInState)) {

            // Update to LSWING
            currentState = LSWING;
            *kneeThetaPtr = paramsPtr->lSwingParams.kneeTheta;
            *kneeKPtr = paramsPtr->lSwingParams.kneeK;
            *kneeBPtr = paramsPtr->lSwingParams.kneeB;
            *ankleThetaPtr = paramsPtr->lSwingParams.ankleTheta;
            *ankleKPtr = paramsPtr->lSwingParams.ankleK;
            *ankleBPtr = paramsPtr->lSwingParams.ankleB;
            hardwarePtr->currentTimeInState = 0.0;
        
        // Otherwise, remain in ESWING
        } else {
            currentState = ESWING;
            *kneeThetaPtr = paramsPtr->eSwingParams.kneeTheta;
            *kneeKPtr = paramsPtr->eSwingParams.kneeK;
            *kneeBPtr = paramsPtr->eSwingParams.kneeB;
            *ankleThetaPtr = paramsPtr->eSwingParams.ankleTheta;
            *ankleKPtr = paramsPtr->eSwingParams.ankleK;
            *ankleBPtr = paramsPtr->eSwingParams.ankleB;
            hardwarePtr->currentTimeInState += hardwarePtr->time;
        }

    // When in LSWING
    } else if (currentState == LSWING) {

        // Conditions to transition to ESTANCE
        if ((hardwarePtr->osl.loadcell.fz < paramsPtr->lSwingParams.loadEStance) ||
        (hardwarePtr->osl.knee.outputPosition <
        paramsPtr->lSwingParams.kneeThetaLSwingToEStance)) {
            
            // Update to ESTANCE
            currentState = ESTANCE;
            *kneeThetaPtr = paramsPtr->eStanceParams.kneeTheta;
            *kneeKPtr = paramsPtr->eStanceParams.kneeK;
            *kneeBPtr = paramsPtr->eStanceParams.kneeB;
            *ankleThetaPtr = paramsPtr->eStanceParams.ankleTheta;
            *ankleKPtr = paramsPtr->eStanceParams.ankleK;
            *ankleBPtr = paramsPtr->eStanceParams.ankleB;
            hardwarePtr->currentTimeInState = 0.0;
        
        // Otherwise, remain in LSWING
        } else {
            currentState = LSWING;
            *kneeThetaPtr = paramsPtr->lSwingParams.kneeTheta;
            *kneeKPtr = paramsPtr->lSwingParams.kneeK;
            *kneeBPtr = paramsPtr->lSwingParams.kneeB;
            *ankleThetaPtr = paramsPtr->lSwingParams.ankleTheta;
            *ankleKPtr = paramsPtr->lSwingParams.ankleK;
            *ankleBPtr = paramsPtr->lSwingParams.ankleB;
            hardwarePtr->currentTimeInState += hardwarePtr->time;
        }

    // If the current state is not one of the four states, set the current state to ESTANCE
    } else {
        currentState = ESTANCE;
        *kneeThetaPtr = paramsPtr->eStanceParams.kneeTheta;
        *kneeKPtr = paramsPtr->eStanceParams.kneeK;
        *kneeBPtr = paramsPtr->eStanceParams.kneeB;
        *ankleThetaPtr = paramsPtr->eStanceParams.ankleTheta;
        *ankleKPtr = paramsPtr->eStanceParams.ankleK;
        *ankleBPtr = paramsPtr->eStanceParams.ankleB;
        hardwarePtr->currentTimeInState = 0.0;
    }

    // Update the current state
    *currentStateOutPtr = currentState;

}
