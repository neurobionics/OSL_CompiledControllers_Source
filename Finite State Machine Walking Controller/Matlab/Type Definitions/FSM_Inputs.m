classdef FSM_Inputs
    properties
        parameters
        sensors
        time
    end
    methods
        function obj = FSM_Inputs()
            obj.parameters = FSMParameters();
            obj.sensors = Sensors();
            obj.time = 0.0;
        end
    end
end

