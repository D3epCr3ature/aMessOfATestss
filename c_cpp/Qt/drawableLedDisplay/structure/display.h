#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "json.hpp"
#include "led.h"
#include <vector>
#include <string>

/* Can't simply name it Display, sa it conflicts with Qt's */
struct LEDDisplay {
    std::vector<LED> leds;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LEDDisplay, leds)
};

bool openDisplay(struct LEDDisplay &display);

bool saveDisplay(const LEDDisplay& display, const std::string& path);
bool saveDisplay(const LEDDisplay& display);

#endif // __DISPLAY_H__
