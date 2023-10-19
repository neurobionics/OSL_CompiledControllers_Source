classdef JointImpedanceSet
    properties
        earlyStance ImpedanceParameters
        lateStance ImpedanceParameters
        earlySwing ImpedanceParameters
        lateSwing ImpedanceParameters
    end
    methods
        function obj = JointImpedanceSet()
            obj.earlyStance = ImpedanceParameters();
            obj.lateStance = ImpedanceParameters();
            obj.earlySwing = ImpedanceParameters();
            obj.lateSwing = ImpedanceParameters();
        end
    end
end