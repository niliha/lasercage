#include <Arduino.h>
#include <nvs_flash.h>

#include "network/Network.hpp"
#include "network/WifiCredentials.hpp"

extern "C" void app_main() {
    // initialize arduino library before we start the tasks
    initArduino();

    Serial.begin(115200);

    nvs_flash_erase();  // erase the NVS partition and...
    nvs_flash_init();   // initialize the NVS partition.

    if (!Network::connectToWifi(WifiCredentials::ssid, WifiCredentials::password)) {
        ESP.restart();
    }
    // Network::initWifiAccessPoint(WifiCredentials::ssid, WifiCredentials::password);

    while (true) {
        // Stay in setup() such that stack frame is not popped
        delay(1000);
    }
}