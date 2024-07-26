//=====[#include guards - begin]===============================================

#ifndef PC_SERIAL_COM_H
#define PC_SERIAL_COM_H

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void pc_serial_comInit();
void pc_serial_comStringWrite( const char* str );
void pc_serial_comUpdate();

//=====[#include guards - end]=================================================

#endif // PC_SERIAL_COM_H