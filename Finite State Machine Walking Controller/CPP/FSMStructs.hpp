#ifndef FSMSTRUCTS_HPP
#define FSMSTRUCTS_HPP


/**
 * @brief      This struct contains the output positions and velocities for the knee and ankle joints
 * 
 * @param     outputPosition  The output position read from the encoder
 * @param     outputVelocity  The output velocity read from the encoder
*/
struct Joint {
    double outputPosition;
    double outputVelocity;
};

/**
 * @brief      This struct contains the forces and moments read from the loadcell
 * 
 * @param     fx  The force in the x direction
 * @param     fy  The force in the y direction
 * @param     fz  The force in the z direction
 * @param     mx  The moment in the x direction
 * @param     my  The moment in the y direction
 * @param     mz  The moment in the z direction
 * 
*/
struct Loadcell {
  double fx;
  double fy;
  double fz;
  double mx;
  double my;
  double mz;
};


/**
 * @brief      This struct contains the joint and loadcell structs for the OSL
 * 
 * @param     knee  The knee joint
 * @param     ankle  The ankle joint
 * @param     loadcell  The loadcell
 * 
*/
struct OSL{
  Joint knee;
  Joint ankle;
  Loadcell loadcell;
};


/**
 * @brief      This struct contains the OSL and time
 * 
 * @param     osl  The OSL struct
 * @param     time  The time
 * 
*/
struct Hardware{
  OSL osl;
  double time;
  double currentTimeInState;
};

struct eStanceParams{
  double kneeK;
  double kneeB;
  double kneeTheta;
  double ankleK;
  double ankleB;
  double ankleTheta;
  double loadLStance;
  double ankleThetaEStanceToLStance;
};

struct lStanceParams{
  double kneeK;
  double kneeB;
  double kneeTheta;
  double ankleK;
  double ankleB;
  double ankleTheta;
  double loadESwing;
};

struct eSwingParams{
  double kneeK;
  double kneeB;
  double kneeTheta;
  double ankleK;
  double ankleB;
  double ankleTheta;
  double kneeThetaESwingToLSwing;
  double kneeDThetaESwingToLSwing;
};

struct lSwingParams{
  double kneeK;
  double kneeB;
  double kneeTheta;
  double ankleK;
  double ankleB;
  double ankleTheta;
  double loadEStance;
  double kneeThetaLSwingToEStance;
};

struct FSMParameters{
  double bodyWeight;
  eStanceParams eStanceParams;
  lStanceParams lStanceParams;
  eSwingParams eSwingParams;
  lSwingParams lSwingParams;
  double minTimeInState;
};

enum State {
    ESTANCE = 1,
    LSTANCE = 2,
    ESWING = 3,
    LSWING = 4,
};

// struct ReturnValues {
//     State currentState;
//     double kneeTheta;
//     double kneeK;
//     double kneeB;
//     double ankleTheta;
//     double ankleK;
//     double ankleB;
//     double currentTimeInState;
// };


#endif // FSMSTRUCTS_HPP