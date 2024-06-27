#include <MKRWAN.h>
#include <TinyGPSPlus.h>
#include <math.h>
#include "arduino_secrets.h"


#define gpsPort Serial1

// The TinyGPSPlus object
TinyGPSPlus gps;
LoRaModem modem;

//double latitude;
//double longitude;

double latitude = 0.0;
double longitude = 0.0;

// Please enter your sensitive data in the Secret tab or arduino_secrets.h
String appEui = SECRET_APPEUI;
String appKey = SECRET_APPKEY;


unsigned long lastConnectionTime = 0L;// last time you connected to the server, in milliseconds
const unsigned long postingInterval = 120000L; // delay between updates, in milliseconds

void setup(){
  Serial.begin(115200);
  delay(5000);
  gpsPort.begin(9600);

  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
   
  }
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
  }else{
     Serial.println("Joined");
  }
 

}

void loop(){
  //This displays information every time a new sentence is correctly encoded.
  while (gpsPort.available() > 0){
    if (gps.encode(gpsPort.read())){
      
      if (gps.location.isValid()){
        latitude = gps.location.lat();
        longitude = gps.location.lng();
        Serial.print(latitude, 6);
        Serial.print(F(","));
        Serial.print(longitude, 6);
      }else{
        Serial.print(F("INVALID"));
      }
      Serial.println();
      Serial.println("End of read");
      
    }
    
  }

  if (millis() - lastConnectionTime > postingInterval) {
    sendLoRaPayload();
    lastConnectionTime = millis();
    
  }

}


void sendLoRaPayload(){ 
  byte payload[8];
  int offset = 0;

  int32_t lat = round(latitude * 1e7);
  int32_t lng = round(longitude * 1e7);

  intToBytes(payload + offset, lat, 4);
  offset += 4;
  intToBytes(payload + offset, lng, 4);
 

  int err;
  modem.beginPacket();
  modem.write(payload, sizeof(payload));
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }

}

/* From https://github.com/thesolarnomad/lora-serialization/tree/master */
void intToBytes(byte* buf, int32_t i, uint8_t byteSize) {
  for(uint8_t x = 0; x < byteSize; x++) {
      buf[x] = (byte) (i >> (x*8));
  }
}
