CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
LDFLAGS =
TARGET = battleship_game
OBJECTS = main.o GameBoard.o Ship.o ShipManager.o

# Главная цель
all: $(TARGET)

# Линковка
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Правила компиляции
main.o: main.cpp GameBoard.h Ship.h ShipManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

GameBoard.o: GameBoard.cpp GameBoard.h Ship.h ShipManager.h
	$(CXX) $(CXXFLAGS) -c GameBoard.cpp -o GameBoard.o

Ship.o: Ship.cpp Ship.h
	$(CXX) $(CXXFLAGS) -c Ship.cpp -o Ship.o

ShipManager.o: ShipManager.cpp ShipManager.h Ship.h
	$(CXX) $(CXXFLAGS) -c ShipManager.cpp -o ShipManager.o

# Очистка
clean:
	rm -f $(TARGET) $(OBJECTS)
