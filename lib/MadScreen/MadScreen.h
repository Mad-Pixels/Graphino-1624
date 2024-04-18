#ifndef MadScreen_h
#define MadScreen_h

#include "../LiquidCrystal/LiquidCrystal.h"
#include <Arduino.h>

class Screen{
public:
    explicit Screen(LiquidCrystal& lcd);
    void welcome_screen(int16_t delay_millis);
    void error_screen(String msg);
    void disconnect_screen();

private:
    class Skull {
    public:
        explicit Skull(LiquidCrystal& lcd);
        void draw(int8_t startX, int8_t startY);
    private:
        LiquidCrystal& lcd;
    };

    class Fork {
    public:
        explicit Fork(LiquidCrystal& lcd);
        void draw(int8_t startX, int8_t startY);
    private:
        LiquidCrystal& lcd;
    };

    class Error {
    public:
        explicit Error(LiquidCrystal& lcd);
        void draw();
    private:
        LiquidCrystal& lcd;
    };

    LiquidCrystal& lcd;
    Skull skull;
    Error error;
    Fork fork;
};

#endif