
#include "my_blinear_array.h"


int main()
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist;

    for (int k = 0; k < 10; ++k) {
        timer prev{};
        for (int i = 0; i < 20'000; ++i) {
            timer t = schedule_timer(dist(gen), [](void*){return 0U;}, nullptr);
            if (i & 1) cancel_timer(prev);
            prev = t;
        }
        while (shoot_first());
    }
}
