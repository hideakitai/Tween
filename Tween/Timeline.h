
#ifndef TWEEN_DUINO_TIMELINE_H
#define TWEEN_DUINO_TIMELINE_H

#include "Types.h"
#include "Sequence.h"
#include "util/PollingTimer/PollingTimer.h"

namespace ht {
namespace tween {

class Timeline : public PollingTimer
{
    Map<void*, SequenceRef> seqs;

public:

    template <typename EasingType = Ease::Linear, typename T, typename U>
    auto add(T& target, const U& to, const int32_t in)
    -> typename std::enable_if<std::is_convertible<U, T>::value, Sequence<T>&>::type
    {
        auto p = make_shared<Sequence<T>>(target, to, in, EasingType());
        seqs.insert(make_pair((void*)&target, (SequenceRef)p));
        return *p;
    }

    void update()
    {
        if (!isRunning()) return;
        for (auto& s : seqs)
            s.second->update(msec());
    }

    void clear()
    {
        seqs.clear();
        PollingTimer::stop();
    }
};

} // tween
} // ht

#endif