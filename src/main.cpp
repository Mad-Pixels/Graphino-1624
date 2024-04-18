#include <Arduino.h>

#include "../lib/SerialHandshake/SerialHandshake.h"
#include "../lib/LiquidCrystal/LiquidCrystal.h"
#include "../lib/ArduinoJson/ArduinoJson.h"
#include "../lib/MadScreen/MadScreen.h"
#include "../lib/MadChart/MadChart.h"

Handshake handshake("1602MAD1MNTR-ad4ov42df4", 3000);
LiquidCrystal lcd(0x27, 16, 2);
Screen screen(lcd);
Chart chart(lcd);

bool sync_screen = false;

void setup() {
    Serial.begin(9600);
    while (!Serial) {};
    lcd.begin();

    screen.welcome_screen(5000);
    lcd.clear();
}

void loop() {
    handshake.ping();

    // switch by button.
    Type type = SPEC_PERCENTAGE_UNO;
    int8_t idx = 0;

    if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');

        if (data.startsWith("serial:")) {
            handshake.check(data);
        } else {
            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, data);
            if (error) {
                Serial.print("ERROR");
                Serial.print(data);
                screen.error_screen(error.c_str());
                return;
            }
            JsonArray metricsArray = doc["metrics"].as<JsonArray>();

            RawData dataPoint[metricsArray.size()];
            for (size_t i = 0; i < metricsArray.size(); ++i) {
//                const char* nameStr = metricsArray[i]["n"];
//                strncpy(dataPoint[i].name, nameStr, sizeof(dataPoint[i].name) - 1);
//                dataPoint[i].name[sizeof(dataPoint[i].name) - 1] = '\0';

                const char* titleStr = metricsArray[i]["i"];
                strncpy(dataPoint[i].title, titleStr, sizeof(dataPoint[i].title) - 1);
                dataPoint[i].title[sizeof(dataPoint[i].title) - 1] = '\0';

                dataPoint[i].value = metricsArray[i]["v"].as<int>();
                dataPoint[i].type = metricsArray[i]["t"].as<int>();
            }
            chart.draw(idx, type, metricsArray.size(), dataPoint);
        }
    }
    if (!handshake.is_synced() && !sync_screen) {
        screen.disconnect_screen();
        sync_screen = true;
    }
    if (handshake.is_synced()) {
        sync_screen = false;
    }
}
