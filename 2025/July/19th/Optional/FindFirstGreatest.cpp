#include <iostream>
#include <vector>
#include <optional>

std::optional<int> findFirstGreatest(std::vector<int>& vector, const int threshold);

int main()
{
    std::vector<int> vector = {2, 4, 6, 8, 10};
    int threshold = 7;

    std::cout << findFirstGreatest(vector, threshold).value() << std::endl;
}

std::optional<int> findFirstGreatest(std::vector<int>& vector, const int threshold)
{
    for(int& current : vector)
    {
        if (current > threshold)
        {
            return current;
        }
    }

    return std::nullopt;
}
