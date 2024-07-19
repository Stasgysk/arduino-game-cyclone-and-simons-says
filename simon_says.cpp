#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include <FastLED.h>
#include <LiquidCrystal_I2C.h>
#include "lcd_wrapper.h"

#include "simon_says.h"

CRGB ledsSimon[NUM_LEDS]; /* POLE LEDIEK */


int level = 0; /* AKTUALNY LEVEL HRY (POCET VYGENEROVANYCH FARIEB) */


int randomGenerated[GAME_LENGTH]={0}; /* TU SA UKLADA, CO MA HRAC UHADNUT (CO HRA VYGENEROVALA) (0 - yellow, 1 - blue, 2 - red, 3 - green) */

/*FUNKCIA, KTORA ROZSVIETI A ZHASNE DANU FARBU light, ZABZUCI BZUCIAKOM PRISLUSNY TON PRE FARBU*/
void lightUp(int light){
  int toLightUp;
  switch(light){ /* PODLA CISLA FARBY NASTAVI V POLI LED DIOD PRISLUSNU FARBU AK SA LED MA ROZSVIETIT*/
    case 0:
      for(int i=LED0; i<=LED0+11;i++)ledsSimon[i] = CRGB ( 255, 255, 0); /* NASTAVENIE ROZVECOVANYCH LEDIEK V POLI LED DIOD*/
      tone(BUZZER_PIN, 400); /* BZUCANIE PRISLUSNEHO TONU*/
      break;
     case 1:
      for(int i=LED1; i<=LED1+11;i++)ledsSimon[i] = CRGB ( 0, 0, 255);
      tone(BUZZER_PIN, 500);
      break;
     case 2:
      for(int i=LED2; i<=LED2+11;i++)ledsSimon[i] = CRGB ( 255, 0, 0);
      tone(BUZZER_PIN, 600);
      break;
     case 3:
      for(int i=LED3; i<=LED3+11;i++)ledsSimon[i] = CRGB ( 0, 255, 0);
      tone(BUZZER_PIN, 700);
      break;
    }
   FastLED.show(); /* ROZSVIETENIE LED PODLA POLA LED DIOD */
   delay(200);
   noTone(BUZZER_PIN); /* VYPNUTIE BZUCIAKA*/
   FastLED.clear(); /* VYPNUTIE VSETKYCH LED */
   FastLED.show();
   delay(200);
  }

/*FUNKCIA, KTORA PREHRAJE SEKVENCIU FARIEB, KTORU VYGENEROVALA HRA*/
void playGenerated(){
  for(int i=0; i<level; i++){
    lightUp(randomGenerated[i]);
    }
  }

/*FUNKCIA, KTORA CAKA NA STLACENIE TLACIDLA, VRATI FARBU TLACIDLA, KTORU HRAC STLACIL */
int getPressed(){
  while (true) {
    if(digitalRead(BTN_0_PIN)==HIGH){
      return 0;
      }
      if(digitalRead(BTN_1_PIN)==HIGH){
      return 1;
      }
      if(digitalRead(BTN_2_PIN)==HIGH){
      return 2;
      }
      if(digitalRead(BTN_3_PIN)==HIGH){
      return 3;
      }
    }
  }

/* FUNKCIA, KTORA NACITAVA SEKVENCIU FARIEB OD HRACA, POROVNAVA JU SO SEKVENCIOU VYGENEROVANOU HROU. AK UHADNE CELU SEKVENCIU FUNKCIA VRATI 0. AK NEUHADNE VRATI 1 */
int getInput(){
  int input;
  for(int i=0; i<level; i++){ 
    input=getPressed(); /* ZISKA STLACENE TLACIDLO (VYBRANU FARBU)*/
    lightUp(input); /* ROZSVIETI HRACOV VYBER */
    if(input!=randomGenerated[i]){ /* OVERI CI HRAC (NE)UHADOL VYGENEROVANU FARBU */
      return 1;
      }
    }
    return 0;
  }
/* HLAVNA HERNA SLUCKA */
int simonSays() {
  lcd_init(); /* INICIALIZACIA LCD */
  lcd_print_at_clear(3,0,"Simon Says");

  char* levelString = (char*)calloc(10, sizeof(char));;
  

  FastLED.addLeds<WS2812, LED_PIN, GRB>(ledsSimon, NUM_LEDS); /* INICIALIZACIA LED PASU*/
  FastLED.setBrightness(15);

  for(level=1; level<GAME_LENGTH; level++){
    lcd_print_at(3,1,"Level: "); /* LCD ZOBRAZI LEVEL */
    itoa(level, levelString, 10);
    lcd_print_at(11,1,levelString);
    randomGenerated[level]=random(0,4); /* GENERUJE NAHODNU FARBU PRE DANY LEVEL*/
    playGenerated(); /* PREHRAJE VYGENEROVANE FARBY*/

    /* AK JE GET INPUT 1 - HRAC NEUHADOL - GAME OVER - KRUH 3 KRAT ZABLIKA NA CERVENO - FUNKCIA VRATI 1 */
    if(getInput()){
       for(int i=0; i<3; i++){
          fill_solid( ledsSimon, NUM_LEDS, CRGB::Red);
          FastLED.show();
          delay(200);
          FastLED.clear();
          FastLED.show();
          delay(50);
        }
        /*HLAVNE MENU*/
        lcd_print_at_clear(4,0,"Welcome");
        delay(200);
        lcd_print_at(0,1,"Choose the game");
        delay(400);
        lcd_print_at_clear(0,0,"btn1-> Cyclone");
        delay(250);
        lcd_print_at(0,1,"btn2-> SimonSays");
        return 1;
      }
      
    /* HRAC UHADOL SEKVENCIU - KRUH ZABLIKA 3 KRAT NA ZELENO - HRA POKRACUJE DALEJ*/
    else{
      for(int i=0; i<3; i++){
          fill_solid( ledsSimon, NUM_LEDS, CRGB::Green);
          FastLED.show();
          delay(200);
          FastLED.clear();
          FastLED.show();
          delay(50);
        }
      }
    delay(600);
  }
  return 0;
}
