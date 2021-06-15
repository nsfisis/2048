DIST := bin
SUFFIX := _minified
PROGRAM := $(DIST)/2048$(SUFFIX)

all: run

run: build
	./$(PROGRAM)

build: $(DIST) $(PROGRAM)

$(PROGRAM): 2048$(SUFFIX).c
	gcc $^ -lncurses -o $@

$(DIST):
	@mkdir $@

.PHONY: all run build
