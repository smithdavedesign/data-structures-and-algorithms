# make        build ./real-number-calculator
# make clean  remove it
CXX ?= c++
CXXFLAGS ?= -std=c++17 -O2 -Wall
SRCS := smithH6.cpp Real.cpp

real-number-calculator: $(SRCS) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	rm -f real-number-calculator

.PHONY: clean
