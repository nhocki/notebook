all: tex

view: all
	evince tex/biblioteca.pdf &

LIBRARY_DIRS = config geometry graph math string structures
ALL_DIRS = $(LIBRARY_DIRS) tex

.PHONY: $(ALL_DIRS) view

$(ALL_DIRS):
	$(MAKE) -C $@

tex: $(LIBRARY_DIRS)

clean:
	for dir in $(ALL_DIRS); do \
	  $(MAKE) -C $$dir clean; \
	done
