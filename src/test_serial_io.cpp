//
// test_serial_io.cpp
//
// File for testing the ArduinoSerialLib code, by writing a user input string to the
// Arduino and reading back the echo response. 
//
// Use the serial_write_test.ino sketch in conjunction with this file. That sketch 
// will take the string and send back it's echo, exactly as was read by the board. 
// Look into it's code for more details.
//
// Author: Rodrigo R. M. B. Maia
// Created: 12-Sept-2019
//

#include "serial/Serial.hpp"

int main() {
  lofi::Serial bro;
  lofi::CompositeData man;
  while (1) {
    bool work = bro.read(man);
    std::cout<<man.pos0<<std::endl;
  }
  return 0;
}
