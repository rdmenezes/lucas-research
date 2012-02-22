#ifndef DataRef_h
#define DataRef_h


#define MAXIMUM_DATAREFS 20

#include <stdio.h>
#include "XPLMDataAccess.h"

class DataRef {
public:
	DataRef(const char * path);
	DataRef(const char * path, int min, int max);

	void setMultiplier(double m);
	void setBias(double b);

	float getFloat();
	float getFloat(int index);
	bool setFloat(float val);
	bool setFloat(int index, float val);
	double getDouble();
	double getDouble(int index);
	bool setDouble(double val);
	bool setDouble(int index, double val);
	int getInt();
	int getInt(int index);
	bool setInt(int val);
	bool setInt(int index, int val);
private:
	XPLMDataRef ref;
	XPLMDataRef refs[MAXIMUM_DATAREFS];
	int min;
	int length;

	bool write;
	double m, b;
};

#endif