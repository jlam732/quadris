CXX = g++
CXXFLAGS = -Wall -MMD -g -L/usr/X11R6/lib
EXEC = quadris
OBJECTS = main.o cell.o block.o gameBoard.o iBlock.o oBlock.o jBlock.o sBlock.o lBlock.o tBlock.o zBlock.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

