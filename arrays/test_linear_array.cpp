#include <random>

#include "simple_linear_array.h"
#include "move_backward_linear_array.h"

void loop()
{

}
int main()
{
    simple_linear_array sla{};
    move_backward_linear_array mla{};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist;

    for (int k = 0; k < 10; ++k) {
        uint32_t prev{};
        for (int i = 0; i < 20'000; ++i) {
            auto id = dist(gen);
            uint32_t t = sla.schedule_timer(id, [](void*){return 0U;}, nullptr);
            if (i & 1) sla.cancel_timer(prev);
            prev = t;
        }
    }
    return 0;
}
