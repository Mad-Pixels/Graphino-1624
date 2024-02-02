#include "MadChart.h"

Chart::Graph::Graph(LiquidCrystal &lcd) : lcd(lcd) {}

byte graph_pixels[5][2][8] = {
        {
                {0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,0b10000},
                {0b00000,0b00000,0b00000,0b00000,0b00000,0b11111,0b11111,0b00000},
        },
        {
                {0b11000,0b11000,0b11000,0b11000,0b11000,0b11000,0b11000,0b11000},
                {0b00000,0b00000,0b00000,0b00000,0b11111,0b11111,0b11111,0b00000},
        },
        {
                {0b11100,0b11100,0b11100,0b11100,0b11100,0b11100,0b11100,0b11100},
                {0b00000,0b00000,0b00000,0b11111,0b11111,0b11111,0b11111,0b00000},
        },
        {
                {0b11110,0b11110,0b11110,0b11110,0b11110,0b11110,0b11110,0b11110},
                {0b00000,0b00000,0b11111,0b11111,0b11111,0b11111,0b11111,0b00000},
        },{
                {0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111},
                {0b00000,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b00000},
        }
};

void Chart::Graph::drawBar20(uint8_t row, uint8_t col) {
    lcd.createChar(0, graph_pixels[0][0]);
    lcd.setCursor(row, col);
    lcd.write(0);
}

void Chart::Graph::drawBar40(uint8_t row, uint8_t col) {
    lcd.createChar(1, graph_pixels[1][0]);
    lcd.setCursor(row, col);
    lcd.write(1);
}

void Chart::Graph::drawBar60(uint8_t row, uint8_t col) {
    lcd.createChar(2, graph_pixels[2][0]);
    lcd.setCursor(row, col);
    lcd.write(2);
}

void Chart::Graph::drawBar80(uint8_t row, uint8_t col) {
    lcd.createChar(3, graph_pixels[3][0]);
    lcd.setCursor(row, col);
    lcd.write(3);
}

void Chart::Graph::drawBar100(uint8_t row, uint8_t col) {
    lcd.createChar(4, graph_pixels[4][0]);
    lcd.setCursor(row, col);
    lcd.write(4);
}

void Chart::Graph::drawGis20(uint8_t row, uint8_t col) {
    lcd.createChar(0, graph_pixels[0][1]);
    lcd.setCursor(row, col);
    lcd.write(0);
}

void Chart::Graph::drawGis40(uint8_t row, uint8_t col) {
    lcd.createChar(1, graph_pixels[1][1]);
    lcd.setCursor(row, col);
    lcd.write(1);
}

void Chart::Graph::drawGis60(uint8_t row, uint8_t col) {
    lcd.createChar(2, graph_pixels[2][1]);
    lcd.setCursor(row, col);
    lcd.write(2);
}

void Chart::Graph::drawGis80(uint8_t row, uint8_t col) {
    lcd.createChar(3, graph_pixels[3][1]);
    lcd.setCursor(row, col);
    lcd.write(3);
}

void Chart::Graph::drawGis100(uint8_t row, uint8_t col) {
    lcd.createChar(4, graph_pixels[4][1]);
    lcd.setCursor(row, col);
    lcd.write(4);
}
