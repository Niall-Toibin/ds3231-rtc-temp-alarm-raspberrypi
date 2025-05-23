/*
 * I2C.h
 * Copyright (c) 2025 Derek Molloy (www.derekmolloy.ie)
 */

#ifndef I2C_H_
#define I2C_H_

#define I2C_0 "/dev/i2c-0"
#define I2C_1 "/dev/i2c-1"

namespace een1071 {

/**
 * @class I2CDevice
 * @brief Generic I2C Device class that can be used to connect to any type of I2C device and read or 
 * write to its registers. Make sure you select the correct I2C bus
 */
class I2CDevice{
private:
	unsigned int bus;
	unsigned int device;
	int file;
public:
	I2CDevice(unsigned int bus, unsigned int device);
	virtual int open();
	virtual int write(unsigned char value);
	virtual unsigned char readRegister(unsigned int registerAddress);
	virtual unsigned char* readRegisters(unsigned int number, unsigned int fromAddress=0);
	virtual int writeRegister(unsigned int registerAddress, unsigned char value);
	virtual void debugDumpRegisters(unsigned int number = 0xff);
	virtual void close();
	virtual ~I2CDevice();
};

} /* namespace een1071 */

#endif /* I2C_H_ */
