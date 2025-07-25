#include <iostream>
#include <vector>

using namespace std;

int main()
{
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; i++)
    {
        if (i % 2 == 0)
        {
            std::cout << v[i];
        }
        else {
            std::cout << v[++i];
        }
    }
    return 0;
}
