#ifndef _LCD_H
#define _LCD_H

int checkPush(int pinNumber);

/* INICIALIZACIA LCD */
void lcd_init();

/* VYCISTENIE LCD OBRAZOVKY */
void lcd_clear();

/* NASTAVENIE POZICIE LCD KURZORA */
void lcd_set_cursor(int y, int x);

/* VYPIS TEXTA NA OBRAZOVKU */
void lcd_print(char* text);

/* VYPIS TEXTA NA OBRAZOVKU NA KONKRETNEJ POZICIE */
void lcd_print_at(int y, int x, char* text);

/* VYPIS TEXTA NA OBRAZOVKU NA KONKRETNEJ POZICIE S VYCISTENIM OBRAZOVKY */
void lcd_print_at_clear(int y, int x, char* text);

#endif
