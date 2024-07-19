#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "lcd_wrapper.h"

/* NASTAVENIE LCD ADRESY */
LiquidCrystal_I2C lcd(0x27, 16, 2);

int checkPush(int pinNumber){
    bool pushed = digitalRead(pinNumber); 
    if(pushed == true){
        delay(250);
        while(pushed == true){
            pushed = digitalRead(pinNumber);
        } 
        return 1;
    }
    else return 0;
}

/* INICIALIZACIA LCD */
void lcd_init(){
    lcd.init();
    lcd.clear();
    lcd.backlight();
}

/* VYCISTENIE LCD OBRAZOVKY */
void lcd_clear(){
    lcd.clear();
}

/* NASTAVENIE POZICIE LCD KURZORA */
void lcd_set_cursor(int y, int x){
    lcd.setCursor(y, x);
}

/* VYPIS TEXTA NA OBRAZOVKU */
void lcd_print(char* text){
    lcd.print(text);
}

/* VYPIS TEXTA NA OBRAZOVKU NA KONKRETNEJ POZICIE */
void lcd_print_at(int y, int x, char* text){
    lcd_set_cursor(y, x);
    lcd_print(text);
}

/* VYPIS TEXTA NA OBRAZOVKU NA KONKRETNEJ POZICIE S VYCISTENIM OBRAZOVKY */
void lcd_print_at_clear(int y, int x, char* text){
  lcd.clear();
    lcd_set_cursor(y, x);
    lcd_print(text);
}
