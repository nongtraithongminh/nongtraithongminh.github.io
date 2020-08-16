#include "MQ135.h"
#define BLYNK_PRINT Serial
 
#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#include <DHT.h> 
char auth[] = "pdRvqoQgBWPq323a_QCYgiFgnrri_1_k";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "LAX Tin hoc 2";
char pass[] = "L34nhXu4n";
 
#define PIN_MQ135 A0
MQ135 mq135_sensor = MQ135(PIN_MQ135);
#define flame D4 

#define DHTPIN D2          // What digital pin we're connected to
#define DHTTYPE DHT22     // DHT 11<p>DHT dht(DHTPIN, DHTTYPE);
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
float t;
float h;
float correctedPPM;
 
void setup() {
  Serial.begin(9600);
  pinMode(flame,INPUT);
  pinMode(D7,OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}
 
void loop() {
  digitalWrite(D7,0);
  
  Blynk.run();
  timer.run();
  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(t, h);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  correctedPPM = mq135_sensor.getCorrectedPPM(t, h);
 
  /*Serial.print("MQ135 RZero: ");
  Serial.print(rzero);
  Serial.print("\t Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print("\t Resistance: ");
  Serial.print(resistance);
  Serial.print("\t PPM: ");
  Serial.print(ppm);
  Serial.print("\t Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm");*/
  if( correctedPPM >5 ){
    Blynk.notify("cảnh báo có khói");
    digitalWrite(D7,1);
    delay(3000);
  }
  if(digitalRead(flame)==0){
    Blynk.notify("cảnh báo có lửa");
    digitalWrite(D7,1);
    delay(3000);
    
  }
 
  delay(500);
}
void sendSensor()
{
  h = dht.readHumidity();
  t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
//  l = analogRead(LDR);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V4, correctedPPM);
  
}
