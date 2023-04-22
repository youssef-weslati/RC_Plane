# RC Plane Project

This project is aimed at creating a simple remote-controlled (RC) plane using an ESP32 Doit DevKit v1 and an nRF24L01 wireless module for communication between the remote controller and the plane.

## Getting Started

### Prerequisites

To use this project, you will need the following components:

- ESP32 Doit DevKit v1
- nRF24L01 wireless module
- RC plane kit (including brushless motors, ESC, servos, and other necessary components)
- Battery for the plane
- Battery for the remote controller
- Breadboard and jumper wires

### Installation

1. Install the PlatformIO IDE on your computer.
2. Clone this GitHub repository to your computer.
3. Open the project in PlatformIO and upload the code to your ESP32 Doit DevKit board.
4. Assemble the RC plane according to the manufacturer's instructions, and connect the motors, ESC, servos, and other components to the appropriate pins on the ESP32 board.
5. Connect the nRF24L01 wireless module to the ESP32 board using the SPI pins (MOSI, MISO, SCK) and the CE and CSN pins.
6. Connect the battery to the RC plane and turn it on.
7. Connect the battery to the remote controller and turn it on.
8. The plane should now be ready to fly using the remote controller.

## Usage

The code uploaded to the ESP32 board will read the analog input values from the remote controller's potentiometer and joystick and send them over the wireless module to the plane's ESP32 board. The plane's ESP32 board will receive the values, map them to servo positions for the plane's control surfaces (elevator, ailerons, rudder), and to throttle position for the plane's engine.

The remote controller and the plane's ESP32 board will communicate with each other using the nRF24L01 wireless module. The module will be set up with a specific channel and address for the communication.

## Conclusion

This project demonstrates how to use an ESP32 Doit DevKit v1 and an nRF24L01 wireless module to build a simple RC plane. By following the instructions in this README file, you should be able to assemble and program the plane and remote controller, and have fun flying the plane.
