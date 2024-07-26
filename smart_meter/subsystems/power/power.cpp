//=====[Libraries]=============================================================

#include "mbed.h"

#include "power.h"
#include "voltage_sensor.h"
#include "current_sensor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static float maxPower = 0;
static float instPower = 0;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void powerInit()    // initialization of intsPower and maxPower values at zero
{
    maxPower = 0;
    instPower = 0;
}


void powerUpdate()
{
    instPower = voltageSensorRead() * currentSensorRead(); // instantaneous Power and maximum power registered calculation
    if (instPower>maxPower){
        maxPower=instPower;
     }  
}


float maxPowerRead()
 {
      return maxPower;
 }

 float instPowerRead()
{
    return instPower;
}


//=====[Implementations of private functions]==================================
