#ifndef bmp085_h
#define bmp085_h

#include <cmath>
#include "i2cDevice.h"

#define BMP085_ADDRESS 0xEE

class bmp085 : private i2cDevice {
public:
	bmp085();
	
	float getTemperature();
	float getPressure();
	float getAltitude(float basePressure);

private:
	short AC1, AC2, AC3, B1, B2, MB, MC, MD;
	unsigned short AC4, AC5, AC6;

};
#endif
