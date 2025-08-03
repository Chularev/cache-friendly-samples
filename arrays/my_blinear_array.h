#ifndef MY_BLINEAR_ARRAY_H
#define MY_BLINEAR_ARRAY_H

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


class my_blinear_array
{
public:
    my_blinear_array() = default;
    virtual ~my_blinear_array()
    {
        while (shoot_first());
    }

    std::vector<struct timer_data> timeouts;
    uint32_t next_id = 0;
    uint32_t prev{};

    static bool is_after(const timer_data& lh, const timer_data& rh)
    {
        return lh.deadline >= rh.deadline;
    }

    uint32_t schedule_timer(uint32_t deadline, timer_cb cb, void* userp) {
        timer_data element{deadline, next_id++, userp, cb};
        auto it = std::lower_bound(timeouts.begin(), timeouts.end(),
                                   element, is_after);
        // Insert new element
        timeouts.insert(it, std::move(element));
        return next_id;
    }

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

    void loop (uint32_t id, int i)
    {
        uint32_t t = schedule_timer(id, [](void*){return 0U;}, nullptr);
        if (i & 1) cancel_timer(prev);
        prev = t;
    }

};
bool operator==(const timer_data& a1, const timer_data& a2)
{
    return a1.deadline == a2.deadline && a1.id == a2.id;
}
#endif // MY_BLINEAR_ARRAY_H
