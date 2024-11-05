#include "Ship.h"

Ship::Ship(int length, Orientation orientation)
    : length_(length), orientation_(orientation), segments_(length, SegmentState::Intact) {}

void Ship::takeDamage(int segmentIndex) {
    if (segmentIndex >= 0 && segmentIndex < length_) {
        if (segments_[segmentIndex] == SegmentState::Intact) {
            segments_[segmentIndex] = SegmentState::Damaged;
        } else if (segments_[segmentIndex] == SegmentState::Damaged) {
            segments_[segmentIndex] = SegmentState::Destroyed;
        }
        // Если сегмент уже уничтожен, ничего не делаем
    }
}

bool Ship::isSunk() const {
    for (const auto& segment : segments_) {
        if (segment != SegmentState::Destroyed) {
            return false;
        }
    }
    return true;
}

int Ship::getLength() const {
    return length_;
}

Ship::Orientation Ship::getOrientation() const {
    return orientation_;
}

Ship::SegmentState Ship::getSegmentState(int segmentIndex) const {
    if (segmentIndex >= 0 && segmentIndex < length_) {
        return segments_[segmentIndex];
    }
    return SegmentState::Destroyed;
}
