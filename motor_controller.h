#include <memory>


enum DriverCommand{
  MA_DRIVE = 0x20,
  DRIVER_ENABLE = 0x70
};

class MotorController {

public:
  MotorController(std::shared_ptr<I2CDevice> i2cDeviceHandle, int motorIndex) : _i2cDeviceHandle(i2cDeviceHandle), _motorIndex(motorIndex){
      setSpeed(0);
      disable();
  }

  void enable(){
      _i2cDeviceHandle->writeByte(DriverCommand::DRIVER_ENABLE, 1);
  }

  void disable(){
      _i2cDeviceHandle->writeByte(DriverCommand::DRIVER_ENABLE, 0);
  }

  /** Sets the speed of the motor in meter per second. */
  void setSpeed (int speed){
    _i2cDeviceHandle->writeByte(DriverCommand::MA_DRIVE + _motorIndex, speed);
  }

private:
  const int _motorIndex;
  std::shared_ptr<I2CDevice> _i2cDeviceHandle;
};
