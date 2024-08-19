#include <MKRWAN.h> // Handles LoRaWAN communication.
#include <TinyGPSPlus.h> //Processes GPS data.
#include <math.h> //Provides mathematical functions.
#include "arduino_secrets.h" // Contains sensitive data like AppEUI and AppKey.

#define gpsPort Serial1 //gpsPort is set to use Serial1 for GPS communication.

TinyGPSPlus gps; //Creates gps object to handle GPS data.
LoRaModem modem;// Creates modem object for LoRaWAN communication.

//latitude and longitude store GPS coordinates.
double latitude = 0.0;
double longitude = 0.0;

//store LoRaWAN credentials.
String appEui = SECRET_APPEUI;
String appKey = SECRET_APPKEY;

unsigned long lastConnectionTime = 0L; // tracks the last time data was sent.
const unsigned long postingInterval = 120000L; //defines how often to send data (every 2 minutes).
void setup() {
  Serial.begin(115200);
  delay(5000);
  gpsPort.begin(9600);

//Starts LoRa module using the EU868 band.
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
  }
  //Prints module version and device EUI for verification.
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
//Joins the LoRaWAN network using OTAA (Over-The-Air Activation) with appEui and appKey.
  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
  } else {
    Serial.println("Joined");
  }
}

void loop() {
  // This displays information every time a new sentence is correctly encoded.
  while (gpsPort.available() > 0) {
    char c = gpsPort.read();
    Serial.print(c); // Display raw data on the serial monitor
    
    if (gps.encode(c)) {
      Serial.println("GPS data encoded"); // Debug statement

      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        longitude = gps.location.lng();

        Serial.print("Latitude: ");
        Serial.print(latitude, 6);
        Serial.print(", Longitude: ");
        Serial.print(longitude, 6);
        Serial.println();
      } else {
        Serial.print(F("INVALID LOCATION"));
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

void sendLoRaPayload() { 
  //Converts latitude and longitude to a byte array.
  //Packs the payload array with latitude and longitude.
  //Prints the payload bytes to the serial monitor.
  //Sends the payload via LoRaWAN.
  //Prints the status of the message sending process.

  byte payload[8];
  int offset = 0;

  int32_t lat = round(latitude * 1e7);
  int32_t lng = round(longitude * 1e7);

  Serial.print("Raw lat: ");
  Serial.println(lat);
  Serial.print("Raw lng: ");
  Serial.println(lng);

  intToBytes(payload + offset, lat, 4);
  offset += 4;
  intToBytes(payload + offset, lng, 4);

  Serial.print("Payload bytes: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(payload[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

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
  for (uint8_t x = 0; x < byteSize; x++) {
    buf[x] = (byte) (i >> (x * 8));

    //Converts an integer into a byte array.
    //Shifts the integer bits and stores them in the buffer
  }
}