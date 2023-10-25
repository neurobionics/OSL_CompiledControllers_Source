#include "FSMStructs.hpp"

extern "C" void FSMController(FSM_Inputs *inputs, FSM_Outputs *outputs);
extern "C" void FSMController_initialize(void);
extern "C" void FSMController_terminate(void);