//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"
#include "smart_meter_system.h"
#include "passcodes.h"
#include "matrix_keypad.h"
#include "energy.h"
#include "power.h"
#include "pc_serial_com.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn B1_USER(BUTTON1); //boton integrado de la placa a usar para resetear contador de energia
DigitalOut Led1(LED1); //LED integrado de la placa a usar para indicar programa corriendo
DigitalOut Led2(LED2); //LED integrado de la placa a usar para indicar reseteo de energia
DigitalOut Led3(LED3); //LED integrado de la placa a usar para indicar codigo ingresado incorrecto
//for some reason, naming leds differently with more appropiate names causes issues with the serial print

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//char inputted_code[CODE_LENGTH];


//=====[Declaration and initialization of private global variables]============

static bool code_complete = false;
static bool code_is_correct = false;
static int number_of_code_chars = 0;

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceMatrixKeypadUpdate();



//=====[Implementations of public functions]===================================

void user_interfaceInit()
{   
    Led1 = ON;
    Led3 = OFF;
    Led2 = OFF;
    matrix_keypadInit( TIME_INCREMENT_MS );
}

void user_interfaceUpdate()
{
    userInterfaceMatrixKeypadUpdate();
    
}

//=====[Implementations of private functions]==================================

static void userInterfaceMatrixKeypadUpdate()
{
    char keyReleased = matrix_keypadUpdate();
    char inputted_key = '\0';
    if( keyReleased != '\0' && keyReleased != '#') {
                inputted_key = keyReleased;
                Led2 = OFF;
                Led3 = OFF;
                inputted_code[number_of_code_chars] = inputted_key;
                number_of_code_chars++;
                if ( number_of_code_chars >= CODE_LENGTH ){
                    code_complete = true;
                    number_of_code_chars = 0;
                }        
    }
    if( keyReleased == '#' ) { //the key # is used as an enter button. If the code is completed, it will check if its correct
                        if( code_complete == true){
                            code_is_correct = codeMatch(inputted_code); //checks if code is correct
                            if (code_is_correct == true){ 
                                Led2 = ON; //if the inputted code is correct, the resetLed turns ON
                                energyInit(); //if the inputted code is correct, energy and maxPower are reseted
                                powerInit();
                                code_complete = false;
                                number_of_code_chars = 0;
                                int i; //reset of the inputted_code array
                                for (i=0; i < CODE_LENGTH; i++ ){
                                    inputted_code[i]='\0';
                                }
                            }
                            else if (code_is_correct == false) {                 
                                Led3 = ON; //if the inputted code is incorrect, the incorrectCodeLed turns on
                                code_complete = false;
                                number_of_code_chars = 0;
                                int i; //reset of the inputted_code array
                                for (i=0; i < CODE_LENGTH; i++ ){
                                        inputted_code[i]='\0';
                                    }
                            }
                        }
                        else if ( code_complete == false){ //if the code is incomplete and the user presses #, the incorrectCode turns on
                            Led3 = ON;
                            number_of_code_chars = 0;
                            int i;
                            for (i=0; i < CODE_LENGTH; i++ ){
                                inputted_code[i]='\0';
                            }
                        }
    }
}