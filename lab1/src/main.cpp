#include "../include/lab.h"
#include <cstdint>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <string>

int period_to_hours(int hour, std::string period) {
    if (period == "pm"){
        hour += 12;
    }
    if (hour >= 24){
        hour -= 24;
    }
    return hour;
}

std::string time_reformat(int hour, int minute, std::string period) {
    hour = period_to_hours(hour, period);
    std::string result = std::to_string(hour) + std::to_string(minute);
    return result;
}