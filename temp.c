#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <sys/time.h>

#include "pin.h"
#include "temp.h"

CSV LoadCSV(char *file)
{
    CSV ret;
    ret.err = -1;

    FILE *f = fopen(file, "r");

    if(f == NULL)
    {
        return ret;
    }



    ret.err = 0;
    return ret;
}

unsigned int* LireTempsCondensateur(int nbEssais)
{
    int i = 0;
    struct timeval tv1, tv2, tvResult;
    unsigned int* valeurs = malloc(sizeof(unsigned int) * nbEssais);

    while(i <= nbEssais)
    {
        digitalWrite(PIN_PURGE_CONDENSATEUR, HIGH);
        delay(1000*10);
        digitalWrite(PIN_PURGE_CONDENSATEUR, LOW);

        delay(500);

        gettimeofday(&tv1, NULL);
        digitalWrite(PIN_ALIM_CAPTEUR_TEMPERATURE, HIGH);

        while(digitalRead(22));

        gettimeofday(&tv2, NULL);
        digitalWrite(PIN_ALIM_CAPTEUR_TEMPERATURE, LOW);


        timersub(&tv2, &tv1, &tvResult);
        if(i > 0)
        {
            valeurs[i - 1] = tvResult.tv_usec;
        }

        i++;
    }

    return valeurs;
}
