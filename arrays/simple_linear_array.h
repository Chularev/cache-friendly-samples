#ifndef SIMPLE_LINEAR_ARRAY_H
#define SIMPLE_LINEAR_ARRAY_H

#include "common.h"

class simple_linear_array : public common_array
{
public:
    simple_linear_array() = default;

    uint32_t schedule_timer(uint32_t deadline, timer_cb cb, void* userp)
    {
        auto idx = timeouts.size();
        timeouts.push_back({});
        while (idx > 0 && is_after(timeouts[idx-1].deadline, deadline)) {
            timeouts[idx] = std::move(timeouts[idx-1]);
            --idx;
        }
        timeouts[idx] = timer_data{deadline, next_id++, userp, cb };
        return next_id;
    }
};

#endif // SIMPLE_LINEAR_ARRAY_H
