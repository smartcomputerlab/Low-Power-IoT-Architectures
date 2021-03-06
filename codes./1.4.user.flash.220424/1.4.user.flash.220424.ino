#include "Arduino.h"
#define ROW 0
#define ROW_OFFSET 100

//CY_FLASH_SIZEOF_ROW is 256 , CY_SFLASH_USERBASE is 0x0ffff400
#define addr CY_SFLASH_USERBASE+CY_FLASH_SIZEOF_ROW*ROW + ROW_OFFSET

uint8_t data1[512];
uint8_t data2[512];
uint8_t data3;
uint8_t data4;

void setup() 
{
  Serial.begin(9600);delay(100);
  Serial.println();Serial.println();
  // generate data in data1
  for(int i=0;i<512;i++){
    data1[i]=(uint8_t)i;
  }
  // write data1 to flash at addr
  FLASH_update(addr,data1,sizeof(data1));
  //read flash at addr to data2
  FLASH_read_at(addr,data2,sizeof(data2)); 
  
  uint16_t error=0;
  for(int i=0;i<512;i++){
    if(data1[i]!=data2[i])
    {
      Serial.printf("error:data1[%d] %d , data2[%d] %d \r\n",i,data1[i],i,data2[i]);
      error++;
    }
  }

  Serial.printf("Number of error bytes: %d\r\n",error);
  //read a byte at addr to data4
  FLASH_read_at(addr,&data4,1);
  Serial.printf("data4:%d\r\n",data4);
  data3=100;
  //write a byte at addr
  FLASH_update(addr,&data3,1);
  //read a byte at addr to data4
  FLASH_read_at(addr,&data4,1);  
  Serial.printf("data4:%d\r\n",data4);
}

void loop() {
  Serial.println("in the loop");
  delay(2000);
}
