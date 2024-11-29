#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <iostream>

class Ship {
public:
    enum class Orientation { Horizontal, Vertical };
    enum class SegmentState { Intact, Damaged, Destroyed };

    Ship(int length = 1, Orientation orientation = Orientation::Horizontal);

    void takeDamage(int segmentIndex, int damage = 1);
    bool isSunk() const;
    int getLength() const;
    Orientation getOrientation() const;
    SegmentState getSegmentState(int segmentIndex) const;

    friend std::ostream& operator<<(std::ostream& os, const Ship& ship);
    friend std::istream& operator>>(std::istream& is, Ship& ship);

private:
    int length_;
    Orientation orientation_;
    std::vector<SegmentState> segments_;
};

#endif 
