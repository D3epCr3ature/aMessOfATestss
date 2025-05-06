#ifndef __POSITION_H__
#define __POSITION_H__

#include "json.hpp"

struct Position {
    double x;
    double y;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Position, x, y)
};

#endif // __POSITION_H__
