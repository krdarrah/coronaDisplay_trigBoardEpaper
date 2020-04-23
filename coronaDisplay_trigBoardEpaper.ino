#include "includes.h"

const char fwVersion[] = "4/22/20_COVID19";

//ADDED THIS STUFF FOR COVID DISPLAY
//epaper library here:
//https://github.com/ZinggJM/GxEPD
//DIN goes to 13
//CLK goes to 14
//the other signals
//CS to 15
//DC to 33
//RST to 32
//BUSY to 39
#include <SPI.h>
#include <GxEPD.h>
#include <GxGDEW075T8/GxGDEW075T8.h>      // 7.5" b/w
//640x384
//FreeFonts from Adafruit_GFX, make sure you install this library too from lib manager
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
SPIClass spiDisplay(HSPI);
GxIO_Class io(spiDisplay, /*CS=*/ 15, /*DC=*/ 33, /*RST=*/ 32);

GxEPD_Class ePaperDisplay(io, 32, 39 /*RST*/ /*BUSY*/);
void ePaperUpdate();

void setup() {
  pinMode(ESPlatchPin, OUTPUT);
  digitalWrite(ESPlatchPin, HIGH);
  pinMode(LEDpin, OUTPUT);
  Serial.begin(115200);
  checkWakeupPins();
  loadConfiguration(filename, config);
  rtcInit(config.timerCountDown, false);
  Serial.println(getBattery(), 2);
  if (connectWiFi()) {
    ePaperUpdate();
  }

  //  if (pushLogic()) { //decide if push will occur or nt and what message will be
  //    if (wiFiNeeded) {
  //      if (connectWiFi()) {
  //        pushOver();
  //        pushSafer();
  //        ifttt();
  //        mqtt();
  //      }
  //    }
  //    udp();
  //  }

  killPower();
  waitForButton();
  initBluetooth();
}

void loop() {
  serviceBluetooth();
  checkOTA();
}
