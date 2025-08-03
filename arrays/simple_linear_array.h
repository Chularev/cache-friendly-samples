#ifndef SIMPLE_LINEAR_ARRAY_H
#define SIMPLE_LINEAR_ARRAY_H

#include "common.h"
#include <stdio.h>
#include <string.h>

class simple_linear_array : public common_array
{
public:
    uint32_t schedule_timer(uint32_t deadline, timer_cb cb, void* userp) {
        // First ensure we have room
        timeouts.push_back({});

        // Find insertion point that exactly matches linear search behavior
        auto it = std::upper_bound(
            timeouts.begin(),
            timeouts.end() - 1,
            deadline,
            [](uint32_t val, const timer_data& a) {  // Note: reversed arguments
                return val >= a.deadline;  // Equivalent to original condition
            }
            );
        size_t idx = it - timeouts.begin();

        // Only shift if needed
        if (idx < timeouts.size() - 1) {
            size_t bytes = (timeouts.size() - idx - 1) * sizeof(timer_data);
            memmove(&timeouts[idx+1], &timeouts[idx], bytes);
        }

        timeouts[idx] = timer_data{deadline, next_id++, userp, cb};
        return next_id;
    }
};

#endif // SIMPLE_LINEAR_ARRAY_H
