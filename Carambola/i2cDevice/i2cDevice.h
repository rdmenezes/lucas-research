#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#define I2C_BUS_PREFIX "/dev/i2c-"
#define I2C_MSB_FIRST 1
#define I2C_LSB_FIRST 2


class i2cDevice {
public:
	i2cDevice(unsigned short bus, uint8_t address);
	bool write(uint8_t *data, int length);
	bool writeReg(uint8_t reg, uint8_t value);
	bool read(uint8_t *data, int length);
	bool read(uint8_t *data_in, int l_in, uint8_t *data_out, int l_out);
	short getShort(uint8_t reg);
	unsigned short getUnsignedShort(uint8_t reg);
	void setWait(int wait);

private:
	char bus_path[12];
	int bus_handle;
	uint8_t address;
	char endianness;
	int usec;

};

