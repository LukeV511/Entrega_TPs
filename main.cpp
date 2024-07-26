#include "mbed.h"
#include "smart_meter_system.h"

//main code

int main()
{   
    smart_meter_systemInit();
    
    while (true) {
                  
        smart_meter_systemUpdate();
    }
}