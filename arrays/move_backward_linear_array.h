#ifndef MOVE_BACKWARD_LINEAR_ARRAY_H
#define MOVE_BACKWARD_LINEAR_ARRAY_H
#include "common.h"

class move_backward_linear_array
{
public:
    move_backward_linear_array() = default;

    std::vector<struct timer_data> timeouts;
    uint32_t next_id = 0;

    bool is_after(uint32_t lh, uint32_t rh)
    {
        return lh < rh;
    }

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
        timeouts[insertion_pos] = timer_data{deadline, next_id++};
        return next_id - 1;
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

#endif // MOVE_BACKWARD_LINEAR_ARRAY_H
