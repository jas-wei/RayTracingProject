#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

inline double getRandomDouble() {
    return std::rand()/ (RAND_MAX + 1.0);
}

inline double getRandomDouble(double min, double max) {
    return (max - min) * getRandomDouble() + min;
}


// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif