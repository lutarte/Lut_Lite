/*
  OSC INTERACTIVE WALL
  Envia trigger a por la RED interna del ESP a OpenFrameworks para reproducir Videos

*/

// LIBRERIAS WIFI - OSC//

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

//////////////////////////////////////////////
/////////////// WIFI CONFIG //////////////////
//////////////////////////////////////////////

char ssid[] = "Lut Estudio Lab"; // Router Nanme
char pass[] = "hacemostecnologia2019"; // Pass

////////////////////
// OSC CONFIG //////
////////////////////

//IP ADRESS AND PORT - TO OPEN FRAMEWORKS
int ip[] = {192, 168, 0, 118};
int port = 7000;

WiFiUDP Udp;                                 // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(ip[0], ip[1], ip[2], ip[3]); // remote IP of your computer to openFrameworks Soft
const unsigned int outPort = port;
const unsigned int localPort = 7001;        // local port to listen for UDP packets (here's where we send the packets)

////////////////////////////////
// INPUT PIN VARIABLES /////////
////////////////////////////////

// D0 = Boton 1 = GPI-16
// D1 = Boton 2 = GPI-05
// D2 = Boton 3 = GPI-04
// D5 = Boton 4 = GPI-14
// D6 = Boton 5 = GPI-12
// D7 = Boton 6 = GPI-13
// D8 = Boton 7 = GPI-15

const int boton[] = {16, 5, 4, 14, 12, 13, 15};
int botonState[] = {1, 1, 1, 1, 1, 1, 1};
int botonIndex[] = {0, 1, 2, 3, 4, 5, 6};
int buttomsSize = 7;
const int globalDelay = 50;

boolean buttonRead = true;
int changeState = 0;

// LED MONITOR
const int ledPin =  2;      // the number of the LED pin

void setup() {

  Serial.begin(115200);

  // Connect to WiFi network
  wifiSetUp();

  for (int i = 0; i < sizeof(boton); i++) {
    pinMode(boton[i], FUNCTION_3);
    pinMode(boton[i], INPUT);
  }

  pinMode(ledPin, OUTPUT);
}

void loop() {
  
  // Blink LED if WiFi is well connected
  wifiMonitor();

  if (buttonRead == true) {
    readOnlyButtoms();
  }

  if (buttonRead == false) {
    OSCRead();
  }

   Serial.print("ButtonRead: ");
   Serial.println(buttonRead);
}

void readOnlyButtoms() {

  for (int i = 0; i < buttomsSize; i++) {
    botonState[i] = digitalRead(boton[i]);
    OSC_out(botonIndex[i]);

    if (botonState[0] == 1 || 
        botonState[1] == 1 || 
        botonState[2] == 1 || 
        botonState[3] == 1 || 
        botonState[4] == 1 || 
        botonState[5] == 1 || 
        botonState[6] == 1) {
          
      buttonRead = false;
    } else {
      buttonRead = true;
    }
  }
}


/// LEE OSC MESSAGE Y CAMBIA LA VARIABLE buttonRead ////

void OSCRead() {
  OSCMessage msg;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError()) {
      buttonRead = true;
      Serial.print(buttonRead);
      escenarioIntro();
    }
  }
}


/// ENVIA VIDEO POR DEFAULT  ////

void escenarioIntro() {
  OSCMessage msg("/escenario0");
  msg.add((int32_t)0);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp); Udp.endPacket(); msg.empty();

  delay(300);
  Serial.println("ESCENARIO INTRO");
}
