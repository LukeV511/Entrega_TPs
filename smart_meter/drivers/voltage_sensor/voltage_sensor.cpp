//=====[Libraries]=============================================================

#include "mbed.h"

#include "voltage_sensor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn VoltageSensor(A0);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void voltageSensorInit()
{
}

void voltageSensorUpdate()
{
}

float voltageSensorRead()
{
    float vsensitivity = 1/110.5;
    float voltage = VoltageSensor.read();
    float Voltage = (voltage-0.606)*3.3/vsensitivity; //real voltage value calculation. Needs more testing and improvement
    return Voltage;
}

//=====[Implementations of private functions]==================================
