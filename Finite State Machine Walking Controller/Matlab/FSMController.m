function [outputs] = FSMController(inputs)
% TODO: Jace to add comment summarizing the function
% TODO: Jace to add his contact info here and attribution info

% Unpack things for convenience 
sensors = inputs.sensors;
params = inputs.parameters;

persistent currentState currentTimeInState time_last
if isempty(currentState)
    currentState = eStates.eStance;
    currentTimeInState = 0;
    time_last = inputs.time;
end

% Calculate time between calls
dt = inputs.time - time_last;
time_last = inputs.time;

% Finite State Machine
if currentState == eStates.eStance
    if(sensors.Fz > params.transitionParameters.loadLStance ...
            && sensors.ankleAngle > ...
            params.transitionParameters.ankleThetaEStanceToLStance ...
            && currentTimeInState > params.transitionParameters.minTimeInState)
        currentState = eStates.lStance;
        currentTimeInState = 0.0;
    else
        currentState = eStates.eStance;
        currentTimeInState = currentTimeInState + dt;
    end

elseif currentState == eStates.lStance
    if(sensors.Fz > params.transitionParameters.loadESwing && ...
            currentTimeInState > params.transitionParameters.minTimeInState)
        currentState = eStates.eSwing;
        currentTimeInState = 0.0;
    else
        currentState = eStates.lStance;
        currentTimeInState = currentTimeInState + dt;
    end

elseif currentState == eStates.eSwing
    if (sensors.kneeAngle > params.transitionParameters.kneeThetaESwingToLSwing ...
            && sensors.kneeVelocity < params.transitionParameters.kneeDThetaESwingToLSwing ...
            && currentTimeInState > params.transitionParameters.minTimeInState)

        currentState = eStates.lSwing;
        currentTimeInState = 0.0;

    else
        currentState = eStates.eSwing;
        currentTimeInState = currentTimeInState + dt;

    end

elseif currentState == eStates.lSwing

    if (sensors.Fz < params.transitionParameters.loadEStance ...
            || sensors.kneeAngle < params.transitionParameters.kneeThetaLSwingToEStance)
        currentState = eStates.eStance;
        currentTimeInState = 0.0;
    else
        currentState = eStates.lSwing;
        currentTimeInState = currentTimeInState + dt;

    end

else
    currentState = eStates.eStance;
    currentTimeInState = currentTimeInState + dt;
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

% Write to output structures

outputs = FSM_Outputs();
outputs.currentState = currentState;
outputs.timeInCurrentState = currentTimeInState;
outputs.kneeImpedance = kneeImpedance;
outputs.ankleImpedance = ankleImpedance;
end



