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
  int AirleronLeftVal ;
  int AirleronRightVal ;
  int ElevatorVal ;
  int RudderVal ;
  int EngineVal ;
}Plane;



//Address of this receiver 
const byte address[6] = "00001";

//Variables to store the values of the potentiometer and the joystick
struct Data {
  int16_t potval;
  int16_t pitchval;
  int16_t rollval;
  int16_t yawval;
}Data;


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
  radio.setPayloadSize(32);

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
    //Read the whole data and store it into the 'data' structure
    radio.read(&Data, sizeof(Data)); 
    
    //Mapping the received data
    //Engine
    Plane.EngineVal = map(Data.potval,0, 4095, 0, 180);
    

    //Elevator
    Plane.ElevatorVal = map(Data.pitchval,0, 4095, 0, 180);
    

    //Roll control
    Plane.AirleronRightVal = map(Data.rollval,0, 4095, 0, 180);
    Plane.AirleronLeftVal = map(Data.rollval,0, 4095, 180, 0);

    //Yaw control
    Plane.RudderVal = map(Data.yawval,0, 4095, 0, 180);
    

    //Write the values to the servos
    Engine.write(Plane.EngineVal);
    AirleronLeft.write(Plane.AirleronLeftVal);
    AirleronRight.write(Plane.AirleronRightVal);
    Elevator.write(Plane.ElevatorVal);
    Rudder.write(Plane.RudderVal);

  }

}
