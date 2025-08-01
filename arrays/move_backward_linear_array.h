#ifndef MOVE_BACKWARD_LINEAR_ARRAY_H
#define MOVE_BACKWARD_LINEAR_ARRAY_H
#include "common.h"

class move_backward_linear_array : public common_array
{
public:
    uint32_t schedule_timer(uint32_t deadline, timer_cb cb, void* userp)
    {
        // Find insertion position first
        auto insertion_pos = timeouts.size();
        while (insertion_pos > 0 && is_after(timeouts[insertion_pos-1].deadline, deadline)) {
            --insertion_pos;
        }

        // Add space for new element
        timeouts.push_back({});

        // Move elements if needed
        if (insertion_pos < timeouts.size() - 1) {
            std::move_backward(timeouts.begin() + insertion_pos,
                               timeouts.end() - 1,  // Correct range to move
                               timeouts.end());
        }

        // Insert new element
        timeouts[insertion_pos] = timer_data{deadline, next_id++, userp, cb};
        return next_id;
    }


};

#endif // MOVE_BACKWARD_LINEAR_ARRAY_H
