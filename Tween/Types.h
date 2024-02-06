#pragma once
#ifndef HT_TWEEN_TYPES_H
#define HT_TWEEN_TYPES_H

#ifdef ARDUINO
#include <Arduino.h>
#include "Tween/util/TeensyDirtySTLErrorSolution/TeensyDirtySTLErrorSolution.h"
#elif defined(OF_VERSION_MAJOR)
#include "ofMain.h"
#endif
#include <ArxTypeTraits.h>
#include <ArxSmartPtr.h>
#include <ArxContainer.h>

namespace ht {
namespace tween {

    enum class Mode : uint8_t {
        ONCE,       // do once and stop after finished
        REPEAT_TL,  // repeat whole timeline after finished
        REPEAT_SQ,  // repeat each sequence after finished
    };

    struct Setting {
        Mode mode {Mode::ONCE};
        double duration {0};
    };

#if ARX_HAVE_LIBSTDCPLUSPLUS >= 201103L  // Have libstdc++11
    template <typename T, typename U>
    using Map = std::map<T, U>;
    template <typename T>
    using Vec = std::vector<T>;
    template <typename T>
    using Ref = std::shared_ptr<T>;
#else
    template <typename T, typename U>
    using Map = arx::stdx::map<T, U>;
    template <typename T>
    using Vec = arx::stdx::vector<T>;
    template <typename T>
    using Ref = std::shared_ptr<T>;
#endif

}  // namespace tween
}  // namespace ht

#endif  // HT_TWEEN_TYPES_H
