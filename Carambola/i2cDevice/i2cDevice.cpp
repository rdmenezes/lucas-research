#include "i2cDevice.h"

i2cDevice::i2cDevice(unsigned short bus, uint8_t address) {
	sprintf(bus_path, "%s%d", I2C_BUS_PREFIX, bus);
	this->address = address >> 1;
	bus_handle = open(bus_path, O_RDWR);
	ioctl(bus_handle, I2C_SLAVE, this->address);
	this->endianness = I2C_MSB_FIRST;
	this->usec = 100;
}


bool i2cDevice::write(uint8_t *data, int length) {
	::write(bus_handle, data, length);
	return true;
}

bool i2cDevice::writeReg(uint8_t reg, uint8_t value) {
	uint8_t data[2];
	data[0] = reg;
	data[1] = value;
	write(data,2);
}

bool i2cDevice::read(uint8_t *data, int length) {
	::read(bus_handle, data, length);
	return true;
}
bool i2cDevice::read(uint8_t *data_in, int l_in, uint8_t *data_out, int l_out) {
	write(data_in, l_in);
	usleep(usec);
	return read(data_out, l_out);
}

short i2cDevice::getShort(uint8_t reg) {
	uint8_t data[2];
	short out;
	read(&reg, 1, data, 2);
	if (endianness == I2C_MSB_FIRST) {
		out = ((short)((short)data[1] + ((short)data[0] << 8)));
	} else {
		out = ((short)((short)data[0] + ((short)data[1] << 8)));
	}
	return out;
}
unsigned short i2cDevice::getUnsignedShort(uint8_t reg) {
	uint8_t data[2];
	short out;
	read(&reg, 1, data, 2);
	if (endianness == I2C_MSB_FIRST) {
		out = ((unsigned short)((unsigned short)data[1] + ((unsigned short)data[0] << 8)));
	} else {
		out = ((unsigned short)((unsigned short)data[0] + ((unsigned short)data[1] << 8)));
	}
	return out;
}

void i2cDevice::setWait(int wait) {
	usec = wait;
}

