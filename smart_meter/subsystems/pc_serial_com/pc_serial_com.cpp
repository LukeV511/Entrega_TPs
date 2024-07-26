//=====[Libraries]=============================================================

#include "mbed.h"
#include "smart_meter_system.h"

#include "user_interface.h"
#include "energy.h"
#include "power.h"
#include "voltage_sensor.h"
#include "current_sensor.h"
#include "matrix_keypad.h"
#include "passcodes.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

float accumulated_time = 0;

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void pc_serial_comInit()
{
}

void pc_serial_comStringWrite(const char* str )
{
    uartUsb.write(str, strlen(str));
}

void pc_serial_comUpdate()
{
    accumulated_time = accumulated_time + TIME_INCREMENT_MS;
    if (accumulated_time == (100 * TIME_INCREMENT_MS)) // the output is printed every second through serial port.
    {
        char str[100] = "";

        sprintf(str,"Voltaje: %.2f V   Corriente: %.2f A   Potencia: %.2f W \n\
        Energia: %.2f Wh   Maxima Potencia: %.2f W    Passcode: %s \n" , voltageSensorRead(), currentSensorRead(),\
        instPowerRead(), energyRead(), maxPowerRead(), inputted_code);
        
        pc_serial_comStringWrite(str);
        accumulated_time=0;
    }
}

//=====[Implementations of private functions]==================================
