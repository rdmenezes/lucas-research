where-am-i = $(dir $(CURDIR)/$(lastword $(MAKEFILE_LIST)))

libraries = Joystick Thread
include_dirs := $(addprefix -I$(where-am-i), $(libraries))
CPPFLAGS += $(include_dirs)


vpath %.h $(addprefix $(where-am-i), $(libraries))
vpath %.o $(addprefix $(where-am-i), $(libraries))


