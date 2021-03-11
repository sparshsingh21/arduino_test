#include <SoftwareSerial.h>



#include "DHT.h"
#include <Adafruit_Sensor.h>


#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial Bluetooth(3,2);
int flag;
//Motor1
int MotorPin1 =  9;
int MotorPin2 =  8;

//Relay COnnections
int relayPin1 = 13;
int relayPin2 = 12;
int relayPin3 = 11;

//Motor2
int MotorPin3 = 5;
int MotorPin4 =  6;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Bluetooth.begin(9600);
  dht.begin();
  pinMode(MotorPin1,OUTPUT);
  pinMode(MotorPin2,OUTPUT);
  pinMode(MotorPin3,OUTPUT);
  pinMode(MotorPin4,OUTPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  if(Bluetooth.available()>0){
    flag = Bluetooth.read();

    if(flag == '1'){
      digitalWrite(MotorPin1, HIGH);
      digitalWrite(MotorPin2, LOW);
      digitalWrite(MotorPin3, LOW);
      digitalWrite(MotorPin4, LOW);
      Serial.println(F("1 input received"));
      delay(2000);
      flag = '4';
      Bluetooth.print(F("Humidity: "));
      Bluetooth.print(h);
      Bluetooth.print(F("%  Temperature: "));
      Bluetooth.print(t);
      Bluetooth.print(F("°C "));
      Bluetooth.print(f);
      Bluetooth.print(F("°F  Heat index: "));
      Bluetooth.print(hic);
      Bluetooth.print(F("°C "));
      Bluetooth.print(hif);
      Bluetooth.println(F("°F"));
    }

    if(flag == '2'){
      digitalWrite(MotorPin1, LOW);
      digitalWrite(MotorPin2, HIGH);
      digitalWrite(MotorPin3, LOW);
      digitalWrite(MotorPin4, LOW);
    }

    if(flag == '3'){
      digitalWrite(MotorPin1, LOW);
      digitalWrite(MotorPin2, LOW);
      digitalWrite(MotorPin3, HIGH);
      digitalWrite(MotorPin4, LOW);
    }
    if(flag == '4'){
      digitalWrite(MotorPin1, LOW);
      digitalWrite(MotorPin2, LOW);
      digitalWrite(MotorPin3, LOW);
      digitalWrite(MotorPin4, LOW);
    }
    if(flag == '5'){
      digitalWrite(relayPin1, HIGH);
    }
    if(flag == '6'){
      digitalWrite(relayPin1, LOW);
    }
    if(flag == '7'){
      digitalWrite(relayPin2, HIGH);
    }
    if(flag == '8'){
      digitalWrite(relayPin2, LOW);
    }
    if(flag == '9'){
      digitalWrite(relayPin3, HIGH);
    }
    if(flag == '0'){
      digitalWrite(relayPin3, LOW);
    }
  }
}
