/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "IRSensor.h"
#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE       100ms
#define NUM_LED             6
// Initialise the digital pin LED1 as an output
DigitalOut led0(PD_4);
DigitalOut led1(PD_3);
DigitalOut led2(PD_6);
DigitalOut led3(PD_2);
DigitalOut led4(PD_7);
DigitalOut led5(PD_5);

void setLED(int num, int val);

int main()
{
    

    AnalogIn distance(PA_0); // Kreieren der Ein- und Ausgangsobjekte
    DigitalOut enable(PG_1);
    DigitalOut bit0(PF_0);
    DigitalOut bit1(PF_1);
    DigitalOut bit2(PF_2);

    float d[NUM_LED];

    while (true) {

        //Create Sensors
        

        for(int i=0; i<NUM_LED; i++){
            IRSensor sen(distance, bit0, bit1, bit2, i);
            enable = 1;

            d[i] = sen.read();
        
            if(d[i] <= 0.08){
                setLED(i,1);
            } else {
                setLED(i,0);
            }
            printf("sen%d=%dmm; ",i, (int)(1000.0f*d[i]));
        }
        printf("\r\n");
        

        ThisThread::sleep_for(BLINKING_RATE);
    }
}

void setLED(int num, int val){
    switch(num){
        case 0: led0 = val;
                break;
        case 1: led1 = val;
                break;
        case 2: led2 = val;
                break;
        case 3: led3 = val;
                break;
        case 4: led4 = val;
                break;
        case 5: led5 = val;
                break;
    }
}
