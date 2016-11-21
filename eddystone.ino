/*
 * Eddystone for Simblee 
 * 
 */

#include <SimbleeBLE.h>

//maxium payload is 31 bytes
struct MESSAGE_ADVERTISEMENT {
  
  byte raw1[4] = {
    0x03,  // Length
    0x03,  // Param: Service List
    0xAA, 
    0xFE,  // Eddystone ID
  };
  
  byte l =  0x01;  // Dynamicall calculated
  
  byte raw2 [6] = { 
    0x16,  // Service Data
    0xAA, 
    0xFE, // Eddystone ID
    0x10,  // URL flag
    0xEB,  // Power
    0x03 // https:// use 0x01 for https://www.
  }; 

  byte url[20] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } ;

};

MESSAGE_ADVERTISEMENT message;

void setup() {
  
  //TODO: use 0x07 for .com/
  char url[]= "google.com?q=1234";
    
  memcpy(message.url, &url, sizeof(url)-1);

  message.l = (byte) (sizeof(url) + 6 - 1);
  
  SimbleeBLE.connectable = false;
  SimbleeBLE_advdata = (uint8_t *)&message;
  SimbleeBLE_advdata_len = sizeof(message);
    
  // start the BLE stack
  SimbleeBLE.begin();
}

void loop() {
  // switch to lower power mode
  Simblee_ULPDelay(INFINITE);
}

