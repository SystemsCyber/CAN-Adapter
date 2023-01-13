# Testing Information

This directory is intended for PlatformIO Unit testing using Unity.

This directory contains tests for the CAN adapater in order to prove full functionality of the device once assembled. These tests include:

* CAN communication:
  * Tests that the device is able to send and recieve CAN messages on CAN1, CAN2, and CAN3
* LED:
  * This turns the LEDS on and off that is for the user to visually confirm
* Logging Capabilities:
  * Tests that the Teensy 4.1 is able to write and read to the SD card
  * Will also test SD logging speed with full bus load
* Serial Communication:
  * Tests that the device is able to write to the serial port in order to monitor the devices functionalities


More information about PIO Unit Testing:

* https://github.com/platformio/platform-teensy/tree/master

- https://docs.platformio.org/page/plus/unit-testing.html
- https://docs.platformio.org/en/latest/core/userguide/cmd_test.html#cmd-test
