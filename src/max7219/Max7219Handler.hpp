#pragma once

#include <MD_MAX72xx.h>

#include "common/PixelFrame.hpp"

class Max7219Handler {
 public:
    Max7219Handler(MD_MAX72XX &max72, int laserCount);
    void write(const PixelFrame &frame);
    void testLasers();

 private:
    const int laserCount_;

    MD_MAX72XX &max72_;
};