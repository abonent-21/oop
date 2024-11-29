#include "Ship.h"

Ship::Ship(int length, Orientation orientation)
    : length_(length), orientation_(orientation), segments_(length, SegmentState::Intact) {}

void Ship::takeDamage(int segmentIndex, int damage) {
    if (segmentIndex >= 0 && segmentIndex < length_) {
        SegmentState& segment = segments_[segmentIndex];
        if (segment == SegmentState::Intact) {
            if (damage >= 2) {
                segment = SegmentState::Destroyed;
            } else {
                segment = SegmentState::Damaged;
            }
        } else if (segment == SegmentState::Damaged) {
            segment = SegmentState::Destroyed;
        }
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

std::ostream& operator<<(std::ostream& os, const Ship& ship) {
    os << ship.length_ << ' ' << static_cast<int>(ship.orientation_) << std::endl;
    for (const auto& segment : ship.segments_) {
        os << static_cast<int>(segment) << ' ';
    }
    os << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Ship& ship) {
    int orientationInt;
    is >> ship.length_ >> orientationInt;
    ship.orientation_ = static_cast<Ship::Orientation>(orientationInt);
    ship.segments_.resize(ship.length_);
    int segmentStateInt;
    for (int i = 0; i < ship.length_; ++i) {
        is >> segmentStateInt;
        ship.segments_[i] = static_cast<Ship::SegmentState>(segmentStateInt);
    }
    return is;
}
