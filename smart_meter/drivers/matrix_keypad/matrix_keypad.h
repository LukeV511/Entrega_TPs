//=====[#include guards - begin]===============================================

#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void matrix_keypadInit(int updateTime_ms);
char matrix_keypadUpdate();
char matrix_keypadScan();


//=====[#include guards - end]=================================================

#endif // MATRIX_KEYPAD_H