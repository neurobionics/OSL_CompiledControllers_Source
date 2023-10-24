#include <cassert>
#include "FSMStructs.hpp"
#include "FSMController.hpp"


int main() {

    // Initializes the hardware and parameters structs
    Hardware hardware;
    FSMParameters params;
    
    // Initializes body weight of subject
    params.bodyWeight = 60 * 9.8;

    // Initializes the minimum time required to pass before leaving the state
    params.minTimeInState = 2.0;
    
    // Sets the ESTANCE parameters
    params.eStanceParams.kneeK = 99.372;
    params.eStanceParams.kneeB = 3.180;
    params.eStanceParams.kneeTheta = 5;
    params.eStanceParams.loadLStance = -1.0 * params.bodyWeight * 0.25;
    params.eStanceParams.ankleThetaEStanceToLStance = 6.0;
    params.eStanceParams.ankleK = 19.874;
    params.eStanceParams.ankleB = 0;
    params.eStanceParams.ankleTheta = -2;

    // Sets the LSTANCE parameters
    params.lStanceParams.kneeK = 99.372;
    params.lStanceParams.kneeB = 1.272;
    params.lStanceParams.kneeTheta = 8;
    params.lStanceParams.loadESwing = -1.0 * params.bodyWeight * 0.15;
    params.lStanceParams.ankleK = 79.498;
    params.lStanceParams.ankleB = 0.063;
    params.lStanceParams.ankleTheta = -20;

    // Sets the ESWING parameters
    params.eSwingParams.kneeK = 39.749;
    params.eSwingParams.kneeB = 0.063;
    params.eSwingParams.kneeTheta = 60;
    params.eSwingParams.kneeThetaESwingToLSwing = 50;
    params.eSwingParams.kneeDThetaESwingToLSwing = 3;
    params.eSwingParams.ankleK = 7.949;
    params.eSwingParams.ankleB = 0.0;
    params.eSwingParams.ankleTheta = 25;

    // Sets the LSWING parameters
    params.lSwingParams.kneeK = 15.899;
    params.lSwingParams.kneeB = 3.816;
    params.lSwingParams.kneeTheta = 5;
    params.lSwingParams.loadEStance = -1.0 * params.bodyWeight * 0.4;
    params.lSwingParams.kneeThetaLSwingToEStance = 30;
    params.lSwingParams.ankleK = 7.949;
    params.lSwingParams.ankleB = 0.0;
    params.lSwingParams.ankleTheta = 15;

    // Initializes the gains and equilibrium angles for the knee and ankle
    State currentStateOut;
    double kneeTheta = 0.0;
    double kneeK = 0.0;
    double kneeB = 0.0;
    double ankleTheta = 0.0;
    double ankleK = 0.0;
    double ankleB = 0.0;


    // Currently, these are set to values in order to test the function
    // When implementing, these values should be set to readings from the sensors
    hardware.currentTimeInState = 30;
    hardware.time = 0;
    hardware.osl.loadcell.fx = 0;
    hardware.osl.loadcell.fy = 0;
    hardware.osl.loadcell.fz = 0;
    hardware.osl.loadcell.mx = 0;
    hardware.osl.loadcell.my = 0;
    hardware.osl.loadcell.mz = 0;
    hardware.osl.ankle.outputPosition = 70;
    hardware.osl.ankle.outputVelocity = 0;
    hardware.osl.knee.outputPosition = 0;
    hardware.osl.knee.outputVelocity = -4;  


      
    
    // Initializes pointers to the variables that are passed into the function
    Hardware *hardwarePtr = &hardware;
    FSMParameters *paramsPtr = &params;
    State *currentStateOutPtr = &currentStateOut;
    double *kneeThetaPtr = &kneeTheta;
    double *kneeKPtr = &kneeK;
    double *kneeBPtr = &kneeB;
    double *ankleThetaPtr = &ankleTheta;
    double *ankleKPtr = &ankleK;
    double *ankleBPtr = &ankleB;

    
    // CALLS FSMCONTROLLER FUNCTION
    FSMController(hardwarePtr, paramsPtr, currentStateOutPtr,
                  kneeThetaPtr, kneeKPtr, kneeBPtr, ankleThetaPtr, ankleKPtr,
                  ankleBPtr);

    FSMController(hardwarePtr, paramsPtr, currentStateOutPtr,
                  kneeThetaPtr, kneeKPtr, kneeBPtr, ankleThetaPtr, ankleKPtr,
                  ankleBPtr);

    assert(currentStateOut == LSTANCE);

    assert(kneeK == 99.372);
    assert(kneeB == 1.272);
    assert(kneeTheta == 8);
    assert(ankleK == 79.498);
    assert(ankleB == 0.063);
    assert(ankleTheta == -20);
}