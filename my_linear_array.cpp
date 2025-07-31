#include <cassert>
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

bool operator==(const timer_data t1, const timer_data t2)
{
    return t1.deadline == t2.deadline && t1.id == t2.id;
}
static std::vector<struct timer_data> timeouts;
static std::vector<struct timer_data> timeouts2;
static uint32_t next_id = 0;

static bool is_after(uint32_t lh, uint32_t rh)
{
    return lh < rh;
}

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

uint32_t schedule_timer2(uint32_t deadline, timer_cb cb, void* userp)
{
    auto idx = timeouts2.size();
    timeouts2.push_back({});
    while (idx > 0 && is_after(timeouts2[idx-1].deadline, deadline)) {
        timeouts2[idx] = std::move(timeouts2[idx-1]);
        --idx;
    }
    timeouts2[idx] = timer_data{deadline, next_id - 1, userp, cb };
    return next_id;
}
void cancel_timer(uint32_t t)
{
    auto i = std::find_if(timeouts.begin(), timeouts.end(),
                          [t](const auto& e) { return e.id == t; });
    timeouts.erase(i);

    auto i2 = std::find_if(timeouts2.begin(), timeouts2.end(),
                          [t](const auto& e) { return e.id == t; });
    timeouts2.erase(i2);
}

bool shoot_first()
{
    if (timeouts.empty()) return false;
    timeouts.front().callback(timeouts.front().userp);
    timeouts.erase(timeouts.begin());


    if (timeouts2.empty()) return false;
    timeouts2.front().callback(timeouts2.front().userp);
    timeouts2.erase(timeouts2.begin());
    return true;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist;

    for (int k = 0; k < 10; ++k) {
        uint32_t prev{};
        for (int i = 0; i < 20'000; ++i) {
            auto d = dist(gen);
            uint32_t t = schedule_timer(d, [](void*){return 0U;}, nullptr);
            schedule_timer2(d, [](void*){return 0U;}, nullptr);
            if (i & 1) cancel_timer(prev);
            prev = t;
        }
        assert(timeouts == timeouts2);
        while (shoot_first())
            ;
    }
}
