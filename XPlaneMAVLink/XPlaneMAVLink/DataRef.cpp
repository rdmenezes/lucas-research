#include "DataRef.h"

DataRef::DataRef(const char * path) {
	ref = XPLMFindDataRef(path);
	if (ref == NULL) {
		fprintf(stderr, "DataRef '%s' Not Found!\n", path);
	}
	if (XPLMCanWriteDataRef(ref)) {
		write = true;
	} else {
		write = false;
	}
	m = 1.0;
	b = 0;
}

void DataRef::setMultiplier(double m) {
	this->m = m;
}

void DataRef::setBias(double b) {
	this->b = b;
}


float DataRef::getFloat() {
	return b + m*XPLMGetDataf(ref);
}
float DataRef::getFloat(int index) {
	float ret = 0.0;
	XPLMGetDatavf(ref,&ret,index,1);
	return b + m*ret;
}
bool DataRef::setFloat(float val) {
	XPLMSetDataf(ref,(val-b)/m);
	return true;
}
bool DataRef::setFloat(int index, float val) {
	val = (val-b)/m;
	XPLMSetDatavf(ref,&val,index,1);
	return true;
}

double DataRef::getDouble() {
	return b + m*XPLMGetDataf(ref);
}
bool DataRef::setDouble(double val) {
	XPLMSetDatad(ref,(val-b)/m);
	return true;
}

int DataRef::getInt() {
	return (int)(b + m*XPLMGetDatai(ref));
}
int DataRef::getInt(int index) {
	int ret = 0.0;
	XPLMGetDatavi(ref,&ret,index,1);
	return (int)(b + m*ret);
}
bool DataRef::setInt(int val) {
	XPLMSetDatai(ref,(val-b)/m);
	return true;
}
bool DataRef::setInt(int index, int val) {
	val = (val - b)/m;
	XPLMSetDatavi(ref,&val,index,1);
	return true;
}