SUBDIRS = Joystick Thread

.PHONY: libraries clean clean_dirs $(SUBDIRS)

libraries: $(SUBDIRS)
clean: clean_dirs $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(CLEAN)

$(SUBDIRS_CLEAN):
	$(MAKE) -C $(filter-out _clean, $@) clean

clean_dirs:
	$(eval CLEAN=clean)
