/*
  Created by TEOS
  Domotic with Arduino https://goo.gl/btZpjs
  YouTube https://goo.gl/k7TUSZ
  Instagram https://goo.gl/zEIjia
  Facebook https://goo.gl/eivraR
  Twitter https://goo.gl/du5Wgn
  Github https://goo.gl/Xl5IiS
  Google Plus https://goo.gl/gBnUdh
  WEB https://goo.gl/jtiYJy
*/

#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 converterADST;

const float maxAmperT = 100;
const float multiplierT = 0.0575F;
const float mainsT = 120.0;
float finalCurrentT;
float powerT;
float voltageT;
float currentT;
String resultSerialT;

void setup() {
  Serial.begin(9600);
  converterADST.setGain(GAIN_TWO);
  converterADST.begin();
}

void loop() {
  finalCurrentT = getValueT();
  powerT = mainsT * finalCurrentT;
  resultSerialT = "IRMS: " + String(currentT) + "A, " + "Potencia: " + String(powerT) + "W";
  Serial.println(resultSerialT);
  delay(500);
}

float getValueT() {
  unsigned long currentMillisT = millis();
  float additionCurrentT = 0;
  int tempT = 0;
  while (millis() - currentMillisT < 1000) {
    voltageT = converterADST.readADC_Differential_0_1() * multiplierT;
    currentT = voltageT * maxAmperT;
    currentT /= 1000.0;
    additionCurrentT += sq(currentT);
    tempT = tempT + 1;
  }
  currentT = sqrt(additionCurrentT / tempT);
  return (currentT);
}
