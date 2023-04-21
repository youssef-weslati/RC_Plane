#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//Specifying pins for CE (chip enable), CSN (chip select), MOSI, MISO and SCK pins respectively
RF24 radio(4,5,18,19,23); 

//Specifying pins for potentiometer and the joystick
int pot = 32;
int pitch = 33;
int roll = 34;
int yaw = 35;

//Address of the receiver to which we will send the data, the address is a unique identifier that allows the module to distinguish between different receivers
const byte address[6] = "00001";

//Variables to store the values of the potentiometer and the joystick
struct Data_Package {
  int16_t potval;
  int16_t pitchval;
  int16_t rollval;
  int16_t yawval;
}

Data_Package data;

void setup() {

  //initialization of the nRF24
  radio.begin();

  //Setting the the channel to communicate on
  radio.setChannel(2);

  //Setting the size of the payload which is the data that is transmitted over the wireless communication link
  radio.setPayloadSize(32);

  //Setting the DataRate which determine how fast the data is transmitted over the wireless communication link
  radio.setDataRate(RF24_250KBPS);

  //setting the address of the receiver
  radio.openWritingPipe(address);

  //Setting the power amplifier level to minimum, PA level determine the strength of the transmitted signal
  radio.setPALevel(RF24_PA_MIN);

  //Setting in to transmitter by stopping to receive information
  radio.stopListening();
}

void loop() {
  //Speed Control
  data.potval = analogRead(pot);
  

  //Pitch Control
  data.pitchval = analogRead(pitch);
  

  //Roll control
  data.rollval = analogRead(roll);
  

  //Yaw control
  data.yawval = analogRead(yaw);

  // Send the whole data from the structure to the receiver
  radio.write(&data, sizeof(Data_Package));

}