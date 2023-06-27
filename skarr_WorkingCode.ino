#include <ESP32Servo.h>
#include <U8g2lib.h>
#include <Wire.h>

Servo fingers;
const int emgPin = 2;
const int fingersPin = 4;
bool fingersOpen = true;
int emgValue = 0;
int threshold = 300;

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 22, 21, U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);
  fingers.attach(fingersPin);
  u8g2.begin();
}

void loop() {
  u8g2.setFont(u8g2_font_ncenB14_tr);  // Choose a font
  
  emgValue = analogRead(emgPin);
  Serial.println(emgValue);

  u8g2.clearBuffer();
  u8g2.setCursor(0, 20);
  u8g2.print(emgValue);
  u8g2.sendBuffer();
  
  if (fingersOpen && emgValue > threshold) {
    for (int i = 180; i >= 0; i--){
    fingers.write(i);
    delay(1);}
    fingersOpen = false;
  } else if (!fingersOpen && emgValue > threshold) {
    for (int j = 0; j <= 180; j++){
    fingers.write(j);
    delay(1);}
    fingersOpen = true;
  }
  
  delay(100);
}