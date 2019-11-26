CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla
EXEC = computeExpression
OBJECTS = main.o expression.o derived.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

