
#include "display.h"

#include "json.hpp"
#include <fstream>
#include <string>

bool saveDisplay(const Display& display, const std::string& path) {
    nlohmann::json jsonDisplay = display;
    std::ofstream file(path);

    if ( ! (file && file.is_open()) ) {
        file.close();
        return false;
    }

    file << std::setw(4) << jsonDisplay << std::endl;
    file.close();
    return true;
}
