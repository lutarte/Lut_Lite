void wifiSetUp() {

  // Start Wifi Settings //
  // Connect to WiFi network

  Serial.println();
  Serial.println("Connecting to:");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  ///////////////////////
  ///////////////////////

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(500);

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
  }
}


void wifiMonitor() {

  // Blink if WiFi is well connected
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(ledPin, HIGH); delay(100);
    digitalWrite(ledPin, LOW); delay(100);
  }
}
