classdef Sensors
    properties
        kneeAngle
        ankleAngle
        kneeVelocity
        ankleVelocity
        Fz
    end
    methods 
        function obj = Sensors()
            obj.kneeAngle = 0.0;
            obj.ankleAngle = 0.0;
            obj.kneeVelocity = 0.0;
            obj.ankleVelocity = 0.0; 
            obj.Fz = 0.0; 
        end
    end
end
