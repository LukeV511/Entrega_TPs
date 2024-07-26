//=====[Libraries]=============================================================

#include "mbed.h"

#include "passcodes.h"
#include "user_interface.h"
#include "pc_serial_com.h"
#include "matrix_keypad.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of private global variables]============

static char reset_code[CODE_LENGTH] = { '1', '3', '7', '9' };
char inputted_code[CODE_LENGTH];

//=====[Declarations (prototypes) of private functions]========================

bool codeMatch( char* code_to_compare );

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================

bool codeMatch( char* code_to_compare ) //function to check if the inputted code is correct
{

    int i;
    for (i = 0; i < CODE_LENGTH; i++) { 
        if ( reset_code[i] != code_to_compare[i] ) {
            return false;
        }
    }
    return true; //otherwise, it returns true
}