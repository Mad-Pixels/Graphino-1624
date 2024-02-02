#include "MadScreen.h"

Screen::Fork::Fork(LiquidCrystal& lcd) : lcd(lcd) {}

byte fork_pixels[1][6][8] = {
        {
                {0b00000,0b00000,0b00000,0b11111,0b11111,0b00000,0b00000,0b00000},
                {0b00000,0b00001,0b00111,0b11111,0b11111,0b00111,0b00001,0b00000},
                {0b11111,0b11100,0b11100,0b11100,0b11100,0b11100,0b11100,0b11111},
                {0b00100,0b10001,0b01010,0b00000,0b00000,0b01010,0b10001,0b00100},
                {0b00000,0b00111,0b11111,0b00111,0b00111,0b11111,0b00111,0b00000},
                {0b00000,0b10000,0b11100,0b11111,0b11111,0b11100,0b10000,0b00000},
        },
};

void Screen::Fork::draw(int8_t startX, int8_t startY) {
    lcd.createChar(0, fork_pixels[0][0]);
    lcd.createChar(1, fork_pixels[0][1]);
    lcd.createChar(2, fork_pixels[0][2]);
    lcd.createChar(3, fork_pixels[0][3]);
    lcd.createChar(4, fork_pixels[0][4]);
    lcd.createChar(5, fork_pixels[0][5]);

    lcd.setCursor(startX, startY);
    lcd.write((uint8_t)0);
    lcd.write((uint8_t)0);
    lcd.write((uint8_t)0);
    lcd.write((uint8_t)1);
    lcd.write((uint8_t)2);
    lcd.write((uint8_t)3);
    lcd.write((uint8_t)4);
    lcd.write((uint8_t)5);
    lcd.write((uint8_t)0);
    lcd.write((uint8_t)0);
    lcd.write((uint8_t)0);
}