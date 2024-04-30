#include <chrono>

#include "Utils.hpp"

namespace Utils {

Color black() {
    return Color{ 0, 0, 0 };
}

Color red() {
    return Color{ 255, 0, 0 };
}

Color green() {
    return Color{ 0, 255, 0 };
}

Color blue() {
    return Color{ 0, 0, 255 };
}

Color orange() {
    return Color{ 255, 120, 0 };
}


int64_t timeInMs() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    int64_t duration = value.count();
    return duration;
}

}
