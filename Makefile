# Description: Project 1 (cold calling system)
#
# Author: Owen, Mason, James, Zach, Sam
#
# Date of last update: 2/3/2020
#
# Notes: Project currently under construction
# 			 Makefile based on the one provided for UO CIS 330 2019 Winter

CXX=g++
LIBS=-lncurses
CXXFLAGS=-Wall -W -g -std=c++11
DIRS=~/Documents/Invoke ~/Documents/Invoke/Rosters ~/Documents/Invoke/InvokeReports ~/Documents/Invoke/.invokeData

all: invoke directories

directories:
	$(shell mkdir -p $(DIRS))

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

invoke: Student.o ColdCallQueue.o ColdCallClass.o ColdCallClassList.o Reporting.cpp RosterIE.o statePersistence.o
	$(CXX) main.cpp $^ $(CXXFLAGS) $(LIBS) -o invoke

run:
	./invoke
clean:
	rm -f invoke *.o
