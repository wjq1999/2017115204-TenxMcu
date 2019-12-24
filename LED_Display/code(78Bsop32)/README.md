# File Comment
## init.h
**File**: init.h  
**Brief**: System initialize head file

**Details**:  
- Declaration the SysInit() and VarsInit(), what is use to ensure systeam run normally 
- Define the necessary variable and data structure

## init.c
**File**: init.c  
**Brief**: System initialize source file

**Details**:
- Clear the watch dog peripheral, to ensure the  system could reset when program run unexpectedly
- Config GPIO peripheral. Set pin 10 to output
- No  variables need to initalize in this project

## display.h
**File**: display.h  
**Brief**: Led control head file

**Details**:
- Define the led pin macro and const data macro
- Define the action macro use to control led turn on or turn off

## includeAll.h
**File**: includeAll.h  
**Brief**: Include the project head file

## main.c
**File**: main.c  
**Brief**: The project main source file

**Details**: 
- Achieve flicker of led use gpio periheral
- Achieve delay function 

## mian.h
**File**: main.h  
**Brief**: project main head file

# Attention

The file comment also write at git commit. Move you mouse over the file commit to see then. 