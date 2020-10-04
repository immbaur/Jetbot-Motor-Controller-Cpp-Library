
#include <linux/i2c-dev.h>
#include <string>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

/** Represents an I2C device.
 */
class I2CDevice
{
public:
  I2CDevice(int i2cAddress, int i2cBus): _address(i2cAddress), _bus(i2cBus), _handle(-1){
    openHandle();
  }

  ~I2CDevice(){
    closeHandle();
  }

  bool isValid(){
    return _handle != -1;
  }

  void writeByte(int command, int data){
    if (isValid())
    {
      selectDevice();
      char buffer[2] = { static_cast<char>(command & 0xFF), static_cast<char>(data & 0xFF)};
      if (write (_handle, buffer, 2) != 2)
      {
          // log::strerror ("Failed to write to device");
      }
    }
  }

private:
  void openHandle(){
    closeHandle();

    std::string filename("/dev/i2c-" + std::to_string(_bus));

    _handle = open(filename.c_str(), O_RDWR);

    if (!isValid())
    {
        // log::strerror ("Couldn't open device");
    }
  }

  void closeHandle(){
    if (isValid()){
        if (close (_handle) < 0){
            // log::strerror ("Couldn't close device");
        }
    }
  }

  void selectDevice(){
      if (ioctl (_handle, I2C_SLAVE, _address & 0x7F) < 0)
      {
          // log::strerror ("Failed to select device");
      }
  }

  const int _address;
  const int _bus;
  int _handle;
};
