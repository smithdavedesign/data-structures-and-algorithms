# make        build ./large-number-calculator
# make clean  remove it
CXX ?= c++
CXXFLAGS ?= -std=c++17 -O2 -Wall
SRCS := main.cpp largeNum.cpp

large-number-calculator: $(SRCS) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	rm -f large-number-calculator

.PHONY: clean
