#include "MadChart.h"

int32_t buffer[2][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
};

Chart::Chart(LiquidCrystal& lcd) : lcd(lcd), arrows(lcd), graph(lcd) {}
ChartData dataByIndex(uint8_t len, uint8_t idx, uint8_t dataSize, RawData *data);

void Chart::draw(uint8_t idx, Type type, uint8_t dataSize, RawData *data) {
    uint8_t filteredSize = 0;
    for (uint8_t i = 0; i < dataSize; ++i) {
        if ((data[i].type == 1 && type <= ROW_PERCENTAGE) || (data[i].type == 0 && type >= COL_RAW_DATA)) {
            filteredSize++;
        }
    }
    auto* filteredData = new RawData[filteredSize];
    uint8_t filteredIndex = 0;
    for (uint8_t i = 0; i < dataSize; ++i) {
        if ((data[i].type == 1 && type <= ROW_PERCENTAGE) || (data[i].type == 0 && type >= COL_RAW_DATA)) {
            filteredData[filteredIndex++] = data[i];
        }
    }

    switch (type) {
        case SPEC_PERCENTAGE_UNO:
            drawSpecPercentage(dataByIndex(1, idx, filteredSize, filteredData));
            delete[] filteredData;
            return;
        case BAR_PERCENTAGE:
            drawBarPercentage(dataByIndex(2, idx, filteredSize, filteredData));
            delete[] filteredData;
            return;
        case GIS_PERCENTAGE:
            drawGisPercentage(dataByIndex(2, idx, filteredSize, filteredData));
            delete[] filteredData;
            return;
        case COL_PERCENTAGE:
            drawColPercentage(dataByIndex(4, idx, filteredSize, filteredData));
            delete[] filteredData;
            return;
        case ROW_PERCENTAGE:
            drawRowPercentage(dataByIndex(4, idx, filteredSize, filteredData));
            delete[] filteredData;
            return;
        case COL_RAW_DATA:
            drawColRawData(dataByIndex(2, idx, filteredSize, filteredData));
            delete[] filteredData;
            return;
        case ROW_RAW_DATA:
            drawRowRawData(dataByIndex(2, idx, filteredSize, filteredData));
            delete[] filteredData;
            return;
        default:
            delete[] filteredData;
            return;
    }
}

void Chart::drawSpecPercentage(ChartData data) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(data.data[0].title);

    lcd.setCursor(0, 1);
    if (data.data[0].value < 10) {
        lcd.print("0");
    }
    if (data.data[0].value < 100) {
        lcd.print("0");
    }
    lcd.print(data.data[0].value);

    delete[] data.data;
}

void Chart::drawBarPercentage(ChartData data) {
    lcd.clear();

    const int8_t percentPerBlock = 100.0 / 5;
    for (uint8_t i = 0; i < data.len; i++) {
        lcd.setCursor(0, i);
        lcd.print(data.data[i].title);
        lcd.print(":");

        if (data.data[i].value >= buffer[0][i]) {
            arrows.drawUpClassic(5, i);
        } else {
            arrows.drawDownClassic(5, i);
        }
        if (data.data[i].value < 10) {
            lcd.print("0");
        }
        if (data.data[i].value < 100) {
            lcd.print("0");
        }
        lcd.print(data.data[i].value);
        lcd.print("% ");

        auto fullBlocks = static_cast<int8_t>(data.data[i].value / percentPerBlock);
        for (int8_t j = 0; j < fullBlocks; j++) {
            graph.drawBar100(11 + j, i);
        }

        auto remainder = static_cast<int8_t>(data.data[i].value - (fullBlocks * percentPerBlock));
        if (remainder > 0) {
            int nextBlockPosition = 11 + fullBlocks;
            if (remainder <= percentPerBlock / 4) {
                graph.drawBar20(nextBlockPosition, i);
            } else if (remainder <= 2 * (percentPerBlock / 4)) {
                graph.drawBar40(nextBlockPosition, i);
            } else if (remainder <= 3 * (percentPerBlock / 4)) {
                graph.drawBar60(nextBlockPosition, i);
            } else if (remainder <= 4 * (percentPerBlock / 4)) {
                graph.drawBar80(nextBlockPosition, i);
            } else {
                graph.drawBar100(nextBlockPosition, i);
            }
        }
        buffer[0][i] = data.data[i].value;
    }
    delete[] data.data;
}

void Chart::drawGisPercentage(ChartData data) {
    lcd.clear();

    const int8_t bufferSize = 5;
    for (uint8_t i = 0; i < data.len; i++) {
        for (int8_t j = bufferSize - 1; j > 0; j--) {
            buffer[i][j] = buffer[i][j - 1];
        }
        buffer[i][0] = data.data[i].value;

        lcd.setCursor(0, i);
        lcd.print(data.data[i].title);
        lcd.print(":");

        if (data.data[i].value >= buffer[i][1]) {
            arrows.drawUp(5, i);
        } else {
            arrows.drawDown(5, i);
        }
        if (data.data[i].value < 10) {
            lcd.print("0");
        }
        if (data.data[i].value < 100) {
            lcd.print("0");
        }
        lcd.print(data.data[i].value);
        lcd.print("% ");

        for (uint8_t j = 0; j < bufferSize; j++) {
            if (buffer[i][j] <= 20) {
                graph.drawGis20(11 +j, i);
            } else if (buffer[i][j] <= 40) {
                graph.drawGis40(11 +j, i);
            } else if (buffer[i][j] <= 60) {
                graph.drawGis60(11 +j, i);
            } else if (buffer[i][j] <= 80) {
                graph.drawGis80(11 +j, i);
            } else {
                graph.drawGis100(11 +j, i);
            }
        }
    }
    delete[] data.data;
}

void Chart::drawColPercentage(ChartData data) {
    lcd.clear();

    const uint8_t columnWidth = 4;
    const uint8_t arrowOffset = 3;

    for (uint8_t i = 0; i < data.len; i++) {
        uint8_t columnStart = i * columnWidth;

        lcd.setCursor(columnStart, 0);
        lcd.print(data.data[i].title);

        uint8_t arrowPosition = columnStart + arrowOffset;
        if (data.data[i].value >= buffer[0][i]) {
            arrows.drawUpClassic(arrowPosition, 0);
        } else {
            arrows.drawDownClassic(arrowPosition, 0);
        }
        lcd.setCursor(columnStart, 1);
        if (data.data[i].value < 10) {
            lcd.print("0");
        }
        if (data.data[i].value != 100) {
            lcd.print("0");
        }
        lcd.print(data.data[i].value);
        buffer[0][i] = data.data[i].value;
    }
    delete[] data.data;
}

void Chart::drawRowPercentage(ChartData data) {
    lcd.clear();

    const uint8_t maxCol = 8;
    const uint8_t arrowOffset = 3;

    for (uint8_t i = 0; i < data.len; i++) {
        uint8_t row = i < data.len / 2 ? 0 : 1;
        uint8_t col = i < data.len / 2 ? i : i - data.len / 2;

        lcd.setCursor(col * maxCol, row);
        lcd.print(data.data[i].title);

        uint8_t arrowPos = col * maxCol + arrowOffset;
        if (data.data[i].value >= buffer[0][i]) {
            arrows.drawUpClassic(arrowPos, row);
        } else {
            arrows.drawDownClassic(arrowPos, row);
        }
        if (data.data[i].value < 10) {
            lcd.print("0");
        }
        if (data.data[i].value != 100) {
            lcd.print("0");
        }
        lcd.print(data.data[i].value);
        buffer[0][i] = data.data[i].value;
    }
    delete[] data.data;
}

void Chart::drawColRawData(ChartData data) {
    lcd.clear();

    lcd.print("drawColRawData");
    delete[] data.data;
}

void Chart::drawRowRawData(ChartData data) {
    lcd.clear();

    lcd.print("drawRowRawData");
    delete[] data.data;
}
