# Компилятор
CXX = g++

# Флаги компилятора
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Цель (имя исполняемого файла)
TARGET = game

# Каталоги
SRC_DIR = src
HEADER_DIR = include
OBJ_DIR = obj

# Исходные файлы
SRCS = $(SRC_DIR)/GameField.cpp $(SRC_DIR)/Ship.cpp $(SRC_DIR)/ShipManager.cpp $(SRC_DIR)/main.cpp

# Объектные файлы (.o)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Включаем заголовочные файлы
INCLUDES = -I$(HEADER_DIR)

# Цель по умолчанию
all: $(TARGET)

# Линковка объектных файлов для создания исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Правило для компиляции .cpp файлов в .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Создание каталога для объектных файлов, если его нет
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Очистка объектных файлов и исполняемого файла
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Псевдонимы для целей
.PHONY: all clean
