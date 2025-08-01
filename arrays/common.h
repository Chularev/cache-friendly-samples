#ifndef COMMON_H
#define COMMON_H

#include <random>
#include <vector>
#include <algorithm>

typedef uint32_t (*timer_cb)(void*);
struct timer_data {
    uint32_t deadline;
    uint32_t id;
    void* userp;
    timer_cb callback;
};


class common_array
{
public:
    common_array() = default;

    std::vector<struct timer_data> timeouts;
    uint32_t next_id = 0;

    bool is_after(uint32_t lh, uint32_t rh)
    {
        return lh < rh;
    }

    virtual uint32_t schedule_timer(uint32_t deadline, timer_cb cb, void* userp) = 0;

    void cancel_timer(uint32_t t)
    {
        auto i = std::find_if(timeouts.begin(), timeouts.end(),
                              [t](const auto& e) { return e.id == t; });
        timeouts.erase(i);
    }

    bool shoot_first()
    {
        if (timeouts.empty()) return false;
        timeouts.front().callback(timeouts.front().userp);
        timeouts.erase(timeouts.begin());
        return true;
    }

    void loop ()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint32_t> dist;

        for (int k = 0; k < 10; ++k) {
            uint32_t prev{};
            for (int i = 0; i < 20'000; ++i) {
                uint32_t t = schedule_timer(dist(gen), [](void*){return 0U;}, nullptr);
                if (i & 1) cancel_timer(prev);
                prev = t;
            }
            while (shoot_first())
                ;
        }
    }

};
#endif // COMMON_H
