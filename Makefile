CXX = g++
CXXFLAGS = -std=c++20 -Wall  -g -fsanitize=address
SERVER_EXEC = raiinet
CLIENT_EXEC = client
SERVER_SRC = basetile.cc board.cc decorator.cc firewall.cc gamecontroller.cc illegalabilityuseexception.cc illegalmoveexception.cc link.cc player.cc server.cc serverinitexception.cc serverport.cc subject.cc superfirewall.cc textDisp.cc tile.cc main.cc networking.cc
SERVER_OBJECTS = ${SERVER_SRC:.cc=.o}
CLIENT_SRC = client.cc clientinitexception.cc client_main.cc networking.cc
CLIENT_OBJECTS = ${CLIENT_SRC:.cc=.o}

.PHONY: clean

all: ${SERVER_EXEC} ${CLIENT_EXEC}

${SERVER_EXEC}: ${SERVER_OBJECTS}
	${CXX} ${CXXFLAGS} ${SERVER_OBJECTS} -o ${SERVER_EXEC}

${CLIENT_EXEC}: ${CLIENT_OBJECTS}
	${CXX} ${CXXFLAGS} ${CLIENT_OBJECTS} -o ${CLIENT_EXEC}

%.o: %.cc
	${CXX} ${CXXFLAGS} -c $<

.PHONY: clean

clean:
	rm -f ${SERVER_OBJECTS} ${CLIENT_OBJECTS} ${SERVER_EXEC} ${CLIENT_OBJECTS}
