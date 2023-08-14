#include "Max7219Handler.hpp"

Max7219Handler::Max7219Handler(MD_MAX72XX &max72, int laserCount) : laserCount_(laserCount), max72_(max72) {
    max72_.begin();
    max72_.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
}

void Max7219Handler::write(const PixelFrame &frame) {
    assert(frame.size() == laserCount_);

    for (int i = 0; i < frame.size(); i++) {
        bool isOn = frame[i].r + frame[i].g + frame[i].b > 0;
        int row = i / 8;
        int column = i % 8;
        max72_.setPoint(row, column, isOn);
    }

    max72_.update();
}

void Max7219Handler::testLasers() {
    Serial.printf("Testing lasers...\n");
    max72_.clear();

    for (int i = 0; i < laserCount_; i++) {
        int row = i / 8;
        int column = i % 8;
        max72_.setPoint(row, column, true);

        max72_.update();
        delay(100);
        max72_.clear();
    }
}