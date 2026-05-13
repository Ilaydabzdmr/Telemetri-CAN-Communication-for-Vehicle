#include <SPI.h>         
#include <mcp2515.h>     

#define potPin A0   
int potValue=0;
   

struct can_frame canMsg;//MCP_CAN kütüphanesindeki bir veri yapısını (can_frame) kullanarak bir CAN mesajı oluşturmak için bir değişken tanımlar. Bu değişken, CAN mesajını depolar.
MCP2515 mcp2515(10); //MCP2515 nesnesini oluşturur ve Arduino'daki CS (Chip Select) pinini 10 olarak belirler.

void setup() 
{
  Serial.begin(9600);
  SPI.begin();   //SPI haberleşmesini başlatır. Bu, diğer cihazlarla (MCP2515 gibi) SPI aracılığıyla iletişim kurabilmek için gereklidir.            
  
  mcp2515.reset(); //MCP2515'i sıfırlar.
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ);//MCP2515'in CAN hızını 500KBPS ve saat frekansını 8MHz olarak ayarlar.
  mcp2515.setNormalMode();// MCP2515'i normal modda ayarlar.

  canMsg.can_id  = 0x036; // CAN mesajının ID'sini 0x036 olarak ayarlar.         
  canMsg.can_dlc = 1;// CAN mesajının veri uzunluğunu (DLC) 1 byte olarak ayarlar.              
 
}

void loop() 
{
  potValue = analogRead(potPin);
  potValue = map(potValue,0,1023,0,255);//Okunan analog değeri 0 ila 1023 aralığından 0 ila 255 aralığına yeniden haritalar. Bu, potansiyometrenin değerini 0 ile 255 arasında bir değere dönüştürür.
  Serial.println(potValue);
    
  canMsg.data[0] = potValue; // CAN mesajının veri alanına potansiyometre değerini ekler.      
  //canMsg.data[1]= 0x00;
  
  mcp2515.sendMessage(&canMsg);// Oluşturulan CAN mesajını MCP2515 üzerinden gönderir. 
  delay(200);
}

s