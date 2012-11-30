/***********************************************
* Wireless iRobot Control Sender For Leonardo  *
*                                              *
* Written by Joshua Long on 11/2012            *
*                                              *
***********************************************/

// Imports
#include <Wire.h>
#include <wii_classic.h>

// Instance Variables

boolean ready = true;
// Setup

void setup(){
  classic_init();
  initXbee();
}

// Main Program Loop
void loop(){
  get_data();
  sendToCom(data_pack);
  delay(100);
  // for test purposes
  //print_data();
  
}

/******************************
          Methods
******************************/

// Initionalization Methods

// Xbee initionalization
void initXbee()
{
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

// Send Data to Computer
void sendToCom(uint8_t b[])
{
  String packet = "";
  for(int i=0; i < 6; i++)
  {
    packet += (char) b[i];
  }
  Serial.print(packet);
}




