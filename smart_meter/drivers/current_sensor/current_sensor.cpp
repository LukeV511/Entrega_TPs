//=====[Libraries]=============================================================

#include "mbed.h"

#include "current_sensor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn CurrentSensor(A1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void currentSensorInit()
{
}

void currentSensorUpdate()
{
}

float currentSensorRead()
{
    float isensitivity = 0.185;
    float current = CurrentSensor.read();
    float Current = (current-0.5)*3.3/isensitivity; // real current value calculation. Needs more testing and improvement
    return Current;
}

//=====[Implementations of private functions]==================================
