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

        // Find insertion point in [begin, end-1] range
        auto it = std::lower_bound(
            timeouts.begin(),
            timeouts.end() - 1,  // Key difference: exclude new empty slot
            deadline,
            [](const timer_data& a, uint32_t val) {
                return a.deadline > val;
            }
            );
        size_t idx = it - timeouts.begin();

        // Rest remains the same
        if (idx < timeouts.size() - 1) {
            size_t bytes_to_move = (timeouts.size() - idx - 1) * sizeof(timer_data);
            memmove(&timeouts[idx+1], &timeouts[idx], bytes_to_move);
        }
        timeouts[idx] = timer_data{deadline, next_id++, userp, cb};
        return next_id;
    }
};

#endif // SIMPLE_LINEAR_ARRAY_H
