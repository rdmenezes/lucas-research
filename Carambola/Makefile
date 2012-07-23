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

include ../libraries/libraries.mk

SOURCES = main

.PHONY: all
all:
	$(MAKE) -C ../libraries
	$(MAKE) $(SOURCES)

$(SOURCES): LDFLAGS+= -lpthread
$(SOURCES): main.o Joystick.o Thread.o

%.d: %.cpp
	@echo "--- Automatically generating dependancies for $(SOURCES) library ---"
	@$(CXX) -M $(CPPFLAGS) $< > $@.$$$$;			\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;	\
	rm -f $@.$$$$

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "clean_all"
ifneq "$(MAKECMDGOALS)" "clean_libs"
   -include $(addsuffix .d,$(SOURCES))
endif
endif
endif

.PHONY: clean
clean: 
	rm -f *.o *.d $(SOURCES)

.PHONY: clean_libs
clean_libs:
	$(MAKE) -C ../libraries clean

.PHONY: clean_all
clean_all: clean clean_libs

