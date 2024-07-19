#ifndef _SIMONSAYS_H
#define _SIMONSAYS_H
/*
                           red
                          LED 30
                             o
                        o  BTN2 o
                     o             o
    green   LED 45 o BTN3      BTN1  o LED 15 blue
                     o             o
                        o  BTN0 o
                            o
                          LED 0 
                          yellow          
*/

/*(0 - yellow, 1 - blue, 2 - red, 3 - green)*/

/* AK BUDE INAK ZAPOJENE, ZMENIT HODNOTY PINOV, KTORE SA BUDU POUZIVAT NA TLACIDLA A LED STRIP */

/* DEFINICIA PINOV BUZZERA */
#define BUZZER_PIN      7

/* DEFINICIA PINOV TLACIDIEK */
#define BTN_0_PIN       8 
#define BTN_1_PIN       9
#define BTN_2_PIN       10
#define BTN_3_PIN       11

/* DEFINICIA PINOV LEDIEK */
#define LED_PIN         3

/* DEFINICIA POCTU LEDIEK */
#define NUM_LEDS    47

/* DEFINICIA POZICIE HADANYCH LEDIEK */
#define LED0        0
#define LED1        11
#define LED2        22
#define LED3        33 


/* DLZKA HRY */
#define GAME_LENGTH 200 

/* KRATKO ZASVIETI LED PODLA CISLA FARBY */
void lightUp(int light);

/* ROZSVIETENIE - SEKVENCIA UHADNUTYCH  (VYGENEROVANYCH) CISEL */ 
void playGenerated();

/* TIP HRACA - VRATI CISLO AKEJ FARBY STLACIL */
int getPressed();

/* NACITAVANIE VSTUPOV OD HRACA A VYHODNOTENIE TIPU - VRATI 1 AK NEUHADOL, INAK 0 */
int getInput();

/* HLAVNA HERNA SLUCKA PRE SIMON SAYS*/
int simonSays();

#endif
