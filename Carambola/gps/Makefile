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

vpath %.h ../../APMMAVLink/DataLink
vpath %.cpp ../../APMMAVLink/DataLink

CXXFLAGS += -I ../../APMMAVLink/DataLink


SOURCES = gps

gps: gps.cpp gps.h SerialDataLink.o SerialDataLink.h


SerialDataLink.o: SerialDataLink.cpp SerialDataLink.h


.PHONY: clean
clean: 
	rm -f *.o *.d $(SOURCES)


