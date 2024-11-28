CXX = g++-14.2.0
CXXFLAGS = -std=c++20 -fmodules-ts -Wall  -g
EXEC = raiinet
SRC = $(wildcard *.cc)
OBJECTS = ${SRC:.cc=.o}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -lX11 -L/usr/X11/lib -I/usr/X11/include ${OBJECTS} -o ${EXEC}

%.o: %.cc
	${CXX} ${CXXFLAGS} -c $<

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC}
