#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArtnetWifi.h>
#include <FastLED.h>

// WIFI
// You must add a wifi.ino file to this project that defines the following vals
//const char* ssid = "SSID";
//const char* password = "pAsSwOrD";
//const char* hostname = "room7led";

// LED Strip
const int numLeds = 20;
const int numberOfChannels = numLeds * 3; // Total number of DMX channels you want to receive (1 led = 3 channels)
#define DATA_PIN 14 //The data pin that the WS2812 strips are connected to.
CRGB leds[numLeds];

// Artnet settings
ArtnetWifi artnet;
const int startUniverse = 0;

int previousDataLength = 0;

byte seq0 = 0;
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  if (seq0 != data[0]) {
    seq0 = data[0];
    Serial.print("Seq0: ");
    Serial.println(seq0);
  }
  // read universe and put into the right part of the display buffer
  for (int i = 0; i < length / 3; i++)
  {
    int led = i + (universe - startUniverse) * (previousDataLength / 3);
    if (led < numLeds)
    {
      leds[led] = CRGB(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
    }
  }
  previousDataLength = length;     
  FastLED.show();
}

void setup()
{
  Serial.begin(9600);
  ConnectWifi();
  artnet.begin();
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, numLeds);

  // onDmxFrame will execute every time a packet is received by the ESP32
  artnet.setArtDmxCallback(onDmxFrame);
}

void loop()
{
  // we call the read function inside the loop
  artnet.read();

  // Check if disconnected from wifi
  if (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Disconnected from WiFi. Trying again...");
    ConnectWifi();
  }
}
