CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror
CXX      = g++

# These targets don't create any files:
.PHONY: clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

convert: main.o AST.o Number.o Operator.o
	${CXX} $(CXXFLAGS) -o $@ $+


main.o: main.cpp AST.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

AST.o: AST.cpp AST.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Number.o: Number.cpp Number.h AST.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Operator.o: Operator.cpp Operator.h AST.h
	${CXX} $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f convert main.o AST.o Number.o Operator.o
