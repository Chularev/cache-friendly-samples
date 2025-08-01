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
    virtual ~common_array()
    {
        while (shoot_first());
    }

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
    }

};
#endif // COMMON_H
