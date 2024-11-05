#include "Ship.h" 
#include <iostream> 
 
Ship::Ship(int length, bool isHorizontal)
    : length(length), horizontal(isHorizontal), segments(length, SegmentState::INTACT) {}

 
int Ship::getLength() const { 
    return length; 
} 
 
SegmentState Ship::getSegmentState(int index) const { 
    if (index < 0 || index >= length) { 
        throw std::out_of_range("Индекс сегмента вне диапазона"); 
    } 
    return segments[index]; 
} 
 
void Ship::hitSegment(int index) { 
    if (index < 0 || index >= length) { 
        throw std::out_of_range("Индекс сегмента вне диапазона"); 
    } 
 
    if (segments[index] == SegmentState::INTACT) { 
        segments[index] = SegmentState::DAMAGED; 
        //std::cout << "Сегмент поврежден!" << std::endl; 
    } else if (segments[index] == SegmentState::DAMAGED) { 
        segments[index] = SegmentState::DESTROYED; 
        //std::cout << "Сегмент уничтожен!" << std::endl; 
    } 
} 
 
bool Ship::isSunk() const { 
    for (const auto& segment : segments) { 
        if (segment != SegmentState::DESTROYED) { 
            return false; 
        } 
    } 
    return true; 
}

bool Ship::isHorizontal() const {
    return horizontal;
}
