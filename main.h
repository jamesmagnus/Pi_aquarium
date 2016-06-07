#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define PIN_ALIM 29
#define PIN_SONNETTE 1
#define PIN_POMPE 4
#define PIN_CHAUFFAGE 28

int CARRY_ON_RING = 0;
int CARRY_ON_HEAT = 0;

const int PINS_OUT[] = {1, 4, 5, 6, 26, 27, 28, 29, -1};
const int PINS_IN[] = {0, 2, 3, 7, 21, 22, 23, 24, 25, -1};

void PinInitialisation();
void AllumerAlimentation();
void EteindreAlimentation();
void DemarrerSonnette();
void ArreterSonnette();
void DemarrerPompe();
void ArreterPompe();
PI_THREAD(Sonne);
PI_THREAD(Chauffe);
void ArreterChauffage();
void DemarrerChauffage();

#endif // MAIN_H_INCLUDED
