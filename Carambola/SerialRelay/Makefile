
#Default compiler
CC = g++
CXX = g++

#OpenWRT Virtual Box Compiler - call make with BUILD_TYPE=virtualbox
ifeq "$(BUILD_TYPE)" "virtualbox"
   CC = i486-openwrt-linux-uclibc-g++
   CXX = i486-openwrt-linux-uclibc-g++
   export STAGING_DIR = ${STAGING_I386}
endif

#OpenWRT Carambola Compiler - call make with BUILD_TYPE=embedded
ifeq "$(BUILD_TYPE)" "embedded"
   CC = mipsel-openwrt-linux-uclibc-g++
   CXX = mipsel-openwrt-linux-uclibc-g++
   export STAGING_DIR = ${STAGING_MIPSEL}
endif

#export variables (incase other makefiles are called)
export CC CXX

#include paths to old structure
vpath %.h ../../APMMAVLink/DataLink
vpath %.cpp ../../APMMAVLink/DataLink
CXXFLAGS += -I ../../APMMAVLink/DataLink -I ../../include


SOURCES = SerialRelay

SerialRelay: SerialRelay.cpp SerialRelay.h SerialDataLink.o SerialDataLink.h MAVLink.o MAVLink.h


SerialDataLink.o: SerialDataLink.cpp SerialDataLink.h DataLink.h

MAVLink.o: MAVLink.cpp MAVLink.h


.PHONY: clean
clean: 
	rm -f *.o *.d $(SOURCES)


