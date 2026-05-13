#include "LoRa_E32.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>


int KalanEnerji2;
int Sicaklik;
int Sicaklik2;
int Voltaj;
int Voltaj2;
int KalanEnerji;

SoftwareSerial mySerial(3, 2);
LoRa_E32 e32ttl(&mySerial);

typedef struct {
  byte deger1;
  byte deger2;
  byte deger3;
  byte deger4;
  byte deger5;
  byte deger6;
  byte deger7;

} Signal;

Signal data;
void setup() {
  SPI.begin();
  randomSeed(200);
  Serial.begin(9600);
  e32ttl.begin();
  delay(500);
}

void loop() {

  //Hiz = random(40, 100);
  Sicaklik = random(40, 100);
  Voltaj = random(40, 100);
  KalanEnerji = 3520;

  byte byteDizi[6];  // int değeri dört byte'a dönüştürmek için bir dizi oluşturun

  // int değerini dört byte'a dönüştürme
  byteDizi[0] = Sicaklik & 0xFF;
  byteDizi[1] = (Sicaklik >> 8) & 0xFF;
  byteDizi[2] = Voltaj & 0xFF;
  byteDizi[3] = (Voltaj >> 8) & 0xFF;
  byteDizi[4] = KalanEnerji & 0xFF;
  byteDizi[5] = (KalanEnerji >> 8) & 0xFF;

  data.deger1 = random(40, 100);
  data.deger2 = byteDizi[0];
  data.deger3 = byteDizi[1];
  data.deger4 = byteDizi[2];
  data.deger5 = byteDizi[3];
  data.deger6 = byteDizi[4];
  data.deger7 = byteDizi[5];

  ResponseStatus rs = e32ttl.sendFixedMessage(highByte(620), lowByte(620), 23, &data, sizeof(Signal));
  Serial.println(rs.getResponseDescription());

  Serial.println("data.deger : ");
  Serial.println(data.deger1);
  Serial.println(data.deger2);
  Serial.println(data.deger3);
  Serial.println(data.deger4);


  delay(500);
}

