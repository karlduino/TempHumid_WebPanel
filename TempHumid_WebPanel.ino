/*
  Arduino code for temperature/humidity web panel

  Slightly modified version of Project 1 from 
  "Arduino Meets Linux" by Bob Hammell.

  I'm using an RCT003 temperature/humidity sensor rather than the
  MCP9808 temperature censor that he used.
*/

#include "DHT.h"
#include <Bridge.h>
#include <Console.h>

#define DHTPIN  A0
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Bridge.begin();
  Console.begin();
  Console.println("RHT03 starting.");

  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(true);

  if(isnan(h) || isnan(t))
    Console.println("Failed to read from sensor.");
  else {
    Console.print("Humidity: ");
    Console.print(h);
    Console.print("%    ");
    Console.print("Temp: ");
    Console.print(t);
    Console.println("*F");

    Bridge.put("RCT03_Temperature", String(t));
    Bridge.put("RCT03_Humidity", String(h));
  }

  delay(2000);
}
