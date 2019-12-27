# IR_KeyControlLED
The port multiplex use to detect the key press use interrupt requestion and toggle the LED status 

# Wiring diagram
Pin 10 use to get key status and display LED
![](../photo/wiring-diagram-2.jpg)

# File Comment
## init.h
**File**: init.h  
**Brief**: System initialize head file

**Details**:  
- Declaration the *SysInit()* and *VarsInit()*, what is use to ensure systeam run normally 
- Define the necessary variable and data structure

## init.c
**File**: init.c  
**Brief**: System initialize source file

**Details**:
- Clear the watch dog peripheral, to ensure the  system could reset when program run unexpectedly
- Config GPIO peripheral. Set pin 10 to output
- Config TIMER peripheral. Initialize some parameter 
- No variables need to initalize in this project

## includeAll.h
**File**: includeAll.h 
**Brief**: Include the project head file

## display.h
**File**: display.h  
**Brief**: Led control head file

**Details**:
- Define the led pin macro and const data macro
- Define the action macro use to control LED turn on or turn off
- Define the action macro use to reversal the LED status

## key.h
**File**: key.h  
**Brief**: Key control head file

**Details**:
- Define the key pin macro
- Define the key status macro

## key.c
**File**: key.c  
**Brief**: Key control source file

**Details**:
- Change pin 10 function output to input when the timer count complete 
- Scanning the key status
- Reset pin to output when scan down 
- Stable key press. Use raise edge to enter the *GetKeys()* first IF statement and fall edge update the key status

## isr.h
**File**: isr.h  
**Brief**: Interrupt requestion handler head file

**Details**:
- Define the timer flag variable to indicate time is count down

## isr.c
**File**: isr.c  
**Brief**: Interrupt requestion handler source file

**Details**:
- Contain interrupt requestion handler of INT, TIMER, UART, ADC and so on peripherals 
- Once the TIMER2 count is complete, the flag variable will be set. So check out this variable, we could know that count complete or not 

## mian.h
**File**: main.h  
**Brief**: project main head file

**Details**: 
- Define count time macro
- Declare system framework function

## main.c
**File**: main.c  
**Brief**: The project main source file

**Details**: 
- Scan the key status every 5ms
- Once the key is pressed, the LED status will toggle 
