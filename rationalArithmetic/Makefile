CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -MMD
EXEC = rationalArithmetic
OBJECTS = arithmetic.o rational.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

