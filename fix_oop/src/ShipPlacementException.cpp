#include "ShipPlacementException.h"

ShipPlacementException::ShipPlacementException()
    : GameException("Unable to place a ship: overlapping or adjacent to another ship.") {}
