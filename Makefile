DIST := bin
SUFFIX := _minified
PROGRAM := $(DIST)/2048

all: run

run: build
	./$(PROGRAM)

build: $(DIST) $(PROGRAM)

$(PROGRAM): 2048$(SUFFIX).c
	gcc $^ -lncurses -o $@

$(DIST):
	@mkdir $@

clean:
	@rm -rf $(DIST)

.PHONY: all run build clean
