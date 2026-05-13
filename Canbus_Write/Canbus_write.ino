#include <SPI.h>            
#include <mcp2515.h>          

#include <Wire.h> 



struct can_frame canMsg; // Bu satır, MCP_CAN kütüphanesinde tanımlanan bir veri yapısını (can_frame) kullanarak bir CAN mesajı almak için bir değişken tanımlar. Bu değişken, alınan CAN mesajını depolar.
MCP2515 mcp2515(10);  //Bu satır, MCP2515 nesnesini oluşturur ve Arduino'daki CS (Chip Select) pinini 10 olarak belirler. Bu, MCP2515 ile iletişim kurmak için kullanılır.              
 
void setup() {
  
 
  SPI.begin();                      
  
  Serial.begin(9600);              
  
  mcp2515.reset();      

  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); // MCP2515'in CAN hızını 500KBPS ve saat frekansını 8MHz olarak ayarlar.
  mcp2515.setNormalMode();                  
}

void loop() 
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)// Bu ifade, MCP2515 üzerinden bir mesajın okunup okunmadığını kontrol eder. Eğer mesaj okunmuşsa (ERROR_OK durumu), altındaki kodu çalıştırır.
  {
    if(canMsg.can_id==0x036)//Alınan mesajın ID'sini kontrol eder. Eğer mesajın ID'si 0x036 ise, aşağıdaki işlemleri gerçekleştirir.
    {
     int x = canMsg.data[0];
     int y = canMsg.data[1];
     int z = canMsg.data[2];
     int q = canMsg.data[3];// Alınan CAN mesajının veri alanındaki ilk byte'ı alır ve x değişkenine atar.
     Serial.print(x);
     Serial.print("/");
     Serial.print(y);
     Serial.print("/");
     Serial.print(z);
     Serial.print("/");
     Serial.println(q);
     
     
      delay(200);
     }
    }
   
}                  