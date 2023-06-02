CXX = g++
CXXFLAGS = -Wall -pedantic

TARGET = game
SOURCES = Main.cpp Game.cpp AntHill.cpp board.cpp BonusEffect.cpp bot.cpp obstacles.cpp Position.cpp Ant.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)


BonusEffect.o: BonusEffect.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

AntHill.o: AntHill.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
board.o: board.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bot.o: bot.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obstacles.o: obstacles.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Position.o: Position.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Game.o: Game.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Main.o: Main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Ant.o: Ant.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

clear:
	rm *.o
	