
#include "simple_linear_array.h"


int main()
{
    simple_linear_array sla{};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist;

    for (int k = 0; k < 10; ++k) {
        for (int i = 0; i < 20'000; ++i) {
            auto id = dist(gen);
            sla.loop(id,i);
        }
    }

    return 0;
}
