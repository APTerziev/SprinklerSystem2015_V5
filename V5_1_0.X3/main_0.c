/* 
 * File:   main_0.c
 * Author: Anatoliy Terziev
 *
 * Created on Monday, 2015, May 4, 23:37
 */
#include <pic16f1507.h>
#include <xc.h>
//#include <htc.h>
#include <stdio.h>
#include <stdlib.h>
//#include <ctype.h>    // Are you processing ASCII chars?
#include <float.h>      // This should not be needed unless you are manually controlling floats/doubles
#include <math.h>       //
#include "mcc_generated_files/mcc.h"
//
//
//
//
//CONSTANTS:
//#define VREF                        3.3             //Reference voltage for ADC Used for calculation of exact value
#define K_ACCU                      6.5555556       //constant for ADC = (R7+R8)/R8; (1500+270)/270
#define Q_ACCU                      6.8             //constant for ADC=U D4 (6.8V)
#define K_PV                        9.14814815      //constant for ADC = (R19+R22)/R22; (2200+270)/270
#define Q_PV                        6.8             //constant for ADC=U D10 (6.8V)
#define PWM_VALUE                   50              //in % -> value for PWM for solenoid supply
#define VOLTAGE_FOR_CHARGING        15.1            //If the PV generates over this voltage the LEDs will not be flashing, it means that is the day time!
#define ENABLE_START_BATT_VOLTAGE   10.1            //If the voltage of accumulator is less than this value, starting of sprinkler is not possible
#define TIME_FOR_HIGH_VOLTAGE       4               //*0.5sec ->time for supply solenoid with 100% of battery voltage
#define IS_TIME_FOR_VERIFYING       300             //*0.1sec ->time between reducing the solenoid voltage and supllying the shock sensor
#define TIME_FOR_ESTABLISH_THE_SHOCK 10             //*0.1sec ->time between supllying the shock sensor and startinh of is's scanning
#define IS_TIME_FOR_CHECK_SHOCK     600             //*0.1sec ->how much time after supplying the shock it has to recieve sprinkling condition
#define IS_TIME_FOR_STOP_VALVE      9000            //*0.1sec ->how much time after start the sprinkler will be stopped forcedly
#define SHOCK_ERROR_CRITERIA        2               // how many times the number of pulses when sprinkler i worling are more than when sprinkler is stopped
#define TIME_FOR_DEMAGNETISING      2               //*0.5sec ->time for recieving signal for de magnetising from RID sensor
#define TIME_FOR_STOPPING           1200            //*0.5sec ->after this time the shock have to show that the sprinkler is not sprinkling
#define LEDS_ON_TIME                2               //*0.5sec ->time for lighting (*0.1 sec during sprinkling)
#define LEDS_OFF_TIME               3               //*0.5sec ->time for not lighting (*0.1 sec during sprinkling)
#define LEDS_LIGHTING_TIME          108000L         //apprx. *0.5sec ->it is not a good idea the leds to work over 12 hours, becouse of accumulators
#define RESET_PERIOD                600000L         //apprx. *0.5 sec ->this is a time to send reset ZIGBEE signal periodically. Aprx. 12 hours
#define RESET_DURATION              7               //*0.5 sec ->this is a duration or RESET ZIGBEE pulse
#define I_AM_ALIVE_ON_TIME          2               //*0.5 sec -> how many secundes I am alive LED will be light (*0.1 sec during sprinkling)
#define I_AM_ALIVE_OFF_TIME         6               //*0.5 sec -> how many secundes I am alive LED will be dark (*0.1 sec during sprinkling)
#define I_AM_ALIVE_START_TIME       5               //*0.5 sec -> how many secundes I am alive LED will be light after RESET
#define NUMBER_FOR_AVERAGE          10              //How many times we have to read ADC value and to get average from this samples
//
/*
 * Macro commands
 */
#define REDUCE_SOLENOUD_SUPPLY      PWM1CON = 0xC0;
#define STOP_SOLENOID               PWM1CON = 0x90;outSolenoidSupply_SetLow();
#define START_SOLENOID_FULL_POWER   PWM1CON = 0x90;outSolenoidSupply_SetHigh();

//GLOBAL VARIABLES:
unsigned long ulgCyclesForReset=0;  // this variable counts every 0.1 sec 
bit bInterrupted;                   //we use it to exit from sleep mode
unsigned long pulses;               //we use it to count peripheral interrupts during Shock registration
bit bDoNotSleep=0;                  //this flag disables sleep mode during PWM is active. PWM can not work in sleep mode.
unsigned char ucValveState=0 ;      //counter for "switch" statement in function "SolenoidManage". Shows which activity is passed
//FUNCTIONS
void SolenoidManage();              //this function starts and stops the sprinkler
void LEDsManage();                  //This function starts and stops LED diodes over sprinkler
void ImAliveManage();               //this function makes LED diode over PCB to be flashed
void WakeUpZigbee();                //sends RESET signal to ZIGBEE every few days
void ResetZigbee();                 //makes the RESET signal
float ReadainVBatt();               // this function reads voltage of accumulator battery
float ReadPHVVoltage();             // this function reads voltage of solar panel

unsigned char ucIAmAliveON;               //counts the cycles when "I am alive" led is lighting
unsigned char ucIAmAliveOFF;              //counts the cycles when "I am alive" led is NOT lighting


int main(void) {

//local variable declarations:
    
//initialize i/o - automatically generated functions:
SYSTEM_Initialize();                    //initialize I/O-s
INTERRUPT_GlobalInterruptEnable();      //global interrupt flag
INTERRUPT_PeripheralInterruptEnable();  //it means that pulses from shock can be counted
PWM1_LoadDutyValue(PWM_VALUE);          //initialize PWM with PWM_VALUE constant/while(FVR_IsOutputReady());             // wait to establish Fixed Voltage Reference. Not needed for PIC16F1507  
//VREGPM1=0;        //Normal Power Sleep mode is selected
//VREGPM0=1;        //always is =1 for PIC16F1507.Reserved for future.
IOCAP2=0; IOCAN2=0; // disable interrupt from shock
WDTCON=0x12;        //WDTPS=8(512mS), WDTEN=0.
VREGCON=0x03;       //Low Power Sleep mode is selected

        outIAmAlive_SetHigh(); SLEEP();                                             //lights "I am still alive LED" 
for(unsigned char m=0;m<I_AM_ALIVE_START_TIME;m++) SLEEP();                         //I am alive LED will flash for few seconds, to show that the PIC is powered
    
        outIAmAlive_SetLow();  SLEEP();                                             //extinguishes I am alive LED
    
  
   
    while (1)   //the general loop begins
    {
        CLRWDT();
        SolenoidManage();   //this function starts and stops the sprinkler
        LEDsManage();       //this function starts and stops LED diodes over sprinkler
        WakeUpZigbee();     ////sends RESET signal to ZIGBEE every day
        ImAliveManage();
        
//bDoNotSleep=1;
    //enter sleep mode - wait for interrupt:
        bInterrupted=false;     //clears flag for TIMER 2 interrupt
        if (bDoNotSleep == 1)   //if PWM is active
        {
          while(!bInterrupted)  // Wait for an interrupt. Can't sleep because of PWM
         {
              NOP();    // do nothing
          }
        }
        else       //PWM is not active
        {
          SLEEP();NOP(); //Wait for an interrupt from timer. The shock has to be disabled
        }

       
    }   // end of general loop
    return (EXIT_SUCCESS);
}// ////// END OF FUNCTION MAIN ////// //


//BASIC FUNCTIONS:
void SolenoidManage()   //this function starts and stops the valve
{


     /* ****************************manage solenoid valve*******************************************************************
     *  1. if inpStartSolenoid=1 -> Start valve at 100% of supply,  if battery voltage is over 10Volts.
     *  2. Check magnetizing and battery voltage. Send signal to ZIGBEE if there is something wrong.
     *  3. Decrease supply to 50%
     *  4. Check battery voltage during 10S and supply SHOCK
     *  5. After one minute check the SHOCK. It has to show that sprinkler is working
     *  6. Check SHOCK, battery voltage, time and inpStartSolenoid=1 for 15 minutes
     *  7. Stop the valve when the ZIGBEE sends 0 and check magnetizing again
     *  8. If the ZIGBEE don't send a STOP signal after 15 minutes, stop the valve, reset ZIGBEE and send signal to ZIGBEE
     *  9. Wait 2 minutes and check SHOCK. If after 2 minutes sprinkler is still sprinkling, send signal to ZIGBEE
     **********************************************************************************************************************/
    //
    //local variables:
unsigned char timeForHighVoltageOnSolenoid = 0;//here is stored how many cycles are passed from start solenoid command to time for reduce voltage
int timeToSupplyShock=0;                    //here is stored how many cycles are passed from reducing the solenoid voltage to energizing the shock
int timeToCheckingShock=0;                  //here is stored how many cycles are passed from energizing the shock to start checking it
int timeForSprinkling =0;                   //here is stored how many cycles are passed from beginning or sprinkling. After 15 min the sprinkler has to stop
unsigned char timeForDemagnetising=0;       //how many cycles are passed from de energizing the valve to receiving a signal from RID sensor
int timeForStopping=0;                      // how many cycles after deenergizing the valve, the shock shows that the sprinkler is stopped
long lngPulsesWorking;                      //counter for pulses from shock sensor during sprinkler is working
long lngPulsesNotWorking;                   //counter for pulses from shock during sprinkler is not working
float flainVBatt;                           //shows battery voltage

        switch (ucValveState) //condition recognizer
        {
            // /////////////////////////////////////////////////////////////// //
                case 0: //Wait for START SOLENOID signal
                if (inpStartSolenoid_GetValue())
                   {
                    ucValveState=1 ; //go to step 1
                   }
                break;



            // /////////////////////////////////////////////////////////////// //
                case 1: //Start valve at 100% of supply.If inpStartSolenoid=1 -> Start valve at 100% of supply,  if battery voltage is over 10Volts.
                {
                outStopNotRecieved_SetLow(); //reset output for error in case of missing of stop signal
                flainVBatt = ReadainVBatt();

                if  (flainVBatt<ENABLE_START_BATT_VOLTAGE)
                   {
                   outBatteryErr_SetHigh();   //Voltage is not enough to energize the valve
                   ucValveState=10 ;
                   }
                else //Start of sprinkling
                   {
                    outBatteryErr_SetLow();
                    timeForHighVoltageOnSolenoid = 0;
                    START_SOLENOID_FULL_POWER  // Supply solenoid with full battery voltage
                    ucValveState=2 ;
                    timeForHighVoltageOnSolenoid=0;
                   }
                }
                break;


            // /////////////////////////////////////////////////////////////// //
                case 2: //Check magnetizing and battery voltage. Send signal to ZIGBEE if there is something wrong.
                {
                    timeForHighVoltageOnSolenoid++; //counts the cycles when solenoid is 100% energized
                    if (timeForHighVoltageOnSolenoid > TIME_FOR_HIGH_VOLTAGE) //is time for reducing the voltage?
                    {
                        //Show sensor condition:
                        if (! inpValveMonitoringSensor_GetValue()) {outValveState_SetHigh();}
                        else {outValveState_SetLow();}
                        //read Battery Voltage:
                        flainVBatt = ReadainVBatt();
                        if  (flainVBatt < ENABLE_START_BATT_VOLTAGE) //check battery voltage value
                        {//Voltage is not enough to energize the valve
                        outBatteryErr_SetHigh();            // send signal to Zigbee
                        STOP_SOLENOID                       // DeEnergise the solenoid coil
                        ucValveState=10 ;                   // end of start valve cycle
                        }
                        else
                        {
                        ucValveState=3 ;   // continue to next step
                        }
                    }
                }
                break;


            // /////////////////////////////////////////////////////////////// //
                case 3: // Decrease power supply to 50% of nominal
                {
                  bDoNotSleep = 1; //PWM will be active! Sleep is not possible.
                        /*code for PWM have to be here !!!*/
                  REDUCE_SOLENOUD_SUPPLY // reduce the solenoid power
                  ucValveState=4 ;  // continue to next step
                }              
               break;



            // /////////////////////////////////////////////////////////////// //
                case 4: //continue checking the battery voltage during next 10S  and supply SHOCK
                {
                    timeToSupplyShock++;    //counter for steps
                    flainVBatt = ReadainVBatt();
                    if  (flainVBatt<ENABLE_START_BATT_VOLTAGE) //is the battery good?
                        {
                        outBatteryErr_SetHigh(); //Voltage is not enough to energize the valve
                        /*stop PWM have to be here*/
                        STOP_SOLENOID          // DeEnergise
                        ucValveState=10 ;      //end of start valve cycle
                        }
                    else if (timeToSupplyShock> IS_TIME_FOR_VERIFYING ) //is the time for starting of sprinkler expired?
                        {
                        outShockSupply_SetHigh();   //supplying the shock sensor
                        ucValveState=5;             //go to next step
                        timeToCheckingShock=0;      //counter for steps
                        }
                }
                break;



            // /////////////////////////////////////////////////////////////// //
                case 5: //After one minute check the SHOCK. It has to show that sprinkler is working
                timeToCheckingShock++; //counter for steps
                if  (!inpStartSolenoid_GetValue()) //is STOP command received ?
                {// Stop command is received
                    flainVBatt = ReadainVBatt();
                    if (flainVBatt >ENABLE_START_BATT_VOLTAGE) outBatteryErr_SetLow(); // if battery is good send signal to Zigbee
                        STOP_SOLENOID          // Deenergize solenoid
                        ucValveState=10 ;      //end of start valve cycle
                }
                else if (flainVBatt<ENABLE_START_BATT_VOLTAGE) // stop command is not received. Is battery good?
                        {//battery is not good
                        outBatteryErr_SetHigh();          //Voltage is not enough to energize the valve
                        /*stop PWM have to be here*/
                        STOP_SOLENOID          // DeEnergise coil
                        ucValveState=10 ;      // Go to end of start valve cycle
                        }
                else if (timeToCheckingShock>TIME_FOR_ESTABLISH_THE_SHOCK)//battery is good, stop not received, is time to check Shock Sensor?
                        {
                        outBatteryErr_SetLow();     //send signal to Zigbee about good condition of battery
                        /*code for checking the shock sensor have to be here*/
                        outShockSupply_SetHigh();   //Energizing the shock
                        pulses=0;                   //reset Shock counter
                        ucValveState=6;             //go to next step
                        }
                break;


            // /////////////////////////////////////////////////////////////// //
                case 6: //Check SHOCK, battery voltage, time and inpStartSolenoid=1 for 15 minutes
                     timeForSprinkling++;

                if  (!inpStartSolenoid_GetValue()) //STOP command is received
                {//we received STOP command
                        if (flainVBatt>ENABLE_START_BATT_VOLTAGE) outBatteryErr_SetLow(); //clear error output
                        STOP_SOLENOID             // Deenergize solenoid
                        outShockSupply_SetLow();  // Deenergize the Shock sensor
                        ucValveState=7 ;          //end of start valve cycle
                }
                else if (flainVBatt < ENABLE_START_BATT_VOLTAGE)// continue sprinkling, is battery good?
                        {//battery is not good:
                        outBatteryErr_SetHigh(); //send to Zigbee "Voltage is not enough to energize the valve"
                        STOP_SOLENOID           // Deenergize valve
                        /*stop PWM have to be here*/
                        ucValveState=10 ;      //end of start valve cycle
                        }
                else if (timeForSprinkling>IS_TIME_FOR_STOP_VALVE) //the sprinkler have to be stopped forcedly
                        {
                        /*code for checking the such sensor have to be here*/
                       STOP_SOLENOID           // Deenergize solenoid
                        // RESET Zigbee:
                        ResetZigbee();         // ...it clears reset counter                      
                       outStopNotRecieved_SetHigh();   //go to next step
                        ucValveState=7;         //go to next step
                        }
                else // we have START signal, battery is good and time for stop is not received
                {
                    /* code for checking Shock have to be here */
                    if (timeForSprinkling < IS_TIME_FOR_CHECK_SHOCK)
                    {
                     // !!! Enable interrupt from shock
                        IOCAP2 = 1; IOCAN2=1;              
                    }
                    else
                    {
                        lngPulsesWorking=pulses;
                        if ((lngPulsesNotWorking==0) && (lngPulsesWorking>SHOCK_ERROR_CRITERIA)) outShockErr_SetHigh();
                        if ((lngPulsesNotWorking >0)&&((lngPulsesWorking/lngPulsesNotWorking)>=SHOCK_ERROR_CRITERIA) )
                        {
                            outShockErr_SetHigh();
                        }
                        else
                        {
                            outShockErr_SetLow();
                        }
                        outShockSupply_SetLow(); //Deenergize the shock sensor
                        IOCAP2 = 0; IOCAN2=0;    //Disable interrupt from shock, calculate pulses and set Shock output in next step
                    }
                    
                }
                break;


            // /////////////////////////////////////////////////////////////// //
                case 7: //Stop the valve when the ZIGBEE sends 0 or the time for stopping forcefully become and check magnetizing again
                timeForDemagnetising++;
                if( timeForDemagnetising > TIME_FOR_DEMAGNETISING)
                {
                 if(!inpValveMonitoringSensor_GetValue()) outValveState_SetHigh();
                 else outValveState_SetLow();   //Show RID sensor condition
                 ucValveState=8;                //go to next step
                }
                break;





            // /////////////////////////////////////////////////////////////// //
                case 8: //If the ZIGBEE don't send a STOP signal after 15 minutes, stop the valve and send signal to ZIGBEE

                ucValveState=9;         //it was done in step 6
                

                /*RESET ZIGBEE may be should be here*/

       
                
                     //supplying the shock sensor
                break;




            // /////////////////////////////////////////////////////////////// //
                case 9: //Wait 2 minutes and check SHOCK. If after 2 minutes sprinkler is still sprinkling, send signal to ZIGBEE
                    timeForStopping++; //counts stopping time
                    if (timeForStopping>TIME_FOR_STOPPING) // is stopping time done?
                    {//Yes, we have to check shock
                        /*code for checking the shock sensor have to be here*/                        
                        outShockSupply_SetHigh ();  //Energize the shock sensor
                        if ((timeForStopping > TIME_FOR_STOPPING+TIME_FOR_ESTABLISH_THE_SHOCK)&& (timeForStopping < TIME_FOR_STOPPING+TIME_FOR_ESTABLISH_THE_SHOCK+2))
                        {
                          IOCAP2 = 1; IOCAN2=1;       //Enable peripheral interrupts from pins  
                        }      
                        
                        if (timeForStopping>TIME_FOR_STOPPING + IS_TIME_FOR_CHECK_SHOCK)
                        {
                        lngPulsesNotWorking=pulses;
                        if ((lngPulsesNotWorking==0) && (lngPulsesWorking>SHOCK_ERROR_CRITERIA)) outShockErr_SetLow();
                        if ((lngPulsesNotWorking >0)&&((lngPulsesWorking/lngPulsesNotWorking)>=SHOCK_ERROR_CRITERIA) )
                        {
                            outShockErr_SetHigh();
                        }
                        else
                        {
                            outShockErr_SetLow();
                        }
                        outShockSupply_SetLow(); //Deenergize the shock sensor
                        ucValveState=10; //end of valve cycle
                     // !!! Disable interrupt from shock, calculate pulses and set Shock output
                        IOCAP2 = 0; IOCAN2=0; //Disable peripheral interrupts
                        }
                    }
                    else
                    {
                        pulses=0;                   
                    }
                break;



            // /////////////////////////////////////////////////////////////// //
                case 10:  //end of the process, clear all temporary variables

                    bDoNotSleep=0;
                    if (inpStartSolenoid_GetValue()) //we have START signal, but start is not possible
                   {
                    NOP();                  //Do nothing. We can't start the valve, waiting STOP signal
                   }
                    else
                    {
                    timeForHighVoltageOnSolenoid = 0;       //here is stored how many cycles are passed from start solenoid command to time for reduce voltage
                    timeToSupplyShock=0;                    //here is stored how many cycles are passed from reducing the solenoid voltage to energizing the shock
                    timeToCheckingShock=0;                  //here is stored how many cycles are passed from energizing the shock to start checking it
                    timeForDemagnetising=0;                 //how mani cycles are passed from clearing of PWM1 to reading Shock
                    timeForSprinkling =0;
                    timeForStopping=0;      
                    outShockSupply_SetLow();                //supply of the shock sensor is switched off
                    ucValveState=0 ;                        //go to initial state
                    }
                break;



            // /////////////////////////////////////////////////////////////// //
                default: // we have software (logic) mistake
ucValveState = 10;       // this code will never been executed
                break;
            // /////////////////////////////////////////////////////////////// //

        }

}//end of "SolenoidManage()"

void LEDsManage()   //this function starts and stops LEDs over sprinkler
{
        //
    /* ************************************LEDS control ********************************************************************************
     *  1. If battery voltage is over 10 volts and inpStartLEDs=1, put the LEDS in flashing condition
     *  2. Measure flashing time, PHV voltage and battery voltage
     *  3. When the flashing time exceeded 14 hours or PHV voltage rising over 16V, or inpStartLEDs=0 or battery voltage falls under 10V
     *  stop the LEDS and send signal to Zigbee
     *
     ********************************************************************************************************************************  */
        //
    //Local variables:
unsigned char intLedsOnTime=0;              //counter for LEDs flashing. Counts time for light
unsigned char intLedsOffTime=0;             //counter for LEDs flashing. Counts time for dark
unsigned long ulgCyclesForLEDs=0;           // this variable counts every 0.1 sec
    if (inpStartLEDs_GetValue())
    {
        
        if ((ReadPHVVoltage() > VOLTAGE_FOR_CHARGING)&&(ulgCyclesForLEDs < LEDS_LIGHTING_TIME)) //is day? ...and if the LEDs are not working for more than 12 hours?
        {
          ulgCyclesForLEDs++ ;                       // counts the time that LEDs are lighting
          if (outLEDsSupply_GetValue())              //if the Zigbee sends command for starting LEDs
          {
              intLedsOffTime=1;                      //reset time for LEDs are not lighting
                if (intLedsOnTime < LEDS_ON_TIME) 
                {
                    outLEDsSupply_SetHigh();        //LEDs are lighting
                    intLedsOnTime++;                //counts time for flashing (lighting time)
                    
                }else if (intLedsOffTime < LEDS_OFF_TIME) 
                {
                    outLEDsSupply_SetLow();     //LEDs are not lighting
                }
                else    //reset flashing cycle
                {
                        intLedsOffTime=1;       //initialize with one, because during this "reset flashing cycle" the LEDs are off
                        intLedsOnTime=0;        //initialize counter for lighting
                }
          }
          else // Stop LEDs because of ZIGBEE sent stop command 
          {
              outLEDsSupply_SetLow();   //turn off the LEDs
              intLedsOffTime=1;         //reset all counters
              intLedsOnTime=0;          //
              
          }
        }
    }
    else // we have to stop LEDs because is a day or LEDS are flashing for more than 12 hours
    {
        ulgCyclesForLEDs=0;     //reset 12 hours counter
        outLEDsSupply_SetLow(); //stop LEDs
    }


}//end of "LEDsManage()"


void ImAliveManage()  //this function makes LED diode over PCB to be flashed
{
    /*
     * Code for I am alive LED
     *
     **/
    //
//Local variables:
//unsigned char ucIAmAliveON;               //counts the cycles when "I am alive" led is lighting
//unsigned char ucIAmAliveOFF;              //counts the cycles when "I am alive" led is NOT lighting

//outIAmAlive_Toggle();
        if (ucIAmAliveON < I_AM_ALIVE_ON_TIME)
        {
        ucIAmAliveON++;
        outIAmAlive_SetHigh();
        }
        else if (ucIAmAliveOFF < I_AM_ALIVE_OFF_TIME)
        {
         ucIAmAliveOFF++;
         outIAmAlive_SetLow();   
        }
        else
        {
            ucIAmAliveON=0;
            ucIAmAliveOFF=1;
            outIAmAlive_SetLow();
        }
        
    
}//end of "I'm Alive Manage()"

void WakeUpZigbee()                //sends RESET signal to ZIGBEE every day
{
    /* 
     * Send RESET time to time ...
     *
     **/
    ulgCyclesForReset++ ;
    //code for sending RESET
    // Reset is possible only during the day time and valve is in WAIT condition
        if ((ulgCyclesForReset > RESET_PERIOD) && (ucValveState==0) && (ReadPHVVoltage() > VOLTAGE_FOR_CHARGING)) ResetZigbee();
        
}
//ADDITIONAL FUNCTIONS:
void ResetZigbee(void)
    {//RESET Zigbee:
      outResetZigbee_SetHigh();                               //  Set RESET output to HIGH
      for(unsigned char k=0; k< RESET_DURATION; k++) SLEEP(); //wait RESET_DURATION cycles *0.1s
      outResetZigbee_SetLow();                                // clear RESET output
      ulgCyclesForReset=0;                                    // clear reset counter
    }

float ReadainVBatt()    //reads voltage of accumulator battery. Used in SolenoidManage();
{
    float sum;   //temporary used variable
     sum=0;      //initialization
    for (unsigned char k=0; k<NUMBER_FOR_AVERAGE; k++)  // we will measure NUMBER_FOR_AVERAGE times and will get average
    {
        sum=sum+ADC_GetConversion(ainVBatt);            //create sum of all measurement
    }
     sum=sum/NUMBER_FOR_AVERAGE;                        //average calculation
   //  sum=sum/1488;                                      //calibrate result
          sum=sum*2;     //exact voltage on pin
     sum=(sum*K_ACCU)+Q_ACCU;
    return sum;                                         //return the proper value in voltage
}

float ReadPHVVoltage()  //reads voltage of PV panel. Shows that it is day or night
{

 float sum;     //temporary used variable
     sum=0;     //initialization
    for (unsigned char k=0; k<NUMBER_FOR_AVERAGE; k++) // we will measure NUMBER_FOR_AVERAGE times and will get average
    {
        sum=sum+ADC_GetConversion(ainVSolar);           //create sum of all measurement
    }
     sum=sum/NUMBER_FOR_AVERAGE;                        //average calculation
  //   sum=sum/1082;                                      //calibrate result
     sum=sum*2;     //exact voltage on pin
     sum=(sum*K_PV)+Q_PV;
    return sum;                                         

}