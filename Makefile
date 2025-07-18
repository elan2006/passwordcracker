CXX = g++
CXFLAGS = -Wall --std=c++17 -lbcrypt
target = passwordcracker

all:
	 $(CXX) $(CXFLAGS) passwordcracker.cpp -o $(target)
