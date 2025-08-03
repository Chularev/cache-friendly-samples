#ifndef SIMPLE_LINEAR_ARRAY_H
#define SIMPLE_LINEAR_ARRAY_H

#include "common.h"
#include <stdio.h>
#include <string.h>

class simple_linear_array : public common_array
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

        size_t insertion_pos = it - timeouts.begin();

        timeouts.push_back({});

        // Move elements if needed
        if (insertion_pos < timeouts.size() - 1) {
            std::move_backward(timeouts.begin() + insertion_pos,
                               timeouts.end() - 1,  // Correct range to move
                               timeouts.end());
        }

        // Insert new element
        timeouts[insertion_pos] = std::move(element);
        return next_id;
    }
};

#endif // SIMPLE_LINEAR_ARRAY_H
