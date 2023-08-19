#include <Arduino.h>

#include "LaserCage.hpp"
#include "network/Network.hpp"
#include "network/WifiCredentials.hpp"

extern "C" void app_main() {
    // initialize arduino library before we start the tasks
    initArduino();
    Serial.begin(115200);
    sleep(3);


    //if (!Network::connectToWifi(WifiCredentials::ssid, WifiCredentials::password)) {
        //ESP.restart();
    //}
    Network::initWifiAccessPoint(WifiCredentials::ssid, WifiCredentials::password);


    Serial.printf("Constructing LaserCage...\n");
    MD_MAX72XX max7219(MD_MAX72XX::FC16_HW,7,6,5,1);
    LaserCage laserCage(max7219, 50);

    while (true) {
        laserCage.testLasers();
    }

    laserCage.start();

    while (true) {
        // Stay in setup() such that stack frame is not popped
        delay(1000);
    }
}
