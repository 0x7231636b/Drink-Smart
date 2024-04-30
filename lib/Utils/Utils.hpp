#pragma once

#include <sstream>

namespace Utils {

struct Color {
    int red;
    int green;
    int blue;
};

Color black();
Color red();
Color green();
Color blue();
Color orange();

int64_t timeInMs();

template <class T>
inline std::string to_string(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

}
