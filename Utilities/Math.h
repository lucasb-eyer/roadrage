/**
 * \file Math.h
 * \author Pompei2
 * \date 2 February 2010
 * \brief This file contains some mathematical utility functions.
 **/

#pragma once

#include <algorithm>
#include <stdlib.h>
#include <cmath>

#define D_FTS_EPSILON      0.0001

namespace RoadRage {
    // angles
    static const float pi = 3.141592f;
    static const float rad2deg = 57.29577f;
    static const float deg2rad = 0.01745329f;

    // velocity
    static const float kmh2ms = 0.2777778f;
    static const float ms2kmh = 3.6f;
    static const float mph2ms = 0.44704f;
    static const float ms2mph = 2.236936f;

    // acceleration
    static const float kmhh2mss = kmh2ms / 3600.0f;
    static const float mss2kmhh = ms2kmh * 3600.0f;
    static const float kmhs2mss = kmh2ms;
    static const float mss2kmhs = ms2kmh;
    static const float mphh2mss = mph2ms / 3600.0f;
    static const float mss2mphh = ms2mph * 3600.0f;
    static const float mphs2mss = mph2ms;
    static const float mss2mphs = ms2mph;

/// Checks if a floating point value is nearly zero.
/// \param val The value to check if it is near zero.
/// \returns true if \a val is nearly zero.
inline bool nearZero(const float& val, const float& epsilon = D_FTS_EPSILON) {
    return ((val > 0.0f && val < epsilon)
         || (val < 0.0f && val > -epsilon)
         || (val == 0.0f));
}

template<class T>
inline T clamp(T& in_val, T in_min, T in_max) {
    return in_val = std::max(std::min(in_val, in_max), in_min);
}

template<class T>
inline T clamp(const T& in_val, T in_min, T in_max) {
    return std::max(std::min(in_val, in_max), in_min);
}

template<class T>
inline T lerp(T in_min, T in_max, float in_percent) {
    return in_min + (in_max - in_min) * in_percent;
}

/// Get a random number between two numbers.
/** Returns a random number between \a in_iMin and \a in_iMax.
 *
 * \param in_dMin The minimum numeric value of the number.
 * \param in_dMax The maximum numeric value of the number.
 *
 * \return An valid number between \a in_dMin and \a in_dMax.
 *
 * \note both values may be negative (and real) numbers, no problem.
 *
 * \author Pompei2
 */
template<typename T>
T random(T in_dMin, T in_dMax)
{
    double min = std::min(in_dMin, in_dMax);
    double max = std::max(in_dMin, in_dMax);

    // between 0 and 1.
    double dFact = ((double)rand() / (double)RAND_MAX);

    // between 0 and max-min (for example min=-5, max=10, this is between 0 and 15)
    long double posval = (max - min)*dFact;

    // now between min and max, following the example above: between 0-5=-5 and 15-5=10
    return static_cast<T>(posval + min);
}

/// Returns the next power of two value from \a in_i
/** Returns the next bigger power of two value from \a in_i
 *
 * \param in_i The value wich to get the bigger power of 2 from.
 *
 * \return a power of two.
 *
 * \Note If \a in_i is 6, this function returns 8, because 8 is the next power of two.\n
 *       If \a in_i is 17, this function returns 32, because 32 is the next power of two.
 *
 * \author Pompei2
 */
template<typename T>
T power_of_two(T in_i)
{
    T iValue = 1;

    while(iValue < in_i)
        iValue <<= 1;

    return iValue;
}

}
