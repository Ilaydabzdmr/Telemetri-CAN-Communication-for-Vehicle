#include "LoRa_E32.h"
#include <SoftwareSerial.h>

int pot1;
int pot2;
int pot3;
int pot4;
SoftwareSerial mySerial(3, 2);

/*
 * Pinler     Arduino uno    Lora E32 433T20d
 *               2                3
 *                3                4
 */

LoRa_E32 e32ttl(&mySerial);

typedef struct {
  byte deger1;
  byte deger2;
  byte deger3;
  byte deger4;
} Signal;

Signal data;

void setup() {
  Serial.begin(9600);


  e32ttl.begin();
  delay(500);
}

void loop() {

  pot1 = random(0,100);
  pot2 = random(0, 100);
  pot3 = random(0, 100);
  pot4 = random(0, 72000);

  data.deger1 = pot1;
  data.deger2 = pot2;
  data.deger3 = pot3;
  data.deger4 = pot4;

  ResponseStatus rs = e32ttl.sendFixedMessage(highByte(620), lowByte(620), 23, &data, sizeof(Signal));
  Serial.println(rs.getResponseDescription());

  Serial.println("data.deger : ");
  Serial.println(data.deger1);
  Serial.println(data.deger2);
  Serial.println(data.deger3); 
  Serial.println(data.deger4);
    

  delay(500);
}