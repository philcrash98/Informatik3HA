//
// Created by kalve on 03.07.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

#define DHTPIN  6

int main(void) {
    if (wiringPiSetup() == -1)
        exit(1);

    wiringPiSetup();
    pinMode (6, INPUT);

    while (1){
        printf("DHT 11 Value" + analogRead(DHTPIN));
    }

}