#ifndef MEMMOVE_LINEAR_ARRAY_H
#define MEMMOVE_LINEAR_ARRAY_H
#include "common.h"
#include <stdio.h>
#include <string.h>

class memmove_backward_linear_array : public common_array
{
public:
    uint32_t schedule_timer(uint32_t deadline, timer_cb cb, void* userp) {
        // First ensure we have room
        timeouts.push_back({});

        // Find insertion point
        size_t idx = timeouts.size() - 1;
        while (idx > 0 && is_after(timeouts[idx-1].deadline, deadline)) {
            --idx;
        }

        // Only use memmove if we actually need to shift elements
        if (idx < timeouts.size() - 1) {
            // Calculate byte counts
            size_t elements_to_move = timeouts.size() - idx - 1;
            size_t bytes_to_move = elements_to_move * sizeof(timer_data);

            // Safe memmove usage
            memmove(
                &timeouts[idx+1],  // destination
                &timeouts[idx],    // source
                bytes_to_move      // byte count
                );
        }

        // Insert new element
        timeouts[idx] = timer_data{deadline, next_id++, userp, cb};
        return next_id;
    }


};

#endif // MEMMOVE_LINEAR_ARRAY_H
