/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1507
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set inpShockSensor aliases
#define inpShockSensor_TRIS               TRISA2
#define inpShockSensor_LAT                LATA2
#define inpShockSensor_PORT               RA2
#define inpShockSensor_WPU                WPUA2
#define inpShockSensor_ANS                ANSA2
#define inpShockSensor_SetHigh()    do { LATA2 = 1; } while(0)
#define inpShockSensor_SetLow()   do { LATA2 = 0; } while(0)
#define inpShockSensor_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define inpShockSensor_GetValue()         RA2
#define inpShockSensor_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define inpShockSensor_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define inpShockSensor_SetPullup()    do { WPUA2 = 1; } while(0)
#define inpShockSensor_ResetPullup()   do { WPUA2 = 0; } while(0)
#define inpShockSensor_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define inpShockSensor_SetDigitalMode()   do { ANSA2 = 0; } while(0)
// get/set inpValveMonitoringSensor aliases
#define inpValveMonitoringSensor_TRIS               TRISA4
#define inpValveMonitoringSensor_LAT                LATA4
#define inpValveMonitoringSensor_PORT               RA4
#define inpValveMonitoringSensor_WPU                WPUA4
#define inpValveMonitoringSensor_ANS                ANSA4
#define inpValveMonitoringSensor_SetHigh()    do { LATA4 = 1; } while(0)
#define inpValveMonitoringSensor_SetLow()   do { LATA4 = 0; } while(0)
#define inpValveMonitoringSensor_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define inpValveMonitoringSensor_GetValue()         RA4
#define inpValveMonitoringSensor_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define inpValveMonitoringSensor_SetDigitalOutput()   do { TRISA4 = 0; } while(0)

#define inpValveMonitoringSensor_SetPullup()    do { WPUA4 = 1; } while(0)
#define inpValveMonitoringSensor_ResetPullup()   do { WPUA4 = 0; } while(0)
#define inpValveMonitoringSensor_SetAnalogMode()   do { ANSA4 = 1; } while(0)
#define inpValveMonitoringSensor_SetDigitalMode()   do { ANSA4 = 0; } while(0)
// get/set outValveState aliases
#define outValveState_TRIS               TRISA5
#define outValveState_LAT                LATA5
#define outValveState_PORT               RA5
#define outValveState_WPU                WPUA5
#define outValveState_SetHigh()    do { LATA5 = 1; } while(0)
#define outValveState_SetLow()   do { LATA5 = 0; } while(0)
#define outValveState_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define outValveState_GetValue()         RA5
#define outValveState_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define outValveState_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define outValveState_SetPullup()    do { WPUA5 = 1; } while(0)
#define outValveState_ResetPullup()   do { WPUA5 = 0; } while(0)
// get/set inpStartSolenoid aliases
#define inpStartSolenoid_TRIS               TRISB4
#define inpStartSolenoid_LAT                LATB4
#define inpStartSolenoid_PORT               RB4
#define inpStartSolenoid_WPU                WPUB4
#define inpStartSolenoid_ANS                ANSB4
#define inpStartSolenoid_SetHigh()    do { LATB4 = 1; } while(0)
#define inpStartSolenoid_SetLow()   do { LATB4 = 0; } while(0)
#define inpStartSolenoid_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define inpStartSolenoid_GetValue()         RB4
#define inpStartSolenoid_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define inpStartSolenoid_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define inpStartSolenoid_SetPullup()    do { WPUB4 = 1; } while(0)
#define inpStartSolenoid_ResetPullup()   do { WPUB4 = 0; } while(0)
#define inpStartSolenoid_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define inpStartSolenoid_SetDigitalMode()   do { ANSB4 = 0; } while(0)
// get/set inpStartLEDs aliases
#define inpStartLEDs_TRIS               TRISB5
#define inpStartLEDs_LAT                LATB5
#define inpStartLEDs_PORT               RB5
#define inpStartLEDs_WPU                WPUB5
#define inpStartLEDs_ANS                ANSB5
#define inpStartLEDs_SetHigh()    do { LATB5 = 1; } while(0)
#define inpStartLEDs_SetLow()   do { LATB5 = 0; } while(0)
#define inpStartLEDs_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define inpStartLEDs_GetValue()         RB5
#define inpStartLEDs_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define inpStartLEDs_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define inpStartLEDs_SetPullup()    do { WPUB5 = 1; } while(0)
#define inpStartLEDs_ResetPullup()   do { WPUB5 = 0; } while(0)
#define inpStartLEDs_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define inpStartLEDs_SetDigitalMode()   do { ANSB5 = 0; } while(0)
// get/set outBatteryErr aliases
#define outBatteryErr_TRIS               TRISB6
#define outBatteryErr_LAT                LATB6
#define outBatteryErr_PORT               RB6
#define outBatteryErr_WPU                WPUB6
#define outBatteryErr_SetHigh()    do { LATB6 = 1; } while(0)
#define outBatteryErr_SetLow()   do { LATB6 = 0; } while(0)
#define outBatteryErr_Toggle()   do { LATB6 = ~LATB6; } while(0)
#define outBatteryErr_GetValue()         RB6
#define outBatteryErr_SetDigitalInput()    do { TRISB6 = 1; } while(0)
#define outBatteryErr_SetDigitalOutput()   do { TRISB6 = 0; } while(0)

#define outBatteryErr_SetPullup()    do { WPUB6 = 1; } while(0)
#define outBatteryErr_ResetPullup()   do { WPUB6 = 0; } while(0)
// get/set outStopNotRecieved aliases
#define outStopNotRecieved_TRIS               TRISB7
#define outStopNotRecieved_LAT                LATB7
#define outStopNotRecieved_PORT               RB7
#define outStopNotRecieved_WPU                WPUB7
#define outStopNotRecieved_SetHigh()    do { LATB7 = 1; } while(0)
#define outStopNotRecieved_SetLow()   do { LATB7 = 0; } while(0)
#define outStopNotRecieved_Toggle()   do { LATB7 = ~LATB7; } while(0)
#define outStopNotRecieved_GetValue()         RB7
#define outStopNotRecieved_SetDigitalInput()    do { TRISB7 = 1; } while(0)
#define outStopNotRecieved_SetDigitalOutput()   do { TRISB7 = 0; } while(0)

#define outStopNotRecieved_SetPullup()    do { WPUB7 = 1; } while(0)
#define outStopNotRecieved_ResetPullup()   do { WPUB7 = 0; } while(0)
// get/set ainVBatt aliases
#define ainVBatt_TRIS               TRISC0
#define ainVBatt_LAT                LATC0
#define ainVBatt_PORT               RC0
#define ainVBatt_ANS                ANSC0
#define ainVBatt_SetHigh()    do { LATC0 = 1; } while(0)
#define ainVBatt_SetLow()   do { LATC0 = 0; } while(0)
#define ainVBatt_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define ainVBatt_GetValue()         RC0
#define ainVBatt_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define ainVBatt_SetDigitalOutput()   do { TRISC0 = 0; } while(0)

#define ainVBatt_SetAnalogMode()   do { ANSC0 = 1; } while(0)
#define ainVBatt_SetDigitalMode()   do { ANSC0 = 0; } while(0)
// get/set outShockErr aliases
#define outShockErr_TRIS               TRISC1
#define outShockErr_LAT                LATC1
#define outShockErr_PORT               RC1
#define outShockErr_ANS                ANSC1
#define outShockErr_SetHigh()    do { LATC1 = 1; } while(0)
#define outShockErr_SetLow()   do { LATC1 = 0; } while(0)
#define outShockErr_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define outShockErr_GetValue()         RC1
#define outShockErr_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define outShockErr_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

#define outShockErr_SetAnalogMode()   do { ANSC1 = 1; } while(0)
#define outShockErr_SetDigitalMode()   do { ANSC1 = 0; } while(0)
// get/set outShockSupply aliases
#define outShockSupply_TRIS               TRISC2
#define outShockSupply_LAT                LATC2
#define outShockSupply_PORT               RC2
#define outShockSupply_ANS                ANSC2
#define outShockSupply_SetHigh()    do { LATC2 = 1; } while(0)
#define outShockSupply_SetLow()   do { LATC2 = 0; } while(0)
#define outShockSupply_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define outShockSupply_GetValue()         RC2
#define outShockSupply_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define outShockSupply_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define outShockSupply_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define outShockSupply_SetDigitalMode()   do { ANSC2 = 0; } while(0)
// get/set outLEDsSupply aliases
#define outLEDsSupply_TRIS               TRISC3
#define outLEDsSupply_LAT                LATC3
#define outLEDsSupply_PORT               RC3
#define outLEDsSupply_ANS                ANSC3
#define outLEDsSupply_SetHigh()    do { LATC3 = 1; } while(0)
#define outLEDsSupply_SetLow()   do { LATC3 = 0; } while(0)
#define outLEDsSupply_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define outLEDsSupply_GetValue()         RC3
#define outLEDsSupply_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define outLEDsSupply_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define outLEDsSupply_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define outLEDsSupply_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set outResetZigbee aliases
#define outResetZigbee_TRIS               TRISC4
#define outResetZigbee_LAT                LATC4
#define outResetZigbee_PORT               RC4
#define outResetZigbee_SetHigh()    do { LATC4 = 1; } while(0)
#define outResetZigbee_SetLow()   do { LATC4 = 0; } while(0)
#define outResetZigbee_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define outResetZigbee_GetValue()         RC4
#define outResetZigbee_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define outResetZigbee_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

// get/set outSolenoidSupply aliases
#define outSolenoidSupply_TRIS               TRISC5
#define outSolenoidSupply_LAT                LATC5
#define outSolenoidSupply_PORT               RC5
#define outSolenoidSupply_SetHigh()    do { LATC5 = 1; } while(0)
#define outSolenoidSupply_SetLow()   do { LATC5 = 0; } while(0)
#define outSolenoidSupply_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define outSolenoidSupply_GetValue()         RC5
#define outSolenoidSupply_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define outSolenoidSupply_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

// get/set ainVSolar aliases
#define ainVSolar_TRIS               TRISC6
#define ainVSolar_LAT                LATC6
#define ainVSolar_PORT               RC6
#define ainVSolar_ANS                ANSC6
#define ainVSolar_SetHigh()    do { LATC6 = 1; } while(0)
#define ainVSolar_SetLow()   do { LATC6 = 0; } while(0)
#define ainVSolar_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define ainVSolar_GetValue()         RC6
#define ainVSolar_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define ainVSolar_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

#define ainVSolar_SetAnalogMode()   do { ANSC6 = 1; } while(0)
#define ainVSolar_SetDigitalMode()   do { ANSC6 = 0; } while(0)
// get/set outIAmAlive aliases
#define outIAmAlive_TRIS               TRISC7
#define outIAmAlive_LAT                LATC7
#define outIAmAlive_PORT               RC7
#define outIAmAlive_ANS                ANSC7
#define outIAmAlive_SetHigh()    do { LATC7 = 1; } while(0)
#define outIAmAlive_SetLow()   do { LATC7 = 0; } while(0)
#define outIAmAlive_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define outIAmAlive_GetValue()         RC7
#define outIAmAlive_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define outIAmAlive_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define outIAmAlive_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define outIAmAlive_SetDigitalMode()   do { ANSC7 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */