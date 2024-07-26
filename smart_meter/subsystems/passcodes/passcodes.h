//=====[#include guards - begin]===============================================

#ifndef PASSCODES_H
#define PASSCODES_H

//=====[Declaration of public defines]=========================================

#define CODE_LENGTH   4

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

bool codeMatch( char* code_to_compare );
extern char inputted_code[CODE_LENGTH];

//=====[#include guards - end]=================================================

#endif // PASSCODES_H