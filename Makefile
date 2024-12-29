CXX = g++
CXXFLAGS = -std=c++20 -Wall  -g
EXEC = raiinet
SRC = $(wildcard *.cc)
OBJECTS = ${SRC:.cc=.o}

.PHONY: clean

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

%.o: %.cc
	${CXX} ${CXXFLAGS} -c $<

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC}
