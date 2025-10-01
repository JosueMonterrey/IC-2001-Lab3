EXECUTABLES := L30 L31 L33
CXX := g++

all: compile

compile:
	${CXX} -o L30 L30.cpp
	${CXX} -o L31 L31.cpp
	${CXX} -o L33 L33.cpp

clean:
	rm -f ${EXECUTABLES}