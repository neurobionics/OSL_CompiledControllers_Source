classdef ImpedanceParameters
    properties
        stiffness
        damping
        eqAngle
    end
    methods
        function obj = ImpedanceParameters()
            obj.stiffness = 0;
            obj.damping = 0;
            obj.eqAngle = 0; 
        end
    end           
end