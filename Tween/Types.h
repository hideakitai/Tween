#pragma once
#ifndef HT_TWEEN_TYPES_H
#define HT_TWEEN_TYPES_H

#ifdef ARDUINO
#include <Arduino.h>
#include "Tween/util/TeensyDirtySTLErrorSolution/TeensyDirtySTLErrorSolution.h"
#elif defined(OF_VERSION_MAJOR)
#include "ofMain.h"
#endif
#include "util/ArxTypeTraits/ArxTypeTraits.h"
#include "util/ArxSmartPtr/ArxSmartPtr.h"
#include "util/ArxContainer/ArxContainer.h"

namespace ht {
namespace tween {

    enum class Mode : uint8_t
    {
        ONCE, // do once and clear after finished
        LOOP, // loop current timeline after finished
        SAVE  // store current timeline with no loop
    };

    struct Setting
    {
        Mode mode {Mode::ONCE};
        uint32_t duration {0};
    };

#if ARX_HAVE_LIBSTDCPLUSPLUS >= 201103L // Have libstdc++11
    template <typename T, typename U> using Map = std::map<T, U>;
    template <typename T> using Vec = std::vector<T>;
    template <typename T> using Ref = std::shared_ptr<T>;
    using namespace std;
#else
    template <typename T, typename U> using Map = arx::map<T, U>;
    template <typename T> using Vec = arx::vector<T>;
    template <typename T> using Ref = std::shared_ptr<T>;
    using namespace arx;
#endif

} // tween
} // ht


#endif // HT_TWEEN_TYPES_H
