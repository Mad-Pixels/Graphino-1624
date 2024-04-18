#include "MadScreen.h"

Screen::Error::Error(LiquidCrystal& lcd) : lcd(lcd) {}

byte error_pixels[1][1][8] = {
        {
                {0b11111,0b10001,0b10101,0b10101,0b10001,0b10101,0b10001,0b11111},
        },
};

void Screen::Error::draw() {
    lcd.createChar(0, error_pixels[0][0]);

    lcd.setCursor(0, 0);
    lcd.write((uint8_t)0);

    lcd.setCursor(5, 0);
    lcd.write('#');
    lcd.write('E');
    lcd.write('R');
    lcd.write('R');
    lcd.write('O');
    lcd.write('R');

    lcd.setCursor(15, 0);
    lcd.write((uint8_t)0);
}