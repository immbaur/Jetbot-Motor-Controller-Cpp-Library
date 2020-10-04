#include <chrono>
#include <thread>
#include <cstdlib>
#include <iostream>

#include "i2c_device.h"
#include "motor_controller.h"

int main(int argc, char **argv) {

  std::shared_ptr<I2CDevice> i2cDeviceHandle = std::make_shared<I2CDevice>(0x5D, 1);

  MotorController motorRight(i2cDeviceHandle, 0);
  MotorController motorLeft(i2cDeviceHandle, 1);

  std::cout << atoi(argv[1]) << atoi(argv[2]) << std::endl;

  motorRight.setSpeed(atoi(argv[1]));
  motorLeft.setSpeed(atoi(argv[2]));

  motorRight.enable();
  motorLeft.enable();


  std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  //
  // motorRight.setSpeed(-100);
  // motorLeft.setSpeed(-100);
  //
  // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  //
  motorRight.disable();
  motorLeft.disable();

  // i2cdevice.writeByte(0x70,0x01);
  // i2cdevice.writeByte(0x20,100);
  // i2cdevice.writeByte(0x21,100);

  return 0;
}
