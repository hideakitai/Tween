
#ifndef TWEEN_DUINO_TIMELINE_H
#define TWEEN_DUINO_TIMELINE_H

#include "Types.h"
#include "Sequence.h"
#include "util/PollingTimer/FrameRateCounter.h"

namespace ht {
namespace tween {

    class Timeline : public FrameRateCounter {
        Map<void*, SequenceRef> seqs;
        Setting setting;

    public:
        template <typename T>
        Sequence<T>& add(T& target, bool b_auto_erase = false) {
            if (seqs.find(&target) != seqs.end()) {
                return this->Timeline::operator[](target);
            } else {
                auto p = std::make_shared<Sequence<T>>(target);
                p->auto_erase(b_auto_erase);
                seqs.insert(make_pair((void*)&target, (SequenceRef)p));
                return *p;
            }
        }

        void start() {
            // update total duration of this timeline
            auto it = seqs.begin();
            while (it != seqs.end()) {
                if (setting.duration < it->second->duration_with_offset())
                    setting.duration = it->second->duration_with_offset();
                ++it;
            }
            this->FrameRateCounter::start();
        }

        bool update() {
            if (!isRunning()) return false;

            const double ms = msec();
            auto it = seqs.begin();
            while (it != seqs.end()) {
                if (it->second->update(ms)) {
                    ++it;
                } else {
                    switch (setting.mode) {
                        case Mode::REPEAT_SQ: {
                            if (it->second->auto_erase())
                                it = seqs.erase(it);
                            else {
                                it->second->repeat(true);
                                ++it;
                            }
                            break;
                        }
                        default: {
                            if (it->second->auto_erase())
                                it = seqs.erase(it);
                            else {
                                it->second->repeat(false);
                                ++it;
                            }
                            break;
                        }
                    }
                }
            }

            // check current time here to seek completely to the end of sequence
            if (ms > setting.duration) {
                switch (setting.mode) {
                    case Mode::REPEAT_TL: restart(); return true;
                    case Mode::REPEAT_SQ: return true;
                    default: stop(); return false;
                }
            } else {
                return true;
            }
        }

        void clear() {
            for (auto& s : seqs) s.second->update(s.second->duration_with_offset());
            seqs.clear();
            FrameRateCounter::stop();
        }

        void mode(const Mode m) { setting.mode = m; }
        Mode mode() const { return setting.mode; }

        size_t size() const { return seqs.size(); }

        template <typename T>
        const Sequence<T>& operator[](const T& t) {
            return *(Sequence<T>*)(seqs[(void*)&t].get());
        }
        template <typename T>
        Sequence<T>& operator[](T& t) {
            return *(Sequence<T>*)(seqs[(void*)&t].get());
        }
    };

}  // namespace tween
}  // namespace ht

#endif
