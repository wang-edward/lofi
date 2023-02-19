#include "serial/serial_port.h"
#include "serial/serial_devices.h"
#include "serial/CompositeData.hpp"
#include <csignal>		// So std::signal can work
#include <sstream>

namespace lofi {

// Ctrl+C handler function
void sig_handler(int s) {
  printf("Caught signal %d\n", s);
  exit(1);
}

class Serial {

public:
  

  Serial() {
// Define the Ctrl+C handler function
    std::signal(SIGINT, sig_handler);
    // List available ports for user choice
    mVec_ports = mEnum_ports.GetDevices();
    if (mVec_ports.size() == 0) {
        PCOUT << "No serial ports found on device. Quitting." << std::endl;
        return;
    }

    // std::cout<<mVec_ports.at(PORT_INDEX)<<std::endl;

    // Attempt to open the selected port
    int serial_result = mSerial.open_port(mVec_ports.at(PORT_INDEX).calloutDevice, BAUD, 50);
    if(serial_result < 0) {
      PCOUT << "SERIAL CONNECTION FAILED" << std::endl;
      return;
    }
  }

  bool read(CompositeData& c) {
		std::string read_str;
    int rr = 0;
    rr = mSerial.sreadline(read_str);

    if(rr <= 0) {
      return false;
    } else {
      std::vector<float> buf;
      std::stringstream ss(read_str);
      float temp;
      while (ss >> temp) {
        buf.push_back(temp);
      }
      if (buf.size() == 6) {
        std::cout<<"goodiz"<<std::endl;
        // c.pos0 = buf[0];
        // c.pos1 = buf[1];
        // c.pos2 = buf[2];
        // c.button0 = buf[3];
        // c.button1 = buf[4];
        // c.button2 = buf[5];
      }
      return true;
    }
  } 
  

private:
  SERIAL_PORT mSerial;
  INTERFACE_CLASS mEnum_ports;
  std::vector<SerialDevice> mVec_ports;
  const int PORT_INDEX = 2;
  const int BAUD = 9600;
    
  std::string out_str;





};

} // namespace lofi
