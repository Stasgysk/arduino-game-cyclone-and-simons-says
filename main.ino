#include <FastLED.h>
#include <LiquidCrystal_I2C.h>
#include "lcd_wrapper.h"
#include "cyclone.h"
#include "simon_says.h"

/* DEFINICIA PINOV TLACIDIEK */
#define BTN_0_PIN 8
#define BTN_1_PIN 9
#define BTN_2_PIN 10
#define BTN_3_PIN 11

void setup() {
  /* NASTAVENIE PIN MODU TLACIDIEK */
  pinMode(BTN_0_PIN, INPUT);
  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);

  /* INICIALIZACIA LCD */
  lcd_init();

  /* VYPIS WELCOME SCREENU */
  lcd_print_at_clear(4,0,"Welcome");
  delay(1000);
  lcd_print_at(0,1,"Choose the game");
  delay(2000);
  lcd_print_at_clear(0,0,"btn1-> Cyclone");
  delay(1000);
  lcd_print_at(0,1,"btn2-> SimonSays");
}

void loop() {
  /* HLAVNA HERNA SLUCKA
  AK STLACITE PRVE TLACIDKO -> SPUSTI SA CYCLONE GAME
  AK STLACITE DRUHE TLACIDKO -> SPUSTI SA SIMON SAYS GAME */
  if(checkPush(BTN_0_PIN))  cycloneMain(40); 
  if(checkPush(BTN_1_PIN))  simonSays(); 
  if(checkPush(BTN_2_PIN)){}
  if(checkPush(BTN_3_PIN)){}
}
