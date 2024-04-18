#include "MadScreen.h"

Screen::Skull::Skull(LiquidCrystal& lcd) : lcd(lcd) {}

byte skull_pixels[3][4][8] = {
        {
                {0b00011, 0b00001, 0b01011, 0b01111, 0b00111, 0b00000, 0b00000, 0b00000},
                {0b00000, 0b00000, 0b00000, 0b10000, 0b10111, 0b01111, 0b11111, 0b10001},
                {0b00000, 0b00000, 0b00000, 0b00001, 0b11101, 0b11110, 0b11111, 0b10001},
                {0b11000, 0b10000, 0b11010, 0b11110, 0b11100, 0b00000, 0b00000, 0b00000}
        },
        {
                {0b00000, 0b00000, 0b00000, 0b01111, 0b11111, 0b10111, 0b00011, 0b00111},
                {0b10111, 0b11110, 0b11111, 0b11111, 0b00101, 0b00000, 0b00000, 0b00000},
                {0b11101, 0b01111, 0b11111, 0b11111, 0b10100, 0b00000, 0b00000, 0b00000},
                {0b00000, 0b00000, 0b00000, 0b11110, 0b11111, 0b11101, 0b11000, 0b11100}
        }
};

void Screen::Skull::draw(int8_t startX, int8_t startY) {
    lcd.createChar(0, skull_pixels[0][0]);
    lcd.createChar(1, skull_pixels[0][1]);
    lcd.createChar(2, skull_pixels[0][2]);
    lcd.createChar(3, skull_pixels[0][3]);
    lcd.createChar(4, skull_pixels[1][0]);
    lcd.createChar(5, skull_pixels[1][1]);
    lcd.createChar(6, skull_pixels[1][2]);
    lcd.createChar(7, skull_pixels[1][3]);

    lcd.setCursor(startX, startY);
    lcd.write((uint8_t)0);
    lcd.write((uint8_t)1);
    lcd.write((uint8_t)2);
    lcd.write((uint8_t)3);

    lcd.setCursor(startX, startY+1);
    lcd.write((uint8_t)4);
    lcd.write((uint8_t)5);
    lcd.write((uint8_t)6);
    lcd.write((uint8_t)7);
}