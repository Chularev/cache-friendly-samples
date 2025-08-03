#ifndef MY_BLINEAR_ARRAY_H
#define MY_BLINEAR_ARRAY_H
#include "common.h"

class my_blinear_array : public common_array
{
public:
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


};

#endif // MY_BLINEAR_ARRAY_H
