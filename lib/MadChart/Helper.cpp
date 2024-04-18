#include "MadChart.h"

uint16_t factorial(uint16_t n) {
    uint16_t result = 1;
    for (uint16_t i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

uint16_t combination(uint16_t n, uint16_t k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

ChartData dataByIndex(uint8_t len, uint8_t idx, uint8_t dataSize, RawData *data) {
    uint16_t maxIdx = combination(dataSize, len);
    idx %= static_cast<uint8_t>(maxIdx);

    auto* arr = new RawData[len];
    auto* indices = new uint8_t[len];

    for (uint8_t i = 0; i < len; ++i) {
        indices[i] = i;
    }
    for (uint8_t i = 0; i < idx; ++i) {
        uint8_t t = len - 1;
        while (t != 0 && indices[t] == dataSize - len + t) {
            t--;
        }
        indices[t]++;

        for (uint8_t j = t + 1; j < len; ++j) {
            indices[j] = indices[j - 1] + 1;
        }
    }

    uint8_t actualLen = 0;
    for (uint8_t i = 0; i < len; ++i) {
        if (indices[i] < dataSize) {
            arr[i] = data[indices[i]];
            actualLen++;
        } else {
            break;
        }
    }
    ChartData res = {arr, actualLen};
    delete[] indices;
    return res;
}
