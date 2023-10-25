# Source Code for `opensourceleg` example controllers
This repo contains the source code for the example controllers shipped with the `opensourceleg` library. You can install the `opensourceleg` library using `pip install opensourceleg` and you can see the examples in the [opensourceleg respository](https://github.com/neurobionics/opensourceleg/tree/main/examples). 

## Contents
### Finite State Machine Walking Controller
We provide the source code for a standard finite state machine walking controller in two languages (C++ and MATLAB). 
The state machine has four states, two for stance and two for swing. Constant impedance parameters for each joint and state can be tuned to give the desired walking gait. The controller also has tunable transition parameters to allow timing flexibility for different tasks. 

![Schematic of the Finite State Machine Logic](/assets/FSM_Diagram.svg)

Please reference the readmes for each implementation for more information and compilation instructions:
- [C++](/Finite%20State%20Machine%20Walking%20Controller/CPP/readme.md)
- [MATLAB](/Finite%20State%20Machine%20Walking%20Controller/Matlab/readme.md)