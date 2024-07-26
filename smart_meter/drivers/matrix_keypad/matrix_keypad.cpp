//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "matrix_keypad.h"
#include "energy.h"

//=====[Declaration of private defines]========================================

#define DEBOUNCE_KEY_TIME_MS 50
#define MATRIX_KEYPAD_NUMBER_OF_ROWS    4
#define MATRIX_KEYPAD_NUMBER_OF_COLS    4

#define C1 PB_12
#define C2 PB_13
#define C3 PB_15
#define C4 PC_6
#define R1 PA_15
#define R2 PC_7
#define R3 PB_5
#define R4 PB_3         //definition of pins that will work as the rows and columns of the keypad

//=====[Declaration of private data types]=====================================

typedef enum {
    MATRIX_KEYPAD_SCANNING,
    MATRIX_KEYPAD_DEBOUNCE,
    MATRIX_KEYPAD_KEY_HOLD_PRESSED
} matrix_keypadState_t;                 //states definition for implementation of a Finite State Machine

//=====[Declaration and initialization of public global objects]===============

DigitalIn columns[] = {DigitalIn(C1), DigitalIn(C2), DigitalIn(C3), DigitalIn(C4)};
DigitalOut rows[] = {DigitalOut(R1), DigitalOut(R2), DigitalOut(R3), DigitalOut(R4)};

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static matrix_keypadState_t matrix_keypadState;
static int timeIncrement_ms = 0;

//=====[Declarations (prototypes) of private functions]========================

char matrix_keypadScan();
static void matrix_keypadReset();

//=====[Implementations of public functions]===================================

void matrix_keypadInit(int updateTime_ms)
{
    timeIncrement_ms = updateTime_ms;
    matrix_keypadState = MATRIX_KEYPAD_SCANNING;
    int pinIndex = 0;
    for( pinIndex=0; pinIndex<MATRIX_KEYPAD_NUMBER_OF_COLS; pinIndex++ ) {
        (columns[pinIndex]).mode(PullUp);  //definition for column pins to stay in state ON/HIGH until a button is pressed
    }
}

char matrix_keypadUpdate()
{
    static int accumulated_debounce_time = 0;
    static char matrix_keypad_last_key_pressed = '\0';
    
    char key_detected = '\0';
    char key_released = '\0';

    switch(matrix_keypadState){         //implementation of Finite State Machine (FSM)

        case MATRIX_KEYPAD_SCANNING:    //the system will constantly scan for pressed keys
            key_detected = matrix_keypadScan();
            if(key_detected != '\0'){
                matrix_keypad_last_key_pressed = key_detected;
                accumulated_debounce_time = 0;
                matrix_keypadState = MATRIX_KEYPAD_DEBOUNCE; //if a key is pressed, the FSM will enter in DEBOUNCE state
            }
            break;
        
        case MATRIX_KEYPAD_DEBOUNCE:    //the system will wait some time to ignore glitches and mechanical debounces from the keypad
            if (accumulated_debounce_time >= DEBOUNCE_KEY_TIME_MS){
                key_detected = matrix_keypadScan();
                if (key_detected == matrix_keypad_last_key_pressed){
                    matrix_keypadState = MATRIX_KEYPAD_KEY_HOLD_PRESSED;
                    //if the dettected key is the same after the debounce time, the FSM will enter in KEY HOLD PRESSED state
                } else {
                    matrix_keypadState = MATRIX_KEYPAD_SCANNING;
                    //if the detected key is not the same after the debounce time, the detection was probably a glitch or a debounce,
                    //so it will be ignored and the FSM will go back to SCANNNING state
                }
            }
            accumulated_debounce_time = accumulated_debounce_time + timeIncrement_ms;
            break;

        case MATRIX_KEYPAD_KEY_HOLD_PRESSED:    //the system will return the pressed key once it detects it has stopped being pressed.
            key_detected = matrix_keypadScan();
            if(key_detected != matrix_keypad_last_key_pressed){
                if(key_detected == '\0'){
                    key_released = matrix_keypad_last_key_pressed;
                }
                matrix_keypadState = MATRIX_KEYPAD_SCANNING; 
                //after detecting that the key stopped being pressed, the system returns to SCANNING state
            }
            break;
        
        default:
            matrix_keypadReset();
            break;
    }
    return key_released;
}
//=====[Implementations of private functions]==================================

char matrix_keypadScan() 
    {
    int row = 0;
    int col = 0;
    int i = 0; 

    //definition of the array with the values of the matrix keypad
    char matrixKeypadIndexToCharArray[] = {
        '1', '2', '3', 'A',
        '4', '5', '6', 'B',
        '7', '8', '9', 'C',
        '*', '0', '#', 'D',
    };

    for( row=0; row<MATRIX_KEYPAD_NUMBER_OF_ROWS; row++ ) {

        for( i=0; i<MATRIX_KEYPAD_NUMBER_OF_ROWS; i++ ) {
            rows[i] = ON;
        }

        rows[row] = OFF;

        for( col=0; col<MATRIX_KEYPAD_NUMBER_OF_COLS; col++ ) {
            if( columns[col] == OFF ) { //if a button is pressed, its corresponding column pin will go OFF/LOW
                return matrixKeypadIndexToCharArray[
                    row*MATRIX_KEYPAD_NUMBER_OF_ROWS + col];
                    //the function will return the corresponding element of the array based on the number of row and column detected
            }
        }
    }
    return '\0'; //if no button is pressed, the function returns a null value
}

static void matrix_keypadReset()
{
    matrix_keypadState = MATRIX_KEYPAD_SCANNING;
}