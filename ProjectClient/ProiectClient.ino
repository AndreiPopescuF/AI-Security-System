#include <WiFi.h>
#include <WiFiUdp.h>
#include <coap-simple.h>


//buzzer

//#include "pitches.h"
// Define pin 10 for buzzer, you can use any other digital pins (Pin 0-13)
#include "pitches.h"
#define BUZZZER_PIN  13 // ESP32 pin GPIO18 connected to piezo buzzer

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


//buzzer
//matrix
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 4
#define CS_PIN 5

MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
//matrix




const char* ssid = "UPB-Guest";
const char* password = NULL ;
IPAddress serverIP(10, 41, 66, 157); // Replace with your server's IP address

WiFiUDP udp;
Coap coap(udp);


const int trigPin = 15;
const int echoPin = 14;
#define SOUND_SPEED 0.034
long duration;
float distanceCm;


void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Display.begin();
  Display.setIntensity(0);
  Display.displayClear();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  Serial.println(distanceCm);

  delay(1000);
  // Send CoAP GET request to check LED status
  coap.get(serverIP, 5683, "light"); 


  // Send CoAP PUT request to toggle LED state
  if (distanceCm < 10) {
    Serial.println(distanceCm);
    coap.put(serverIP, 5683, "light", "1");
    Display.setTextAlignment(PA_CENTER);
    Display.print("Intruder");

    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(BUZZZER_PIN, melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(BUZZZER_PIN);
    }

    delay(2000);

   } else { 
    Serial.println(distanceCm);
    Display.displayClear();
    Display.setTextAlignment(PA_CENTER);
    Display.print("Google");
    coap.put(serverIP, 5683, "light", "0");
  }
}