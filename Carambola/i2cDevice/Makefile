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

SOURCES = i2cDevice

i2cDevice.o: i2cDevice.cpp

.PHONY: clean
clean: 
	rm -f *.o *.d $(SOURCES)

