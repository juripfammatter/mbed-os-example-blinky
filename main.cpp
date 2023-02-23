/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 * Juri Pfammatter
 */

#include "IRSensor.h"
#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE       100ms
#define NUM_LED             6

//Create bus in reverse Order: https://os.mbed.com/docs/mbed-os/v6.15/apis/busout.html
BusOut led(PD_5, PD_7, PD_2, PD_6, PD_3, PD_4); 


int main()
{
    AnalogIn distance(PA_0); // Kreieren der Ein- und Ausgangsobjekte
    DigitalOut enable(PG_1);
    DigitalOut bit0(PF_0);
    DigitalOut bit1(PF_1);
    DigitalOut bit2(PF_2);

    float d[NUM_LED];

    while (true) {
        for(int i=0; i<NUM_LED; i++){
            IRSensor sen(distance, bit0, bit1, bit2, i); // automatically destructed when going out of scope (for loop)
            enable = 1;
            d[i] = sen.read();

            if(d[i] <= 0.08){
                led[i] = 1;
            } else {
                led[i] = 0;
            }
            printf("sen%d=%dmm; ",i, (int)(1000.0f*d[i]));
        }

        printf("\r\n");
        ThisThread::sleep_for(BLINKING_RATE);
    }
}