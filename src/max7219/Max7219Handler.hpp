#pragma once

#include  <LedControl.h>

#include "common/PixelFrame.hpp"

class Max7219Handler {
 public:
    Max7219Handler(LedControl &ledControl, int laserCount);
    void write(const PixelFrame &frame);
    void testLasers();

 private:
    const int laserCount_;

    LedControl &ledControl_;
};