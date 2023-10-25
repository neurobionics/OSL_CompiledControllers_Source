clear
close all

inputs = FSM_Inputs();
params = FSMParameters();
params.bodyWeight = 60 * 9.8;

params.transitionParameters.minTimeInState = 2.0;
params.transitionParameters.loadLStance = 10;

params.kneeImpedance.earlyStance.stiffness = 99.372;
params.kneeImpedance.earlyStance.damping = 3.180;
params.kneeImpedance.earlyStance.eqAngle = 5;
params.transitionParameters.loadLStance = -1.0 * params.bodyWeight * 0.25;
params.transitionParameters.ankleThetaEStanceToLStance = 6.0;
params.ankleImpedance.earlyStance.stiffness = 19.874;
params.ankleImpedance.earlyStance.damping = 0;
params.ankleImpedance.earlyStance.eqAngle = -2;

params.kneeImpedance.lateStance.stiffness = 99.372;
params.kneeImpedance.lateStance.damping = 1.272;
params.kneeImpedance.lateStance.eqAngle = 8;
params.transitionParameters.loadESwing = -1.0 * params.bodyWeight * 0.15;
params.ankleImpedance.lateStance.stiffness = 79.498;
params.ankleImpedance.lateStance.damping = 0.063;
params.ankleImpedance.lateStance.eqAngle = -20;

params.kneeImpedance.earlySwing.stiffness = 39.749;
params.kneeImpedance.earlySwing.damping = 0.063;
params.kneeImpedance.earlySwing.eqAngle = 60;
params.transitionParameters.kneeThetaESwingToLSwing = 50;
params.transitionParameters.kneeDThetaESwingToLSwing = 3;
params.ankleImpedance.earlySwing.stiffness = 7.949;
params.ankleImpedance.earlySwing.damping = 0.0;
params.ankleImpedance.earlySwing.eqAngle = 25;

params.kneeImpedance.lateSwing.stiffness = 15.899;
params.kneeImpedance.lateSwing.damping = 3.816;
params.kneeImpedance.lateSwing.eqAngle = 5;
params.transitionParameters.loadEStance = -1.0 * params.bodyWeight * 0.4;
params.transitionParameters.kneeThetaLSwingToEStance = 30;
params.ankleImpedance.lateSwing.stiffness = 7.949;
params.ankleImpedance.lateSwing.damping = 0.0;
params.ankleImpedance.lateSwing.eqAngle = 15;
inputs.parameters = params;

outputs = FSMController(inputs);


