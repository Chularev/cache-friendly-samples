#include <random>

#include "simple_linear_array.h"
#include "move_backward_linear_array.h"
#include "memmove_linear_array.h"

#include "assert.h"

int main()
{
    simple_linear_array sla{};
    move_backward_linear_array mla{};
    memmove_backward_linear_array mma{};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist;

    for (int k = 0; k < 10; ++k) {
        for (int i = 0; i < 20'000; ++i) {
            auto id = dist(gen);
            sla.loop(id,i);
            mla.loop(id,i);
            mma.loop(id,i);
        }
    }
    assert(mla.timeouts == sla.timeouts);
    assert(mma.timeouts == sla.timeouts);

    return 0;
}
