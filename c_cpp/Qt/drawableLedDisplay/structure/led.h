#ifndef __LED_H__
#define __LED_H__

#include "json.hpp"
#include "position.h"

struct LED {
    Position position;
    double radius;
    double angle;
    float pitch;
    std::string type;

    struct {
        unsigned char  r;
        unsigned char  g;
        unsigned char  b;
    } color;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LED, position,            \
                                   radius, angle, pitch, type)
};

#endif // __LED_H__
