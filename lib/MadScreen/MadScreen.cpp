#include "MadScreen.h"
#include <Arduino.h>

Screen::Screen(LiquidCrystal& lcd) : lcd(lcd), skull(lcd), error(lcd), fork(lcd) {}

void Screen::welcome_screen(int16_t delay_millis) {
    lcd.clear();
    skull.draw(0,0);
    lcd.setCursor(6, 0);
    lcd.print("MadPixels");
    lcd.setCursor(9, 1);
    lcd.print("***");

    delay(delay_millis);
}

void Screen::error_screen(const String msg) {
    lcd.clear();
    error.draw();

    int msgLength = msg.length();
    if (msgLength > 16) {
        for (int i = 0; i < msgLength + 16; ++i) {
            lcd.setCursor(0, 1);
            lcd.print(msg.substring(i % msgLength, i % msgLength + 16));
            delay(450);
            lcd.setCursor(0, 1);
            lcd.print("                ");
        }
    }
    lcd.setCursor(0, 1);
    lcd.setCursor((16 - msgLength) / 2, 1);
    lcd.print(msg);
}

void Screen::disconnect_screen() {
    lcd.clear();
    fork.draw(2,0);

    lcd.setCursor(4, 1);
    lcd.print("no sync");
}
