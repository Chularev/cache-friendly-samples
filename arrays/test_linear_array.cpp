#include <random>


#include "my_blinear_array.h"

#include "assert.h"

int main()
{
    my_blinear_array mma{};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist;

    for (int k = 0; k < 10; ++k) {
        for (int i = 0; i < 20'000; ++i) {
            auto id = dist(gen);
    //        mla.loop(id,i);
            mma.loop(id,i);
        }
    }
    //assert(mla.timeouts == sla.timeouts);

    return 0;
}
