/***********************************************
* Wireless iRobot Control Reciever For Uno     *
*                                              *
* Written by Joshua Long on 11/2012            *
*                                              *
***********************************************/

// Imports
#include <SoftwareSerial.h>
#include <wii_classic_decoder.h>

// Instance Variables
// Set up the Software Serial Communications
SoftwareSerial robot = SoftwareSerial(2, 3);
SoftwareSerial xbee = SoftwareSerial(4, 5);
// Songs

// Controller data
byte controlPacket[6] = {255, 255, 255, 255, 255, 255};
String data = "";
// iRobot data
int velocity = 00;
int radius = 00;
boolean isControlable = false;
//byte song num = 00;
//boolean playSong = 00;
//boolean songPlaying = 00;

// Setup
void setup(){
  // Initionalize iRobot
  initRobot();
  // Initionalize Xbee
  initXbee();
  // Load iRobot Songs
  // loadSongs(); not yet available
  // Setup Serial Comunication for testing purposes
  Serial.begin(9600);
}

// Main Program Loop
void loop(){
  // Reset data String for new data
  data = "";
  // Get data from xbee
  while(xbee.available() > 0)
  {
    data += (char) xbee.read();
    delay(10);
  }
  // If data is viable update control data packet
  if(data.length() == 6)
  {
     updateControlPacket(data);
  }
  // Put control data packet into wii_classic byte decoder
  load_packet(controlPacket);
  // Update iRobot data bytes
  updateRobotControlBytes();
  // Send data to iRobot for execution
  robotExecute();
  //Print data for testing purposes
  //print_data();
  //Serial.println(data);
}

/******************************
          Methods
******************************/

// Initionalization Methods

// iRobot initionalization
void initRobot()
{
  delay(2000);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  robot.begin(57600);
  robot.write(128);
  robot.write(131);
  isControlable = true;
}

// Xbee initionalization
void initXbee()
{
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  xbee.begin(9600);
}

// Load Songs

// Load a single song

// Recieve a byte of data
char xbeeRecieve()
{
    char b = xbee.read();
    return b;
}

// Update controller data
void updateControlPacket(String s)
{
  for(byte i = 0; i < 6; i++)
  {
    controlPacket[i] = (byte) s.charAt(i);
  }
}

// Update the bytes used to control the iRobot
void updateRobotControlBytes()
{
   if(get_l_joy_y() < 27 || get_l_joy_y() > 31){
     velocity = map(get_l_joy_y(), 0, 56, -500, 500);
     velocity = constrain(velocity, -500, 500);
     
     if(get_l_joy_x() < 27) {
       radius = map(get_l_joy_x(), 0, 27, 1, 2000);
       radius = constrain(radius, 1, 2000);
     }
     else if(get_l_joy_x() > 31){
       radius = map(get_l_joy_x(), 31, 56, -2000, -1);
       radius = constrain(radius, -2000, -1);
     }
     else{
       radius = 32768;
     }
   }
   else{
     velocity = 0;
     if(get_l_joy_x() < 27)
     {
       radius = 0x0001;
       velocity = map(get_l_joy_x(), 0, 27, 400, 0);
     }
     else if(get_l_joy_x() > 31)
     {
       radius = 0xFFFF;
       velocity = map(get_l_joy_x(), 31, 56, 0, 400);
     }
     else{
       radius = 32768;
     }
     velocity = constrain(velocity, 0, 400);
   }
   if(get_home())
   {
       robot.write(143); 
   }
}

// Sends execution data to iRobot
void robotExecute()
{
   // Sends the command to move
   robot.write(137);
   robot.write(highByte(velocity));
   robot.write(lowByte(velocity));
   robot.write(highByte(radius));
   robot.write(lowByte(radius)); 
}


