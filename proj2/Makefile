#
# Makefile for Binary Search Tree
#
# Homework 4 (fall 2018)
#
# Not using -Wextra

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra -O2
LDFLAGS  = -g3

gerp: gerp.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -o gerp gerp.o FSTree.o DirNode.o

gerp.o:              gerp.cpp FSTree.h DirNode.h

clean:
	rm -rf gerp *.o *.dSYM
