// Node02
// NRF24L01 Transmitter2 Arduino Code

const int trigPin = 7;
const int echoPin = 8;

long duration;
int distance; 

#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

RF24 radio(9, 10);                             // nRF24L01 (CE,CSN)
RF24Network network(radio);                    // Include the radio in the network

const uint16_t this_node = 02;                 // Address of this node in Octal format
const uint16_t node00 = 00; 
unsigned long data[2];                         // number of sensors
 
void setup() {
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);                //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
}
void loop() {
  
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  
  duration=pulseIn(echoPin,HIGH);
  distance=(duration*0.034/2);

  network.update();
  if(distance < 65){
      unsigned long res = 0;      // OFF the Motor 
      data[0] = res;
      RF24NetworkHeader header8(node00);
      bool ok = network.write(header8, &data, sizeof(data)); // Send the data
  } else {
      unsigned long res = 1;      // ON the Motor
      data[0] = res;
      RF24NetworkHeader header8(node00);
      bool ok = network.write(header8, &data, sizeof(data)); // Send the data
  }
  delay(500);
}
