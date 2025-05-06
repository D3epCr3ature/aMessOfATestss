#ifndef __LED_H__
#define __LED_H__

#include "json.hpp"
#include "position.h"

struct LED {
    int id;
    Position position;
    double radius;
    double angle;
    float pitch;
    std::string type;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LED, id, position,     \
                                   radius, angle, pitch, type)
};

#endif // __LED_H__
