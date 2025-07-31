#ifndef COMMON_H
#define COMMON_H

#include <memory>
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


#endif // COMMON_H
