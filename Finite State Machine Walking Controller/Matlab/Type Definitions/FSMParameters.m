classdef FSMParameters
    properties
        bodyWeight (1,1) double 
        kneeImpedance  JointImpedanceSet;
        ankleImpedance JointImpedanceSet;
        transitionParameters TransitionParameters;
    end
    methods
        function obj = FSMParameters()
            obj.bodyWeight = 0;
            obj.kneeImpedance = JointImpedanceSet();
            obj.ankleImpedance = JointImpedanceSet();
            obj.transitionParameters = TransitionParameters();
        end
    end
end
