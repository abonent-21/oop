#ifndef SHIP_H
#define SHIP_H

#include <vector>

enum class SegmentState {
    INTACT,      // Целый
    DAMAGED,     // Поврежденный
    DESTROYED    // Уничтоженный
};

class Ship {
public:
    Ship(int length, bool isHorizontal);

    // Получить длину корабля
    int getLength() const;

    // Проверить, горизонтально ли корабль
    bool isHorizontal() const;

    // Получить состояние сегмента по индексу
    SegmentState getSegmentState(int index) const;

    // Нанести удар по сегменту корабля
    void hitSegment(int index);

    // Проверить, уничтожен ли весь корабль
    bool isSunk() const;

private:
    int length;
    bool horizontal;
    std::vector<SegmentState> segments;
};

#endif
