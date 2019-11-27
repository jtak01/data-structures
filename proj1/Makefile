#
# Makefile for SeqMatch
#
# Projecct 1 (spring 2019)
#
# Not using -Wextra

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra
LDFLAGS  = -g3

SeqMatch: main.o Dna.o 
	${CXX} ${LDFLAGS} -o SeqMatch main.o Dna.o
unit-test: Dna.o unit-test.o
	${CXX} ${LDFLAGS} -o unit-test unit-test.o Dna.o

main.o:              main.cpp Dna.h
Dna.o:  Dna.cpp Dna.h
unit-test.o: 		 unit-test.cpp Dna.h

clean:
	rm -rf SeqMatch *.o *.dSYM

