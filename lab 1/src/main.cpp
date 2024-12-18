#include "../include/lab.h"
#include <cstdint>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <string>

int period_to_hours(int hour, string period) {
    if (period == "pm"){
        hour += 12;
    }
    if (hour >= 24){
        hour -= 24;
    }
    return hour;
}

string time_reformat(int hour, int minute, string period) {
    hour = period_to_hours(hour, period);
    string result = to_string(hour) + to_string(minute);
    return result;
}