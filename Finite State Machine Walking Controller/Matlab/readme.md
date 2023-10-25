# Finite State Machine Controller - MATLAB Implementation
This section of the repository contains the source code for the MATLAB implementation of the Finite State Machine Walking Controller. The first subsection details the source files and how we implemented the finite state machine logic in MATLAB. If you're comfortable with writing object-oriented MATLAB code, you can skip down to the [Code Generation and Compilation Section](#code-generation-and-compilation).

## Prerequisites
- MATLAB (any somewhat recent version will do)
- [MATLAB Coder](https://www.mathworks.com/products/matlab-coder.html)[^1]
- [MATLAB Raspberry Pi Hardware Support Package](https://www.mathworks.com/hardware-support/raspberry-pi-matlab.html)[^1]

> **_NOTE_**: MATLAB Coder and the Hardware Support Package can be installed using the `Add-On Explorer` in MATLAB.

## Source Files
The source files consist of a main function `FSMController.m`, a setup script `FSMController_setup.m`, and a `Type Definitions` directory. The main function `FSMController.m` is what our OSL code will call each time through the control loop to execute the state machine logic and calculate knee and ankle impedance values. The setup script is used to configure the search path and to define the function's input and output variables for code generation (see below). 

### Type Definitions
To define input and output types similar to how one would define them in `C` or `C++`, we utilize MATLAB classes. To define a new class, make a new file containing the class name, a properties block, and a single constructor method. For example, we define the `ImpedanceParameters` class as

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/ccc86b909c5e101d1e802491e03dbcf2ebcf83e4/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/ImpedanceParameters.m#L1-L14

In the properties block of this file, we define that the `ImpedanceParameters` structure has three fields, `stiffness`, `damping`, and `eqAngle`. Next in the `methods` block, we create a constructor that initializes each field to a value. Since we don't specify a data type, MATLAB assumes that they are `doubles`. 

> **_NOTE:_** The constructor is simply a method with the same name as the class that returns `obj`. If you are unfamiliar with object oriented programming in MATLAB and Class syntax, check out the simple class definition and explanation on the [MathWorks Help Center](https://www.mathworks.com/help/matlab/matlab_oop/user-defined-classes.html). 

We then make another class called `JointImpedanceSet` that contains four `ImpedanceParameter` objects, one for each state in the state machine.

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/97973ee80d8a63ef02bea106b8a8064f2c2b013e/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/JointImpedanceSet.m#L1-L16

Likewise, we create a `TransitionParameters` class to hold all of the state machine's transition parameters and a `Sensors` class to hold the sensor data. 

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/ccc86b909c5e101d1e802491e03dbcf2ebcf83e4/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/TransitionParameters.m#L1-L12

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/eb5e9d8503c824d5ebe9170c34fe1d6215663e30/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/Sensors.m#L1-L18

Finally, we define our `FSM_Inputs` type using the types we just defined. 

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/97973ee80d8a63ef02bea106b8a8064f2c2b013e/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/FSM_Inputs.m#L1-14

So far, all the types that we have defined have been `doubles`. Next we're going to define an enumeration for the active state name called `eStates`. 

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/97973ee80d8a63ef02bea106b8a8064f2c2b013e/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/eStates.m#L1-L8

We tell this class to inheret (via the `< int32` command) from the integer class, as C++ represents enumerations as integers and we want the MATLAB implementation to be interchangable with the C++ representation in terms of inputs and outputs.

> **_NOTE:_** For more details on enumeration classes in MATALB, please see this [help page](https://www.mathworks.com/help/matlab/matlab_oop/enumerations.html).

Finally, we define the output type `FSM_Outputs` to contain the active impedance parameters for both joints, the time elapsed in the current state, and the enum of the current state.

https://github.com/neurobionics/OSL_CompiledControllers_Source/blob/97973ee80d8a63ef02bea106b8a8064f2c2b013e/Finite%20State%20Machine%20Walking%20Controller/Matlab/Type%20Definitions/FSM_Outputs.m#L1-L16

### Main Function
The main function `[outputs] = FSMController(inputs)` takes inputs of the `FSM_Inputs.m` type and returns a structure of the `FSM_Outputs.m` type. In the first few lines of the file, we unpack things from the inputs structure for convenience and we declare persistent variables. Persistent variables are used in MATLAB to retian data from one function call to the next, similar to `static` in `C` (see [Mathworks Help Center](https://www.mathworks.com/help/matlab/ref/persistent.html)). We want to keep track of which state we're in, as well as how long we've been there, so we declare these inputs:
```matlab
% Unpack things for convenience 
sensors = inputs.sensors;
params = inputs.parameters;

persistent currentState currentTimeInState time_last
if isempty(currentState)
    currentState = eStates.eStance;
    currentTimeInState = 0;
    time_last = inputs.time;
end
```

Next we have our main state machine logic. Each branch of the `if` statement checks the transition parameters to exit each state. 
```matlab
% Finite State Machine
if currentState == eStates.eStance
    if(sensors.Fz < params.transitionParameters.loadLStance ...
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

    if ((sensors.Fz < params.transitionParameters.loadEStance ...
            || sensors.kneeAngle < params.transitionParameters.kneeThetaLSwingToEStance) ...
            && currentTimeInState > params.transitionParameters.minTimeInState)
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
```

Finally, we choose between sets of impedance parameters based on the current states and write to the outputs structure. 

```matlab
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
```

### Setup Script
The purpose of the setup script is to configure the MATLAB path and to make a test call to the main function. In this case, our setup file is quite simple. We reset the workspace, add the `Type Defintions` directory to the path, and call the main function once. 
```matlab
clear all
close all

addpath("Type Definitions")
inputs = FSM_Inputs();

outputs = FSMController(inputs);
```

And that is all of the source files. Now we'll move on to using MATLAB Coder and generating the shared object library. 
## Code Generation and Compilation
We will use [MATLAB Coder](https://www.mathworks.com/products/matlab-coder.html) to convert the function `FSMController.m` into `C` and then compile it into a shared object library for the Raspberry Pi. After ensuring all [prerequisites are installed](#prerequisites), perform the following steps in MATLAB with the working directory set to ``...\OSL_CompiledControllers_Source\Finite State Machine Walking Controller\Matlab``. 

1. Type `coder` into the command window and press enter. 
2. Enter `FSMController` for the function name to install and press enter. Your screen should look like this:![Screenshot of MATLAB Coder](./assets/coder_step2.png)
3. In the next page, type `FSMController_setup` into the field and press `Autodefine Input Types`. MATLAB will then call this script to figure out the structure of the functions inputs and outputs. If successful, your screen will look like this the following. Then click next.
![Screenshot of MATLAB Coder](./assets/coder_step3.png)
4. The next page is the `Check for Issues` page. You can click the `Check for Issues` button to ensure no odd behavior in the generated code. 
![Screenshot of MATLAB Coder](./assets/coder_step4.png)
5. The next page is the code generation page. Set the Build type to be a `Dynamic Library` and select `Raspberry Pi` as the Hardware Board. 
![Screenshot of MATLAB Coder](./assets/coder_step5.png)
6. Click on `More Settings` and navigate to the `Hardware` tab. Enter the IP address and credentials for your Raspberry Pi. Note that in order to compile the shared object, your PC and Pi must both be on the same network. Click `Close` and then click `Generate`.
![Screenshot of MATLAB Coder](./assets/coder_step6.png)
7. You should get a message that code generation was successful. You can now copy the generated library `FSMController.so` to wherever you want to use it. You'll find it in the specified `Build Directory` (configured right below the login credentials) on the Pi. 