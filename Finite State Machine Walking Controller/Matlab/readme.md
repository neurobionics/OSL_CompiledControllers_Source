# Finite State Machine Controller - MATLAB Implementation
This section of the repository contains the source code for the MATLAB implementation of the Finite State Machine Walking Controller. 

## Source Files
The source files consist of a main function `FSMController.m`, a setup script `FSMController_setup.m`, and a `Type Definitions` directory. The main function `FSMController.m` is what our OSL code will call each time through the control loop to execute the state machine logic and calculate knee and ankle impedance values. The setup script is used to configure the search path and to define the function's input and output variables for code generation (see below). 

### Type Definitions
To define input and output types similar to how one would define them in `C` or `C++`, we utilize MATLAB classes. To define a new class, make a new file containing the class name, a properties block, and a single constructor method. For example, we define the `ImpedanceParameters` class as

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/main/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/ImpedanceParameters.m#L1

In the properties block of this file, we define that the `ImpedanceParameters` structure has three fields, `stiffness`, `damping`, and `eqAngle`. Next in the `methods` block, we create a constructor that initializes each field to a value. Since we don't specify a data type, MATLAB assumes that they are `doubles`. 

> **_NOTE:_** The constructor is simply a method with the same name as the class that returns `obj`. If you are unfamiliar with object oriented programming in MATLAB and Class syntax, check out the simple class definition and explanation on the [MathWorks Help Center](https://www.mathworks.com/help/matlab/matlab_oop/user-defined-classes.html). 

We then make another class called `JointImpedanceSet` that contains four `ImpedanceParameter` objects, one for each state in the state machine.

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/main/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/JointImpedanceSet.m#L1

Likewise, we create a `TransitionParameters` class to hold all of the state machine's transition parameters and a `Sensors` class to hold the sensor data. 

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/main/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/TransitionParameters.m#L1

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/eb5e9d8503c824d5ebe9170c34fe1d6215663e30/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/Sensors.m#L1


## Code Generation and Compilation