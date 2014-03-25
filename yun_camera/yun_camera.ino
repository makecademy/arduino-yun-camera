// Sketch to upload pictures to Dropbox when motion is detected
#include <Bridge.h>
#include <Process.h>

// Picture process
Process picture;

// Filename
String filename;

// Pin
int pir_pin = 8;

// Path
String path = "/mnt/sda1/";

void setup() {
  
  // Bridge
  Bridge.begin();
  
  // Set pin mode
  pinMode(pir_pin,INPUT);
}

void loop(void) 
{
  
  if (digitalRead(pir_pin) == true) {
    
    // Generate filename with timestamp
    filename = "";
    picture.runShellCommand("date +%s");
    while(picture.running());

    while (picture.available()>0) {
      char c = picture.read();
      filename += c;
    } 
    filename.trim();
    filename += ".png";
 
    // Take picture
    picture.runShellCommand("fswebcam " + path + filename + " -r 1280x720");
    while(picture.running());
    
    // Upload to Dropbox
    picture.runShellCommand("python " + path + "upload_picture.py " + path + filename);
    while(picture.running());
  }
}
