#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Arduino.h>
#include <FastLED.h>
#include <LiquidCrystal_I2C.h>
#include "lcd_wrapper.h"
#include "cyclone.h"

CRGB leds[NUM_LEDS];

bool cycloneMain(int LED_Duration)
{
    lcd_init(); /* INICIALIZACIA LCD */
    int goal_LED = 0; 
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); /* INICIALIZACIA LED PASKY */
    FastLED.setBrightness(15); /* NASTAVENIE JASU LEDIEK */
    int i = 0, j = 0; /* ITERATOR */
    fill_solid(leds,NUM_LEDS,CRGB::Yellow); /* VYPLNENIE LED PASKY NA ZLTO */
    switch_LED(goal_LED,1); /* ZAPNE LEDKU KTORU HRAC POKUSA SA ZASIAHNUT */
    
    delay(800);
    
   while(true) /* HLAVNA SLUCKA */
    {
        
        if(i>=NUM_LEDS)i=0; /* KED KOLO JE SKONCENE, VRACIA KURZOR NA ZACIATOK */

        if(input_Loop(i,LED_Duration)) /* SPRAVUJE INPUT HRACA, AK JE DANY INPUT UKONCI HRU */
        {
            finish_Screen(i); /* ZAPNE  FINISH ANIMATION, BLIKA LEDKAMI NIEKOLKO KRAT */

            return i==0; /* VRACIA "true" AK HRAC VYHRAL, "false" AK NIE */
        }
        i++; /* IDE KU DALSEJ LEDKY */

        lcd_print_at_clear(j++,1,"->"); /* LCD VYPIS */
        lcd_print_at(4,0,"Cyclone");
        if(j>14) j = 0;
    }

    return false;
}



bool input_Loop(int LED_num,int LED_Duration)
{
    switch_LED(LED_num,(LED_num == 0)?0:2); /* ZAPNE LED KURZOR */

    bool input_Bool = false; /* PRIRADI HODNOTU NA ZAKLADE VSTUPU, true -> NACITALO VSTUP, false -> ZIADNY VSTUP */
    unsigned long start_Time = millis();/* ULOZI AKTUALNY CAS PRE DALSIE POROVNANIE */

    while(!(input_Bool = get_Input())) /* IDE DO OKOLA POKIAL NIE JE DOSIAHNUTY LIMIT -> LED_Duration, ALEBO HRAC NEZADAL VSTUP */
    {
        if(millis()-start_Time >= LED_Duration)break; /* PRERUSI LOOP KED LED_Duration LIMIT JE DOSIAHNUTY */
    }
    switch_LED(LED_num,(LED_num == 0)?-1:1); /* VYPINA LED KURZOR */
    return input_Bool; /* VRACIA AK HRAC NIECO STLACIL */
}

void finish_Screen(int selected)
{
    int i = 0; /* ITERATOR */
    int num_Of_Blinks = 5; /* KONSTANTNY POCET BLIKNUTIA LEDKY */
    int delay_Ms = 500; /* KONSTANTNY DELAY */

    while(i<num_Of_Blinks) /* CYKEL NA ZOBRAZENIE BLIKNUTI LEDKY */
    {
        fill_solid(leds,NUM_LEDS,(selected==0)?CRGB(0,255,0):CRGB(255,0,0)); /* VYPLNENIE LED PASKY */
        FastLED.show();
        delay((selected==0)?delay_Ms:(delay_Ms/2)); /* ONESKORENIE, TAKZE LED ZOSTANE SVIETIT PO URCITU DOBU */

        fill_solid(leds,NUM_LEDS,CRGB(0,0,0));
        FastLED.show();
        delay(((selected==0)?delay_Ms:(delay_Ms/2))/2); /* ONESKORENIE, TAKZE LED ZOSTANE SVIETIT NA POLOVICU TRVANIA */

        i++;
    }
    /* VYPIS WELCOME SCREENU PO PREHRATI (vyber dalsej hry)*/
    lcd_print_at_clear(4,0,"Welcome");
    delay(200);
    lcd_print_at(0,1,"Choose the game");
    delay(400);
    lcd_print_at_clear(0,0,"btn1-> Cyclone");
    delay(250);
    lcd_print_at(0,1,"btn2-> SimonSays");
}

/* VRATI "true" AK JE STLACENE AKE KOLVEK TLACIDKO, "false" AK NIE JE */
bool get_Input()
{
    return (digitalRead(BTN_0_PIN)==HIGH) ||
            (digitalRead(BTN_1_PIN)==HIGH) ||
            (digitalRead(BTN_2_PIN)==HIGH) ||
            (digitalRead(BTN_3_PIN)==HIGH);
}

/* ZMENI FARBU LEDKY NA ZAKLADE CISLA
   0 -> modra,
   1 -> zelena,
   2 -> tirkysova,
   ine -> cervena */
void switch_LED(int LED_num,int col)
{
    switch(col)
    {
        case 0:
            leds[LED_num] = CRGB(0,0,125); /* NASTAVENIE FARBY PRE LED NA POZICIE LED_NUM */
        break;
        case 1:
            leds[LED_num] = CRGB(0,125,0);
        break;
        case 2:
            leds[LED_num] = CRGB(0,125,125);
        break;
        default:
            leds[LED_num] = CRGB(125,0,125);

    }
    FastLED.show();
}

