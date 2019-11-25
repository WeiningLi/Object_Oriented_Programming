CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -MMD
EXEC = treeString
OBJECTS = treeStr.o tstring.o tnode.o utility.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

