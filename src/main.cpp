#include <Arduino.h>

#include "LaserCage.hpp"
#include "network/Network.hpp"
#include "network/WifiCredentials.hpp"

extern "C" void app_main() {
    // initialize arduino library before we start the tasks
    initArduino();
    Serial.setTxTimeoutMs(0);
    Serial.begin(115200);


    //if (!Network::connectToWifi(WifiCredentials::ssid, WifiCredentials::password)) {
        //ESP.restart();
    //}

    Network::initWifiAccessPoint(WifiCredentials::ssid, WifiCredentials::password);


    const int DATA_PIN=7;
    const int SCLK_PIN = 6;
    const int CS_PIN = 5;

    LedControl ledControl(DATA_PIN,SCLK_PIN,CS_PIN);
    LaserCage laserCage(ledControl, 48);

    laserCage.testLasers();

    laserCage.start();

    while (true) {
        // Stay in setup() such that stack frame is not popped
        delay(1000);
    }
}
