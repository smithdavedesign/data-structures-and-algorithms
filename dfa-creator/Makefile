# make        build ./dfa-creator
# make clean  remove it
CXX ?= c++
CXXFLAGS ?= -std=c++17 -O2 -Wall
SRCS := main.cpp DFA_Generator.cpp

dfa-creator: $(SRCS) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	rm -f dfa-creator

.PHONY: clean
