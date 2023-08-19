#pragma once

#include <MD_MAX72xx.h>

#include "artnet/ArtnetHandler.hpp"
#include "artnet/BlockingRingBuffer.hpp"
#include "max7219/Max7219Handler.hpp"

#include "artnet/PixelOutputConfig.hpp"

class LaserCage {
 public:
    LaserCage(MD_MAX72XX max72Xx, uint32_t laserCount, int frameQueueCapacity = 3);
    void testLasers();
    void start();

 private:
    BlockingRingBuffer<std::variant<PixelFrame, PixelOutputConfig>> artnetQueue_;
    ArtnetHandler artnetHandler_;
    Max7219Handler max7219Handler_;
    unsigned long lastFrameMillis_;

    void max7219Task();
    void artnetTask();
};