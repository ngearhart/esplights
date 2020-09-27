// Connect to wifi – returns true if successful or false if not
boolean ConnectWifi(uint16_t ledCount, CRGB* leds, int (*ticker)(byte, uint16_t, CRGB*))
{
  boolean state = true;
  int i = 0;

  WiFi.setHostname(hostname); // TODO fix hostname
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    // Fade lights while connecting
    for (byte tick = 0; tick < 20; tick++) {
      delay(80);
      (*ticker)(tick, ledCount, leds);
      FastLED.show();
    }
    Serial.print(".");
    if (i > 20){
      state = false;
      break;
    }
    i++;
  }
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Hostname: ");
    Serial.println(WiFi.getHostname());
  } else {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}
