CC = g++
CXX = g++

ifeq "$(BUILD_TYPE)" "virtualbox"
   CC = i486-openwrt-linux-uclibc-g++
   CXX = i486-openwrt-linux-uclibc-g++
   export STAGING_DIR = ${STAGING_I386}
endif
ifeq "$(BUILD_TYPE)" "embedded"
   CC = mipsel-openwrt-linux-uclibc-g++
   CXX = mipsel-openwrt-linux-uclibc-g++
   export STAGING_DIR = ${STAGING_MIPSEL}
endif

export CC CXX

vpath %.h ../i2cDevice
vpath %.o ../i2cDevice

CXXFLAGS += -I ../i2cDevice


SOURCES = bmp085

bmp085: bmp085.cpp i2cDevice.o i2cDevice.h

.PHONY: clean
clean: 
	rm -f *.o *.d $(SOURCES)

