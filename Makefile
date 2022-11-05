CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
EXEC = straights
OBJECTS = card.o controller.o main.o model.o player.o straightsModel.o textView.o textController.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
