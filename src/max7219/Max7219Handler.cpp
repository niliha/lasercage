#include <Arduino.h>

#include "Max7219Handler.hpp"

Max7219Handler::Max7219Handler(LedControl &ledControl, int laserCount) : laserCount_(laserCount), ledControl_(ledControl) {
    // Wake up
    ledControl_.shutdown(0,false);
    // Set medium brightness
    ledControl.setIntensity(0,8);
    ledControl_.clearDisplay(0);
}

void Max7219Handler::write(const PixelFrame &frame) {
    assert(frame.size() == laserCount_);

    for (int i = 0; i < frame.size(); i++) {
        bool isOn = frame[i].r + frame[i].g + frame[i].b > 0;
        int row = i / 8;
        int column = i % 8;
        ledControl_.setLed(0,row,column,isOn);
    }

}

void Max7219Handler::testLasers() {
    Serial.printf("Testing lasers...\n");
    ledControl_.clearDisplay(0);

    for (int i = 0; i < laserCount_; i++) {
        int row = i / 8;
        int column = i % 8;
        ledControl_.setLed(0,row,column,true);
        delay(100);
        ledControl_.clearDisplay(0);
    }
}