#include "bmp085.h"

bmp085::bmp085() : i2cDevice(0, BMP085_ADDRESS) {
	AC1 = getShort(0xAA);
	AC2 = getShort(0xAC);
	AC3 = getShort(0xAE);
	AC4 = getUnsignedShort(0xB0);
	AC5 = getUnsignedShort(0xB2);
	AC6 = getUnsignedShort(0xB4);
	B1 = getShort(0xB6);
	B2 = getShort(0xB8);
	MB = getShort(0xBA);
	MC = getShort(0xBC);
	MD = getShort(0xBE);
}

float bmp085::getTemperature() {
	long X1, X2, B5, UT, T;
	writeReg(0xF4, 0x2E);
	usleep(4500);
	UT = (long)getShort(0xF6);

	X1 = (UT - AC6) * AC5 / 32768;
	X2 = MC * 2048 / (X1 + MD);
	B5 = X1 + X2;
	T = (B5 + 8) / 16;

	return (float)T/10.0 + 273.15;
}

float bmp085::getPressure() {
	long X1, X2, X3, B5, T, B6, B3, UT, UP, p;
	unsigned long B4, B7;

	writeReg(0xF4, 0x2E);
	usleep(4500);
	UT = (long)getShort(0xF6);

	X1 = (UT - AC6) * AC5 / 32768;
	X2 = MC * 2048 / (X1 + MD);
	B5 = X1 + X2;

	writeReg(0xF4, 0x34);
	usleep(4500);

	uint8_t reg = 0xF6;
	uint8_t data_out[3];
	

	read(&reg, 1, data_out, 3);

	UP = ((long)((long)data_out[2] + ((long)data_out[1] << 8) + ((long)data_out[0] << 16))) >> 8;

	B6 = B5 - 4000;
	X1 = (B2*(B6*B6/4096))/2048;
	X2 = AC2 * B6 / 2048;
	X3 = X1 + X2;
	B3 = ((AC1*4+X3) + 2)/4;
	X1 = AC3 * B6 / 8192;
	X2 = (B1 * (B6*B6/4096)) / 65536;
	X3 = ((X1 + X2) + 2) / 4;
	B4 = AC4 * (unsigned long)(X3 + 32768) / 32768;
	B7 = ((unsigned long)UP - B3) * (50000);
	if (B7 < 0x80000000) {
		p = (B7 * 2) / B4;
	} else {
		p = (B7 / B4) * 2;
	}
	X1 = (p / 256) * (p / 256);
	X1 = (X1 * 3038)/ 65536;
	X2 = (-7357 * p) / 65536;
	p = p + (X1 + X2 + 3791) / 16;

	return (float)p;
}

float bmp085::getAltitude(float basePressure) {
	//Barometric formula from Wikipedia...

	float R = 8.31432;
	float g = 9.80665;
	float M = 0.0289644;

	float alt = getTemperature() * R / g / M * log(basePressure/getPressure());

	return alt;

}


int main(int argc, char *argv[]) {
	bmp085 *myBaro = new bmp085();
	
	if (argc == 2) {
		float altSetting;
		sscanf(argv[1], "%f", &altSetting);
		printf("%.2fm\n", myBaro->getAltitude(altSetting));
	} else {
		printf("%.1fK\t%.0fPa\n", myBaro->getTemperature(), myBaro->getPressure());
	}



}









//#include <sys/stat.h>
//#include <signal.h>

/*bool forever = true;
void my_handler(int s){
           forever = false;
}

int main(int argc, char *argv[]) {
	signal (SIGINT,my_handler);
	signal (SIGTERM,my_handler);

	if (argc > 1) {
		//check for options if this matters in the future
/*	} else {
		int pid = fork();
		if (pid < 0) {
			printf("BMP085 fork failed!\n");
			exit(1);
		}
		if (pid > 0) {
			printf("BMP085 forking to %d\n", pid);
			exit(0);
		}
		umask(0);
		int sid = setsid();
		if (sid < 0) {
			exit(1);
		}
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		//Daemon should now be forked
	}
	mkdir("/tmp/bmp085", 0666);
	if (mkfifo("/tmp/bmp085/pressure", 0666) == 0) {
		printf("/tmp/bmp085/pressure created\n");
	} else {
		perror("/tmp/bmp085/pressure");
	}

	if (mkfifo("/tmp/bmp085/temperature", 0666) == 0) {
		printf("/tmp/bmp085/temperature created\n");
	} else {
		perror("/tmp/bmp085/temperature");
	}
	

	if (mkfifo("/tmp/bmp085/altitude", 0666) == 0) {
		printf("/tmp/bmp085/altitude created\n");
	} else {
		perror("/tmp/bmp085/altitude");
	}
	

	if (mkfifo("/tmp/bmp085/pressure_setting", 0666) == 0) {
		printf("/tmp/bmp085/pressure_setting created\n");
	} else {
		perror("/tmp/bmp085/pressure_setting");
	}

	
	
	int presFile = open("/tmp/bmp085/pressure", O_WRONLY | O_NONBLOCK);
	int tempFile = open("/tmp/bmp085/temperature", O_WRONLY | O_NONBLOCK);
	int altFile = open("/tmp/bmp085/altitude", O_WRONLY | O_NONBLOCK);
	int presSetFile = open("/tmp/bmp085/pressure_setting", O_RDWR | O_NONBLOCK);
	
	bmp085 *myBaro = new bmp085();

	float presSet = 101315.0f;
	char str[64];

//	fprintf(presSetFile, "%.0f\n", presSet);

	while (forever) {
		sprintf(str, "%.0f\n", myBaro->getPressure());
		write(presFile, str, 64);
		sprintf(str, "%.2f\n", myBaro->getTemperature());
		write(tempFile, str, 64);
//		fscanf(presSetFile, "%f", &presSet);
		sprintf(str, "%.2f\n", myBaro->getAltitude(presSet));
		write(altFile, str, 64);
		usleep(100000);
	}

	close(presFile);
	close(tempFile);
	close(altFile);
	close(presSetFile);

/*	unlink("/tmp/bmp085/pressure");
	unlink("/tmp/bmp085/temperature");
	unlink("/tmp/bmp085/altitude");
	unlink("/tmp/bmp085/pressure_setting");*/
//	rmdir("/tmp/bmp085");

//}

