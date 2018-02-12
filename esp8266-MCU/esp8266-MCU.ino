#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <Time.h>
#include <TimeLib.h>
#include <EEPROM.h>
#include <Wire.h>
#include <DS3232RTC.h>
#include <SoftwareSerial.h>
#include <FastCRC.h>

#include "mpu_config.h"




void setup() {

  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  RTC.begin(D2,D1);
  
  setTime(21, 42, 30, 3, 2, 2018);   //set the system time to 23h31m30s on 13Feb2009
  RTC.set(now());      
  
  setSyncProvider(RTC.get);

  Serial.println("here0");

  Wire.begin(D2, D1);
  Wire.setClock(400000);
  Serial.println("here1");

  while (!initMPU()) {
   Serial.println("Init fail");
    delay(500);
  }
  pinMode(13, INPUT_PULLUP);
  attachInterrupt(13, detectMotion, FALLING);
  Serial.println("here2");

}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("here3");
  Serial.println(MPU_Status());
  while (true) {
    Serial.println(getMPUReading());
    if (checkMotion()) {
      Serial.println("Motion Detected");
    }
    delay(500);
    Serial.println("here0");
    Serial.println(String(RTC.get()));
  }

  delay(1000);

}


