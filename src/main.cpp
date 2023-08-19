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


    const int MOSI_PIN = 23;
    const int MISO_PIN=19;
    const int SCLK_PIN = 18;
    const int CS_PIN = 5;

    LedControl ledControl(MOSI_PIN,SCLK_PIN,CS_PIN);
    LaserCage laserCage(ledControl, 48);

    while (true) {
        laserCage.testLasers();
    }

    laserCage.start();

    while (true) {
        // Stay in setup() such that stack frame is not popped
        delay(1000);
    }
}
