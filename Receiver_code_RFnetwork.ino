// Node00
//NRF24L01 Receiver Arduino Code

int relaypin = 7;

#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

RF24 radio(9, 10);                    // nRF24L01 (CE,CSN)
RF24Network network(radio);           // Include the radio in the network

const uint16_t this_node = 00;         // Address of our node in Octal format
unsigned long data[2];                  // number of sensors
 
unsigned long data1; 
unsigned long data2;
 
void setup() {
  Serial.begin(9600);
  pinMode(relaypin, OUTPUT);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
}
void loop() { 
    network.update();
        while ( network.available() ) { // Is there any incoming data?
        RF24NetworkHeader header;
         
        network.read(header, &data, sizeof(data)); // Read the incoming data
         
        if (header.from_node == 1) {             // If data comes from Node 01
          data1 = data[0];
//          Serial.println("NODE1: TANK DATA");
//          Serial.println(data1); 
        }
         
        if (header.from_node == 2) {              // If data comes from Node 02
          data2 = data[0]; 
//          Serial.println("NODE2: SUMP DATA");
//          Serial.println(data2);
        }


//        CODE
          if(data2 == 0){
            if(data1 == 0){
              Serial.println("Switch OFF The Motor");
              digitalWrite(relaypin, HIGH);
            } else {
              Serial.println("Switch ON The Motor");
              digitalWrite(relaypin, LOW);
            }
         } else {
          Serial.println("Switch OFF The Motor");
          digitalWrite(relaypin, HIGH);
        }
//        if(data1 == 0){
//            Serial.println("Motor OFF");
//            digitalWrite(relaypin, HIGH);   // OFF MOTOR
//        } else {
//            Serial.println("Motor ON");
//            digitalWrite(relaypin, LOW);  // ON MOTOR
//        }
    }    
}
