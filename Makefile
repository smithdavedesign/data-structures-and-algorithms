# make        build every program (each lands in its own folder)
# make clean  remove the binaries
DIRS := linked-list maze vector-sort real-number-calculator large-number-calculator dfa-creator

all:
	@for d in $(DIRS); do $(MAKE) -s -C $$d || exit 1; done

clean:
	@for d in $(DIRS); do $(MAKE) -s -C $$d clean; done

.PHONY: all clean
