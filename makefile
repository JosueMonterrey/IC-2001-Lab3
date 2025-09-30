EXECUTABLES := L30
CXX := g++

all: compile

compile:
	${CXX} -o L30 L30.cpp

clean:
	rm -f ${EXECUTABLES}