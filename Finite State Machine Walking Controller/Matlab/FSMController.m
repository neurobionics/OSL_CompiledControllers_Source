function [outputs] = FSMController(inputs)
% Inputs: FSMParameters (body weight, current impedance parameters, transition parameters), sensors (knee angle,
%         knee velocity, ankle angle, ankle velocity, fz), time
% 
% Persistent variable: current state
% 
% Based on the current state, readings from sensors, and if certain thresholds are met, the current state will
% either remain as the current state, or will change to the next state. Then, based on the current state, the
% new impedance parameters will be selected. Then the current state, the impedance parameters, and the time
% in the current state will be outputted. 
%
% Outputs: current state, time in current state, knee impedance parameters, ankle impedance parameters
%
% 
%
% Jace Derosia, Kevin Best
% October, 2023

% Unpack things for convenience 
sensors = inputs.sensors;
params = inputs.parameters;

persistent currentState previousState currentTimeInState time_last
if isempty(currentState)
    currentState = eStates.eStance;
    previousState = currentState;
    currentTimeInState = 0;
    time_last = inputs.time;
end

% Calculate time between calls
dt = inputs.time - time_last;
time_last = inputs.time;

% Finite State Machine
if currentState == eStates.eStance
    if(sensors.Fz < params.transitionParameters.loadLStance ...
            && sensors.ankleAngle > ...
            params.transitionParameters.ankleThetaEStanceToLStance ...
            && currentTimeInState > params.transitionParameters.minTimeInState)
        currentState = eStates.lStance;
    else
        currentState = eStates.eStance;
    end

elseif currentState == eStates.lStance
    if(sensors.Fz > params.transitionParameters.loadESwing && ...
            currentTimeInState > params.transitionParameters.minTimeInState)
        currentState = eStates.eSwing;
    else
        currentState = eStates.lStance;
    end

elseif currentState == eStates.eSwing
    if (sensors.kneeAngle > params.transitionParameters.kneeThetaESwingToLSwing ...
            && sensors.kneeVelocity < params.transitionParameters.kneeDThetaESwingToLSwing ...
            && currentTimeInState > params.transitionParameters.minTimeInState)

        currentState = eStates.lSwing;
    else
        currentState = eStates.eSwing;
    end

elseif currentState == eStates.lSwing
    if ((sensors.Fz < params.transitionParameters.loadEStance ...
            || sensors.kneeAngle < params.transitionParameters.kneeThetaLSwingToEStance) ...
            && currentTimeInState > params.transitionParameters.minTimeInState)
        currentState = eStates.eStance;
    else
        currentState = eStates.lSwing;
    end

else
    currentState = eStates.eStance;
end

% Select impedance parameters based on the current state
switch currentState
    case eStates.eStance
        kneeImpedance = params.kneeImpedance.earlyStance;
        ankleImpedance = params.ankleImpedance.earlyStance;
    case eStates.lStance
        kneeImpedance = params.kneeImpedance.lateStance;
        ankleImpedance = params.ankleImpedance.lateStance;
    case eStates.eSwing
        kneeImpedance = params.kneeImpedance.earlySwing;
        ankleImpedance = params.ankleImpedance.earlySwing;
    case eStates.lSwing
        kneeImpedance = params.kneeImpedance.lateSwing;
        ankleImpedance = params.ankleImpedance.lateSwing;
    otherwise
        kneeImpedance = params.kneeImpedance.earlyStance;
        ankleImpedance = params.ankleImpedance.earlyStance;
end

% Track time in state
if currentState == previousState
    currentTimeInState = currentTimeInState + dt;
else
    currentTimeInState = 0;
end

% Update previous state
previousState = currentState; 

% Write to output structures

outputs = FSM_Outputs();
outputs.currentState = currentState;
outputs.timeInCurrentState = currentTimeInState;
outputs.kneeImpedance = kneeImpedance;
outputs.ankleImpedance = ankleImpedance;
end




