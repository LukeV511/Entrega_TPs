//=====[Libraries]=============================================================

#include "mbed.h"

#include "smart_meter_system.h"
#include "energy.h"
#include "power.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static float energy = 0;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void energyInit() // initialization of energy value at zero
{
    energy=0;
}

void energyUpdate()
{
    energy = energy + (instPowerRead() * TIME_INCREMENT_MS/3600000) ; 
    // energy in Wh calculation (3600000 ms = 1hr)
}


float energyRead()
 {
      return energy;
 }


//=====[Implementations of private functions]==================================
