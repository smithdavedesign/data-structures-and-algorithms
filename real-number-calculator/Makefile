# make        build ./real-number-calculator
# make clean  remove it
CXX ?= c++
CXXFLAGS ?= -std=c++17 -O2 -Wall
SRCS := smithH6.cpp Real.cpp

real-number-calculator: $(SRCS) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

# make test   check + - * / < == against Python's exact Decimal on 3 x 3000 random cases
test: tests/fuzz_driver
	@for seed in 1 2 3; do python3 tests/fuzz.py $$seed '+-*/<=' 3000 tests/fuzz_driver || exit 1; done

tests/fuzz_driver: tests/fuzz_driver.cpp Real.cpp Real.h
	$(CXX) $(CXXFLAGS) -o $@ tests/fuzz_driver.cpp Real.cpp

clean:
	rm -f real-number-calculator tests/fuzz_driver

.PHONY: clean test
