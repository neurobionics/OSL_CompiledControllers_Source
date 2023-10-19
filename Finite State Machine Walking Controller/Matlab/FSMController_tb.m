clear
close all

inputs = FSM_Inputs();
parameters = FSMParameters();
parameters.bodyWeight = 60 * 9.8;

% Example transition parameters
parameters.transitionParameters.minTimeInState = 2.0;
parameters.transitionParameters.loadLStance = 10;



parameters.kneeImpedance.earlyStance.stiffness = 99.372;
parameters.kneeImpedance.earlyStance.damping = 3.180;
parameters.kneeImpedance.earlyStance.eqAngle = 5;
parameters.transitionParameters.loadLStance = -1.0 * parameters.bodyWeight * 0.25;
% params.eStanceParams.ankleThetaEStanceToLStance = 6.0;
% params.eStanceParams.ankleK = 19.874;
% params.eStanceParams.ankleB = 0;
% params.eStanceParams.ankleTheta = -2;
% 
% params.lStanceParams.kneeK = 99.372;
% params.lStanceParams.kneeB = 1.272;
% params.lStanceParams.kneeTheta = 8;
% params.lStanceParams.loadESwing = -1.0 * params.bodyWeight * 0.15;
% params.lStanceParams.ankleK = 79.498;
% params.lStanceParams.ankleB = 0.063;
% params.lStanceParams.ankleTheta = -20;
% 
% params.eSwingParams.kneeK = 39.749;
% params.eSwingParams.kneeB = 0.063;
% params.eSwingParams.kneeTheta = 60;
% params.eSwingParams.kneeThetaESwingToLSwing = 50;
% params.eSwingParams.kneeDThetaESwingToLSwing = 3;
% params.eSwingParams.ankleK = 7.949;
% params.eSwingParams.ankleB = 0.0;
% params.eSwingParams.ankleTheta = 25;
% 
% params.lSwingParams.kneeK = 15.899;
% params.lSwingParams.kneeB = 3.816;
% params.lSwingParams.kneeTheta = 5;
% params.lSwingParams.loadEStance = -1.0 * params.bodyWeight * 0.4;
% params.lSwingParams.kneeThetaLSwingToEStance = 30;
% params.lSwingParams.ankleK = 7.949;
% params.lSwingParams.ankleB = 0.0;
% params.lSwingParams.ankleTheta = 15;

outputs = FSMController(inputs);


