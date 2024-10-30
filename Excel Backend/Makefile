CXX = clang++
CXXFLAGS = -Wall -pedantic -std=c++2a
LIBS = -L./x86_64-darwin23-clang -lexpression_parser
TARGET = test
VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

all: $(TARGET)

$(TARGET): test.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

run: $(TARGET)
	./$(TARGET)

.: $(TARGET)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(TARGET)

clean:
	rm -f $(TARGET)