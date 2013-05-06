#include"AirQuality.h"
#include"Arduino.h"
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

AirQuality airqualitysensor;

int current_quality =-1;

void setup()
{
    Serial.begin(9600);
    setupDust();
    airqualitysensor.init(14);
    dht.begin();
}
void loop()
{
    reportAirQuality();
    reportHumidityAndTemperature();
    reportSound();
    reportDust();
}


