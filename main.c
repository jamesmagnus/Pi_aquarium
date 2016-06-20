#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <wiringPi.h>
#include <softTone.h>
#include <string.h>
#include <time.h>

#include "main.h"
#include "pin.h"

int main(int argc, char* argv[])
{
    /* Initialisation des differents composants */
    srand(time(NULL));
    wiringPiSetup();
    PinInitialisation();

    if(piHiPri(10) != 0)
        printf("Error switching priority: %d\n", errno), exit(-1);

    AllumerAlimentation();
    //DemarrerSonnette();
    //DemarrerPompe();
    //DemarrerChauffage();
    //delay(1000);
    //ArreterPompe();
    //ArreterSonnette();
    //ArreterChauffage();
    EteindreAlimentation();

    return EXIT_SUCCESS;
}

void PinInitialisation()
{
    /* Pin en mode output */
    int i = 0;
    while(PINS_OUT[i] != -1)
    {
        pinMode(PINS_OUT[i], OUTPUT);
        i++;
    }

    /* Pin en mode input avec pull-up */
    i = 0;
    while(PINS_IN[i] != -1)
    {
        pinMode(PINS_IN[i], INPUT);
        pullUpDnControl(PINS_IN[i], PUD_UP);
        i++;
    }
}

void AllumerAlimentation()
{
    digitalWrite(PIN_ALIM, HIGH);
    delay(800);
}

void EteindreAlimentation()
{
    digitalWrite(PIN_ALIM, LOW);
    delay(200);
}

void DemarrerSonnette()
{
    piLock(0);
    CARRY_ON_RING = 1;
    piUnlock(0);

    piThreadCreate(Sonne);
}

void DemarrerChauffage()
{
    piLock(1);
    CARRY_ON_HEAT = 1;
    piUnlock(1);

    piThreadCreate(Chauffe);
}

PI_THREAD(Sonne)
{
    softToneCreate(PIN_SONNETTE);

    piLock(0);

    while(CARRY_ON_RING)
    {
        piUnlock(0);
        softToneWrite(PIN_SONNETTE, 450);
        delay(600);
        softToneWrite(PIN_SONNETTE, 280);
        delay(500);
        piLock(0);
    }
    piUnlock(0);

    softToneStop(PIN_SONNETTE);
    digitalWrite(PIN_SONNETTE, LOW);

    return NULL;
}

PI_THREAD(Chauffe)
{
    piLock(1);

    while(CARRY_ON_HEAT)
    {
        piUnlock(1);
        digitalWrite(PIN_CHAUFFAGE, HIGH);
        delay(60000);
        digitalWrite(PIN_CHAUFFAGE, LOW);
        delay(15000);
        piLock(1);
    }
    piUnlock(1);

    return NULL;
}

void ArreterChauffage()
{
    piLock(1);
    CARRY_ON_HEAT = 0;
    piUnlock(1);
}

void ArreterSonnette()
{
    piLock(0);
    CARRY_ON_RING = 0;
    piUnlock(0);
}

void DemarrerPompe()
{
    digitalWrite(PIN_POMPE, HIGH);
}

void ArreterPompe()
{
    digitalWrite(PIN_POMPE, LOW);
}
