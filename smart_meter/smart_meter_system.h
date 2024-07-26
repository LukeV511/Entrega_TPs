//=====[#include guards - begin]===============================================

#ifndef SMART_METER_SYSTEM_H
#define SMART_METER_SYSTEM_H

//=====[Declaration of public defines]=========================================

#define TIME_INCREMENT_MS 10 // system refresh rate

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void smart_meter_systemInit();
void smart_meter_systemUpdate();

//=====[#include guards - end]=================================================

#endif // SMART_METER_SYSTEMY_H