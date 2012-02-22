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
	this->length = 0;
	this->min = 0;
}

DataRef::DataRef(const char * path, int min, int max) {
	if (max - min > MAXIMUM_DATAREFS) {
		max = min + MAXIMUM_DATAREFS;
	}
	this->length = max - min;
	this->min = min;
	for (int i = 0; i<=(max-min); i++) {
		char p[256];
		sprintf(p,path,min+i);
		refs[i] = XPLMFindDataRef(p);
		if (XPLMCanWriteDataRef(refs[i])) {
			write = true;
		} else {
			write = false;
		}
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
	if (length > 0) {
		ret = XPLMGetDataf(refs[index]);
	} else {
		XPLMGetDatavf(ref,&ret,index,1);
	}
	return b + m*ret;
}
bool DataRef::setFloat(float val) {
	XPLMSetDataf(ref,(val-b)/m);
	return true;
}
bool DataRef::setFloat(int index, float val) {
	float v = (val-b)/m;
	if (length > 0) {
		XPLMSetDataf(refs[index],v);
	} else {
		XPLMSetDatavf(ref,&v,index,1);
	}
	return true;
}

double DataRef::getDouble() {
	return b + m*XPLMGetDatad(ref);
}
double DataRef::getDouble(int index) {
	float ret = 0.0;
	if (length > 0) {
		ret = XPLMGetDatad(refs[index]);
	} else {
		ret = XPLMGetDatad(ref);
	}
	return b + m*ret;
}
bool DataRef::setDouble(double val) {
	XPLMSetDatad(ref,(val-b)/m);
	return true;
}
bool DataRef::setDouble(int index, double val) {
	double v = (val-b)/m;
	if (length > 0) {
		XPLMSetDatad(refs[index],v);
	} else {
		XPLMSetDatad(ref, v);
	}
	return true;
}

int DataRef::getInt() {
	return (int)(b + m*XPLMGetDatai(ref));
}
int DataRef::getInt(int index) {
	int ret = 0.0;
	if (length > 0) {
		ret = XPLMGetDatai(refs[index]);
	} else {
		XPLMGetDatavi(ref,&ret,index,1);
	}
	return (int)(b + m*ret);
}
bool DataRef::setInt(int val) {
	XPLMSetDatai(ref,(val-b)/m);
	return true;
}
bool DataRef::setInt(int index, int val) {
	val = (val - b)/m;
	if (length > 0) {
		XPLMSetDatai(refs[index], val);
	} else {
		XPLMSetDatavi(ref,&val,index,1);
	}
	return true;
}