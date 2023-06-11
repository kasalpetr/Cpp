CXX = g++
CXXFLAGS = -Wall -pedantic

TARGET = kasalpe2
SOURCES = src/Main.cpp src/Game.cpp src/AntHill.cpp src/Board.cpp src/BonusEffect.cpp src/Bot.cpp src/obstacles.cpp src/Position.cpp src/Ant.cpp
OBJECTS = $(SOURCES:.cpp=.o)

DOXYGEN = doxygen
DOXYGEN_CONFIG = Doxyfile

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

BonusEffect.o: src/BonusEffect.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

AntHill.o: src/AntHill.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
board.o: src/Board.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bot.o: src/Bot.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obstacles.o: src/obstacles.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Position.o: src/Position.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Game.o: src/Game.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Main.o: src/Main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Ant.o: src/Ant.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

compile: $(TARGET)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

clear:
	rm *.o

doc:
	$(DOXYGEN) $(DOXYGEN_CONFIG)
