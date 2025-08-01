#include "move_backward_linear_array.h"

int main()
{

    move_backward_linear_array array;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist;

    for (int k = 0; k < 10; ++k) {
        for (int i = 0; i < 20'000; ++i) {
            auto id = dist(gen);
            array.loop(id,i);
        }
    }

    return 0;
}
