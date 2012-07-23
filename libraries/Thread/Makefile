include ../libraries.mk

SOURCES = Thread


.PHONY: all clean
all: $(addsuffix .o,$(SOURCES))

# Rule to clean directory
clean:
	-rm -f *.o *.d

ifneq "$(MAKECMDGOALS)" "clean"
   -include $(addsuffix .d,$(SOURCES))
endif


%.d: %.cpp
	@echo "--- Automatically generating dependancies for $(SOURCES) library ---"
	@$(CXX) -M $(CPPFLAGS) $< > $@.$$$$;			\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;	\
	rm -f $@.$$$$

