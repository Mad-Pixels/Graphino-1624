#ifndef MadChart_h
#define MadChart_h

#include <Arduino.h>
#include "../LiquidCrystal/LiquidCrystal.h"

enum Type {
    SPEC_PERCENTAGE_UNO = 0,
    BAR_PERCENTAGE,
    GIS_PERCENTAGE,
    COL_PERCENTAGE,
    ROW_PERCENTAGE,
    COL_RAW_DATA,
    ROW_RAW_DATA,
};

struct RawData {
    char    title[4];
    char    name[4];
    int32_t value;
    uint8_t type;
};

struct ChartData {
    RawData* data;
    uint8_t  len;
};

class Chart {
public:
    explicit Chart(LiquidCrystal& lcd);
    void draw(uint8_t idx, Type type, uint8_t dataSize, RawData data[]);
private:
    class Arrows {
    public:
        explicit Arrows(LiquidCrystal& lcd);
        void drawUp(uint8_t row, uint8_t col);
        void drawDown(uint8_t row, uint8_t col);
        void drawUpClassic(uint8_t row, uint8_t col);
        void drawDownClassic(uint8_t row, uint8_t col);
    private:
        LiquidCrystal& lcd;
    };

    class Graph {
    public:
        explicit Graph(LiquidCrystal& lcd);
        void drawBar20(uint8_t row, uint8_t col);
        void drawBar40(uint8_t row, uint8_t col);
        void drawBar60(uint8_t row, uint8_t col);
        void drawBar80(uint8_t row, uint8_t col);
        void drawBar100(uint8_t row, uint8_t col);
        void drawGis20(uint8_t row, uint8_t col);
        void drawGis40(uint8_t row, uint8_t col);
        void drawGis60(uint8_t row, uint8_t col);
        void drawGis80(uint8_t row, uint8_t col);
        void drawGis100(uint8_t row, uint8_t col);
    private:
        LiquidCrystal& lcd;
    };

    LiquidCrystal& lcd;
    Arrows arrows;
    Graph graph;

    void drawSpecPercentage(ChartData data);
    void drawBarPercentage(ChartData data);
    void drawGisPercentage(ChartData data);
    void drawColPercentage(ChartData data);
    void drawRowPercentage(ChartData data);
    void drawColRawData(ChartData data);
    void drawRowRawData(ChartData data);
};

#endif
