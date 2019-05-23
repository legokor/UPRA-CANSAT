#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>
#include <Adafruit_BMP280.h>
#include "MPU9250.h"

//-------------------------------------------------

//SPI
#define spi_mosi //sdi
#define spi_miso //sdo
#define spi_sck //scl

//-------------------------------------------------

//GPS
//VCC 5V
#define gps_Rx 3
#define gps_Tx 2

SoftwareSerial gps(gps_Tx,gps_Rx);

int gps_buffer[82];
int gps_index=0;

//-------------------------------------------------

//LoRa
//VCC 3V3
#define lora_dio0 9
#define lora_cs 10
#define lora_rst 8

//-------------------------------------------------

//BMP280
//VCC 3V3
#define bmp_cs 7
Adafruit_BMP280 bmp(bmp_cs);

//-------------------------------------------------

//MPU9250
//VCC 3V3

#define mpu_cs 6

MPU9250 IMU(SPI,mpu_cs);

//-------------------------------------------------

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("init gps");
  gps.begin(9600);
  Serial.println("gps done");

  Serial.println("init lora");
  LoRa.setPins(lora_cs,lora_rst,lora_dio0);
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  Serial.println("lora done");

  Serial.println("init bmp280");
  while(!bmp.begin()) {
    Serial.println(".");
    delay(500);
  }
  Serial.println("bmp280 done");

  Serial.println("init mpu9250");
  while(!IMU.begin()) {
    Serial.println(".");
    delay(500);
  }
  Serial.println("mpu9250 done");

}

void loop() {
  
  Serial.print("Sending packet... ");

  LoRa.beginPacket();
  
  LoRa.print("Temperature: ");
  LoRa.print(bmp.readTemperature());
  LoRa.print("Pressure: ");
  LoRa.print(bmp.readPressure());
  LoRa.print("Altitude: ");
  LoRa.print(bmp.readAltitude(1013.25));
  
  LoRa.print("X accel: ");
  LoRa.print(IMU.getAccelX_mss(),6);
  LoRa.print("Y accel: ");
  LoRa.print(IMU.getAccelY_mss(),6);
  LoRa.print("Z accel: ");
  LoRa.print(IMU.getAccelZ_mss(),6);
  
  LoRa.endPacket();

//-------------------------------------------------

  Serial.println("Packet sent!");

  Serial.print("Temperature: ");
  Serial.print(bmp.readTemperature());
  Serial.print("Pressure: ");
  Serial.print(bmp.readPressure());
  Serial.print("Altitude: ");
  Serial.print(bmp.readAltitude(1013.25));

  Serial.print("X accel: ");
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("Y accel: ");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("Z accel: ");
  Serial.print(IMU.getAccelZ_mss(),6);

  delay(1000);
}
