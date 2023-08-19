#include "LaserCage.hpp"

LaserCage::LaserCage(MD_MAX72XX max72Xx, uint32_t laserCount, int artnetQueueCapacity)
    : artnetQueue_(artnetQueueCapacity), artnetHandler_(artnetQueue_, laserCount), max7219Handler_(max72Xx, laserCount),
      lastFrameMillis_(millis()) {
    // The Artnet task on core 0 does not yield to reduce latency.
    // Therefore, the watchdog on core 0 is not reset anymore, since the idle task is not resumed.
    // It is disabled to avoid watchdog timeouts resulting in a reboot.
    disableCore0WDT();
}

void LaserCage::start() {
    // Start artnet task on core 0 (together with the WIFI service)
    xTaskCreatePinnedToCore([](void *parameter) { static_cast<LaserCage *>(parameter)->artnetTask(); }, "artnetTask",
                            4096, this, 1, NULL, 0);

    // Start the MAX7219 task on core 1.
    // Therefore it is not affected by WIFI interrupts from core 0 while writing to the lasers
    // (avoiding flickering).
    xTaskCreatePinnedToCore([](void *parameter) { static_cast<LaserCage *>(parameter)->max7219Task(); }, "max7219Task",
                            4096, this, 1, NULL, 1);
}

void LaserCage::testLasers() {
    max7219Handler_.testLasers();
}

void LaserCage::max7219Task() {
    Serial.printf("max7219Task: started on core %d\n", xPortGetCoreID());

    while (true) {
        std::variant<PixelFrame, PixelOutputConfig> pixelVariant;
        artnetQueue_.pop(pixelVariant);

        std::visit(
            [this](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, PixelFrame>) {
                    max7219Handler_.write(arg);
                    Serial.printf("%lu ms since last frame\n", millis() - lastFrameMillis_);
                    lastFrameMillis_ = millis();
                } else if constexpr (std::is_same_v<T, PixelOutputConfig>) {
                    // Don't handle output configuration yet
                }
            },
            pixelVariant);
    }
}

void LaserCage::artnetTask() {
    Serial.printf("artnetTask: started on core %d\n", xPortGetCoreID());

    while (true) {
        artnetHandler_.read();
    }
}
