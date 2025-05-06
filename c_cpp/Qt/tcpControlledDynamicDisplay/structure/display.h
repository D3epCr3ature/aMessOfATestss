#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "json.hpp"
#include "led.h"
#include <vector>
#include <string>

struct Display {
    std::vector<LED> leds;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Display, leds)
};

bool saveDisplay(const Display& display, const std::string& path);

#endif // __DISPLAY_H__
