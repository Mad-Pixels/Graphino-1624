#include "SerialHandshake.h"
#include <Arduino.h>

Handshake::Handshake(const char* serial_number, int16_t ping_delay_millis) :
synced(false),
ping_delay(ping_delay_millis),
lastSuccessfulCheckMillis(0) {
    this->serial_number = serial_number;
}

bool Handshake::is_synced() const {
    return synced;
}

void Handshake::ping() {
    if (millis() - lastSuccessfulCheckMillis >= ping_delay) {
        Serial.print(serial_number+'\n');
    }
    if (millis() - lastSuccessfulCheckMillis > ping_delay*1.3) {
        synced = false;
    }
}

void Handshake::check(const String& data) {
    if (data.equals("serial:ack::" + serial_number)) {
        lastSuccessfulCheckMillis = millis();
        synced = true;
    }
}
