#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ESP32_Servo.h>

Servo Engine;
Servo AirleronLeft;
Servo AirleronRight;
Servo Elevator;
Servo Rudder;

//Specifying pins for CE (chip enable), CSN (chip select), MOSI, MISO and SCK pins respectively
RF24 radio(4,5,18,19,23);

//Specifying pins for plane system
int AirleronLeftPin = 32;
int AirleronRightPin = 33;
int ElevatorPin = 25;
int RudderPin = 26;
int EnginePin = 27;
//Plane Values
struct Plane {
  int16_t AirleronLeftVal ;
  int16_t AirleronRightVal ;
  int16_t ElevatorVal ;
  int16_t RudderVal ;
  int16_t EngineVal ;
}Plane;



//Address of this receiver 
const byte address[6] = "00001";



void setup() {
  //attaching pins for plane system
  Engine.attach(EnginePin, 1000, 2000);
  AirleronLeft.attach(AirleronLeftPin, 1000, 2000);
  AirleronRight.attach(AirleronRightPin, 1000, 2000);
  Elevator.attach(ElevatorPin, 1000, 2000);
  Rudder.attach(RudderPin, 1000, 2000);

  //initialization of the nRF24
  radio.begin();

  //Setting the the channel to communicate on
  radio.setChannel(2);

  //Setting the size of the payload which is the data that is transmitted over the wireless communication link
  radio.setPayloadSize(10);

  //Setting the DataRate which determine how fast the data is transmitted over the wireless communication link
  radio.setDataRate(RF24_250KBPS);

  //Setting the address of the receiver
  radio.openReadingPipe(0, address);

  //Setting the power amplifier level to minimum, PA level determine the strength of the transmitted signal
  radio.setPALevel(RF24_PA_MIN);

  //Setting in to transmitter by stopping to receive information
  radio.startListening();
}

void loop() {
  //Check whether there is data to be received
  if (radio.available()) {
    //Read the whole data and store it into the 'Plane' structure
    radio.read(&Plane, sizeof(Plane)); 
    

    //Write the values to the servos
    Engine.write(Plane.EngineVal);
    AirleronLeft.write(Plane.AirleronLeftVal);
    AirleronRight.write(Plane.AirleronRightVal);
    Elevator.write(Plane.ElevatorVal);
    Rudder.write(Plane.RudderVal);

  }
  else
  { //if we loose connection the plane will land 
    Engine.write(0);
    AirleronLeft.write(0);
    AirleronRight.write(0);
    Elevator.write(140);
    Rudder.write(90);
  }

}
