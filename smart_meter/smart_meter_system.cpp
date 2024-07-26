//=====[Libraries]=============================================================

#include "mbed.h"
#include "smart_meter_system.h"
#include "pc_serial_com.h"
#include "user_interface.h"
#include "energy.h"
#include "power.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void smart_meter_systemInit()
{
    powerInit();
    energyInit();
    user_interfaceInit();
}

void smart_meter_systemUpdate()
{
    powerUpdate();
    energyUpdate();
    pc_serial_comUpdate();
    user_interfaceUpdate();
    
    ThisThread::sleep_for(TIME_INCREMENT_MS);
}


//=====[Implementations of private functions]==================================
