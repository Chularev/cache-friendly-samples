#include <iostream>
#include <random>
#include <chrono>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);

    volatile int result = 0; // volatile to prevent optimization

    auto start = std::chrono::high_resolution_clock::now();

    // Force unpredictable branches
    for (int i = 0; i < 10000000; ++i) {
        if (dist(gen)) {  // 50% misprediction rate
            result += i;
        } else {
            result -= i;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Result: " << result << "\n";
    std::cout << "Time: " << elapsed.count() << "s\n";
    return 0;
}
