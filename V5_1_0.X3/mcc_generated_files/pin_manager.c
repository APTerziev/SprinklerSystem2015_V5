/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1507
        Driver Version    :  1.02
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

#include <xc.h>
#include "pin_manager.h"

//GLOBAL VARIABLES
unsigned long pulses;


void PIN_MANAGER_Initialize(void) {
    LATA = 0x20;
    TRISA = 0x1F;
    ANSELA = 0x03;
    WPUA = 0x00;

    LATB = 0x00;
    TRISB = 0x30;
    ANSELB = 0x00;
    WPUB = 0x00;

    LATC = 0x80;
    TRISC = 0x49;
    ANSELC = 0x41;

    OPTION_REGbits.nWPUEN = 0x01;

    APFCON = 0x00;

    // enable interrupt-on-change individually    
    IOCAN2 = 1;
    IOCAP2 = 1;

    // enable interrupt-on-change globally
    INTCONbits.IOCIE = 1;

}

void PIN_MANAGER_IOC(void) {
    if (((IOCAN2 == 1) || (IOCAP2 == 1)) && (IOCAF2 == 1)) {
        //@TODO Add handling code for IOC on pin RA2
        pulses++;
        outIAmAlive_Toggle();
        // clear interrupt-on-change flag
        IOCAF2 = 0;
    }
}
/**
 End of File
 */