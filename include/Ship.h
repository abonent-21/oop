#ifndef SHIP_H
#define SHIP_H

#include <vector>


class Ship{
    public:
        enum class Orientation{
            Horizontal,
            Vertical
        };

        enum class SegmentState{
            Intact,
            Damaged,
            Destroyed
        };

        Ship(int length, Orientation orientation);
        

        // Разрешение на перемещение
        Ship(Ship&&) noexcept = default;
        Ship& operator=(Ship&&) noexcept = default;

        void HitSegment(int idx_of_segment); 
        bool isSunk() const;
        int getLength() const;
        Orientation getOrientation() const;
        SegmentState getSegmentState(int segmentIndex) const;


    private:
        int length_;
        Orientation orientation_;
        std::vector<SegmentState> segments_;

};

#endif