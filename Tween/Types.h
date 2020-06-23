#pragma once
#ifndef HT_TWEEN_TYPES_H
#define HT_TWEEN_TYPES_H

#if defined(ARDUINO_ARCH_AVR)\
 || defined(ARDUINO_ARCH_MEGAAVR)\
 || defined(ARDUINO_ARCH_SAMD)\
 || defined(ARDUINO_spresense_ast)
    #define HT_TWEEN_STL_DISABLED
#endif

#include <Arduino.h>
#ifdef HT_TWEEN_STL_DISABLED
    #include "Tween/util/TeensyDirtySTLErrorSolution/TeensyDirtySTLErrorSolution.h"
    #include "Tween/util/ArxTypeTraits/ArxTypeTraits.h"
    #include "Tween/util/ArxContainer/ArxContainer.h"
    #include "Tween/util/ArxSmartPtr/ArxSmartPtr.h"
#else
    #include <vector>
    #include <map>
    #include <memory>
#endif

namespace ht {
namespace tween {

#ifdef HT_TWEEN_STL_DISABLED
    template <typename T, typename U> using Map = arx::map<T, U>;
    template <typename T> using Vec = arx::vector<T>;
    template <typename T> using Ref = arx::shared_ptr<T>;
    using namespace arx;
#else
    template <typename T, typename U> using Map = std::map<T, U>;
    template <typename T> using Vec = std::vector<T>;
    template <typename T> using Ref = std::shared_ptr<T>;
    using namespace std;
#endif // HT_TWEEN_STL_DISABLED

} // tween
} // ht


#endif // HT_TWEEN_TYPES_H
