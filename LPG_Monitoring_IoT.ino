
#include "SoftwareSerial.h"
#include "MHZ19.h"   
#include "PMS.h"     
#include "MQ131.h"   
#include "dht.h"     
#include "DS3231.h"  

#define led 13
#define tvocPin 7  
#define dht22 5

dht DHT; 
DS3231  rtc(SDA, SCL);
MHZ19 myMHZ19;    
SoftwareSerial co2Serial(2, 3);  
SoftwareSerial pmsSerial(8, 9); 
PMS pms(pmsSerial);
PMS::DATA data;

unsigned long dataTimer = 0;
unsigned long dataTimer3 = 0;
unsigned long dataTimer4 = 0;
int readDHT, temp, hum;
int CO2;
int o3;
int tvoc;
int pm25;
int hours, minutes;
int previousMinutes = 1;
String timeString;
String receivedData = "Z";

uint8_t tempData[96] = {};
uint8_t humData[96] = {};
uint8_t tvocData[96] = {};
uint8_t co2Data[96] = {};
uint8_t pm25Data[96] = {};
uint8_t o3Data[96] = {};

int8_t last24Hours[12] = {};
int yAxisValues[4] = {};
int maxV = 0;
int8_t r = 99;

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(tvocPin, OUTPUT);

  
  digitalWrite(6, HIGH);        
  digitalWrite(tvocPin, HIGH);  
  delay(20 * 1000); 
  digitalWrite(6, LOW);
  digitalWrite(tvocPin, LOW);

  
  rtc.begin();
  co2Serial.begin(9600);
  pmsSerial.begin(9600);
  myMHZ19.begin(co2Serial);
  myMHZ19.autoCalibration(false);  
  MQ131.begin(6, A0, LOW_CONCENTRATION, 1000000); //
  MQ131.setTimeToRead(20); 
  MQ131.setR0(9000); 
}

void loop() {
  
  digitalWrite(tvocPin, HIGH);
  delay(5000); 
  tvoc = analogRead(A1); 
  digitalWrite(tvocPin, LOW);

  co2Serial.listen();
  dataTimer = millis();
  while (millis() - dataTimer <= 3000) {
    CO2 = myMHZ19.getCO2(); 
  }

  pmsSerial.listen();
  dataTimer3 = millis();
  while (millis() - dataTimer3 <= 1000) {
    pms.readUntil(data);
    pm25 = data.PM_AE_UG_2_5;
  }
  checkForIncomingData();
  MQ131.sample();
  o3 = MQ131.getO3(PPB);

  checkForIncomingData();

  time use the library example
  t = rtc.getTime();
  hours = t.hour;
  minutes = t.min;
  storeData();

  dataTimer4 = millis();
  while (millis() - dataTimer4 <= 200) {
    Serial.print("co2V.val=");
    Serial.print(CO2);
    
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("pm25V.val=");
    Serial.print(pm25);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("o3V.val=");
    Serial.print(o3);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("tempV.val=");
    Serial.print(temp);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("humV.val=");
    Serial.print(hum);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("tvocV.val=");
    Serial.print(tvoc);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

void checkForIncomingData() {
  
  if (Serial.available() > 0) {
    receivedData = Serial.readString();
    delay(30);
    if (receivedData == "0") {
      r = 0;
    }
    if (receivedData == "1") {
      r = 1;
    }
    if (receivedData == "2") {
      r = 2;
    }
    if (receivedData == "3") {
      r = 3;
    }
    if (receivedData == "4") {
      r = 4;
    }
  }
  if (r == 0 || r == 1 || r == 2 || r == 3 || r == 4) {
    delay(200);
    dataTimer3 = millis();
    while (millis() - dataTimer3 <= 200) {
      Serial.print("pageSwitch.val="); 
      Serial.print(1);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
    }
    delay(100);
    
      for (int t = 0; t < sizeof(tempData); t++) {
        int z = 0;
        while (z != 3) {
          Serial.write(tempData[t]);
          z++;
        }
      }
      delay(100);
      Serial.write(0xFF);
      Serial.write(0xFF);
      Serial.write(0xFF);
    }
    k++;
  }
}
