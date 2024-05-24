#include <SPI.h>  
#include <RH_RF95.h>  

#define RFM95_CS 5  
#define RFM95_RST 14  
#define RFM95_INT 2  

#define RF95_FREQ 434.0

RH_RF95 rf95(RFM95_CS, RFM95_INT);

char value = '0'; // Khai báo biến value ở ngoài hàm loop

void setup() {
  Serial.begin(9600);
  
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  
  rf95.setTxPower(18);
}

void loop() {
  char radiopacket[1] = {value}; // Chỉ cần gửi giá trị của biến value
  rf95.send((uint8_t *)radiopacket, 1);
  Serial.print("Send: ");
  Serial.println(value);
  delay(1000);

  value++;

  if (value > '9')
    value = '0'; // Nếu value vượt quá '9' thì reset về '0'
}
