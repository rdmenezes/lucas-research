#ifndef DataRef_h
#define DataRef_h

#include <stdio.h>
#include "XPLMDataAccess.h"

class DataRef {
public:
	DataRef(const char * path);

	void setMultiplier(double m);
	void setBias(double b);

	float getFloat();
	float getFloat(int index);
	bool setFloat(float val);
	bool setFloat(int index, float val);
	double getDouble();
	bool setDouble(double val);
	int getInt();
	int getInt(int index);
	bool setInt(int val);
	bool setInt(int index, int val);
private:
	XPLMDataRef ref;
	bool write;
	double m, b;
};

#endif