# Uncomment this line if you want to compile 2048_clean.c
# SUFFIX ?= _clean

DIST := bin
PROGRAM := $(DIST)/2048

all: $(DIST) $(PROGRAM)

$(PROGRAM): 2048$(SUFFIX).c
	gcc $^ -o $@

$(DIST):
	@mkdir $@

clean:
	@rm -rf $(DIST)

.PHONY: all clean
