classdef TransitionParameters
    properties
        minTimeInState = 0.0;
        loadLStance (1,1) double = 0;
        ankleThetaEStanceToLStance (1,1) double = 0;
        kneeThetaESwingToLSwing (1,1) double = 0;
        kneeDThetaESwingToLSwing (1,1) double = 0;
        loadESwing (1,1) double = 0;
        loadEStance (1,1) double = 0;
        kneeThetaLSwingToEStance (1,1) = 0;
    end
end