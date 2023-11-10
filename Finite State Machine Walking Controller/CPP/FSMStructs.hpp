#ifndef FSMSTRUCTS_HPP
#define FSMSTRUCTS_HPP


struct ImpedanceParameters {

  double stiffness;
  double damping;
  double eqAngle;

};


struct JointImpedanceSet {

  ImpedanceParameters earlyStance;
  ImpedanceParameters lateStance;
  ImpedanceParameters earlySwing;
  ImpedanceParameters lateSwing;

};


struct Sensors {

  double kneeAngle;
  double ankleAngle;
  double kneeVelocity;
  double ankleVelocity;
  double Fz;

};


struct TransitionParameters {

  double minTimeInState;
  double loadLStance;
  double ankleThetaEStanceToLStance;
  double kneeThetaESwingToLSwing;
  double kneeDThetaESwingToLSwing;
  double loadESwing;
  double loadEStance;
  double kneeThetaLSwingToEStance;

};


enum State {
    ESTANCE = 1,
    LSTANCE = 2,
    ESWING = 3,
    LSWING = 4,
};


struct FSMParameters {

  double bodyWeight;
  JointImpedanceSet kneeImpedance;
  JointImpedanceSet ankleImpedance;
  TransitionParameters transitionParameters;

};

struct FSM_Inputs {

  FSMParameters parameters;
  Sensors sensors;
  double time;

};

struct FSM_Outputs {

  State currentState;
  double timeInCurrentState;
  ImpedanceParameters kneeImpedance;
  ImpedanceParameters ankleImpedance;

};

#endif // FSMSTRUCTS_HPP
