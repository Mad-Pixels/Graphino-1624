#include "MadChart.h"

Chart::Arrows::Arrows(LiquidCrystal &lcd) : lcd(lcd) {}

byte arrow_pixels[2][2][8] = {
        {
                {0b00000,0b00100,0b01010,0b10001,0b00000,0b00000,0b00000,0b00000},
                {0b00000,0b00100,0b01110,0b10101,0b00100,0b00100,0b00100,0b00000},
        },
        {
                {0b00000,0b00000,0b00000,0b10001,0b01010,0b00100,0b00000,0b00000},
                {0b00000,0b00100,0b00100,0b00100,0b10101,0b01110,0b00100,0b00000},
        }
};

void Chart::Arrows::drawUp(uint8_t row, uint8_t col) {
    lcd.createChar(7, arrow_pixels[0][0]);
    lcd.setCursor(row, col);
    lcd.write(7);
}

void Chart::Arrows::drawDown(uint8_t row, uint8_t col) {
    lcd.createChar(7, arrow_pixels[1][0]);
    lcd.setCursor(row, col);
    lcd.write(7);
}

void Chart::Arrows::drawUpClassic(uint8_t row, uint8_t col) {
    lcd.createChar(7, arrow_pixels[0][1]);
    lcd.setCursor(row, col);
    lcd.write(7);
}

void Chart::Arrows::drawDownClassic(uint8_t row, uint8_t col) {
    lcd.createChar(7, arrow_pixels[1][1]);
    lcd.setCursor(row, col);
    lcd.write(7);
}
