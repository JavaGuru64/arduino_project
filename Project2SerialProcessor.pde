import processing.serial.*;

Serial portController, portRobot;
String b = "null";

void setup()
{
  size(500, 500);
  portController = new Serial(this, "/dev/tty.usbmodemfa131", 9600);
  portRobot = new Serial(this, "/dev/tty.usbserial-A900XTDE", 9600);
}

void draw()
{
  String data = "";
  background(0);
  text("I am either processing your data or not.\n"
         + "I am either correct or not.\n"
         + "But, I am on.\n\n"
         + "Processing " + b +".", 25, 25);
  
  while(portController.available() > 0)
  {
    data += portController.readString();
    b = data;
    try
    {
        Thread.sleep(10);
    }catch(Exception e){}
  }
  portRobot.write(data);
  redraw(); 
}

