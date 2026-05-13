#include "LoRa_E32.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>

struct can_frame canMsg;  // Bu satır, MCP_CAN kütüphanesinde tanımlanan bir veri yapısını (can_frame) kullanarak bir CAN mesajı almak için bir değişken tanımlar. Bu değişken, alınan CAN mesajını depolar.
MCP2515 mcp2515(10);      //Bu satır, MCP2515 nesnesini oluşturur ve Arduino'daki CS (Chip Select) pinini 10 olarak belirler. Bu, MCP2515 ile iletişim kurmak için kullanılır.

int Hiz;
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

  Serial.begin(9600);

  mcp2515.reset();

  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);  // MCP2515'in CAN hızını 500KBPS ve saat frekansını 8MHz olarak ayarlar.
  mcp2515.setNormalMode();

  e32ttl.begin();
  delay(500);
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)  // Bu ifade, MCP2515 üzerinden bir mesajın okunup okunmadığını kontrol eder. Eğer mesaj okunmuşsa (ERROR_OK durumu), altındaki kodu çalıştırır.
  {
    if (canMsg.can_id == 0x036)  //Alınan mesajın ID'sini kontrol eder. Eğer mesajın ID'si 0x036 ise, aşağıdaki işlemleri gerçekleştirir.
    {
      Hiz= canMsg.data[0];
      Sicaklik = canMsg.data[1];
      Sicaklik2= canMsg.data[2];
      Voltaj= canMsg.data[3];
      Voltaj2= canMsg.data[4];
      KalanEnerji= canMsg.data[5];
      KalanEnerji2= canMsg.data[6];
      

      data.deger1 = Hiz;
      data.deger2 = Sicaklik;
      data.deger3 = Sicaklik2;
      data.deger4 = Voltaj;
      data.deger5 = Voltaj2;
      data.deger6 = KalanEnerji;
      data.deger7 = KalanEnerji2;

      ResponseStatus rs = e32ttl.sendFixedMessage(highByte(620), lowByte(620), 23, &data, sizeof(Signal));
      Serial.println(rs.getResponseDescription());

      Serial.println("data.deger : ");
      Serial.println(data.deger1);
      Serial.println(data.deger2);
      Serial.println(data.deger3);
      Serial.println(data.deger4);


      delay(500);
    }
  }
}

