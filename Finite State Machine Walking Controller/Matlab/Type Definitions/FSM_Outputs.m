classdef FSM_Outputs
    properties
        currentState
        timeInCurrentState
        kneeImpedance
        ankleImpedance
    end
    methods
        function obj = FSM_Outputs
            obj.currentState = eStates.eStance;
            obj.timeInCurrentState = 0.0;
            obj.ankleImpedance = ImpedanceParameters();
            obj.kneeImpedance = ImpedanceParameters(); 
        end
    end
end