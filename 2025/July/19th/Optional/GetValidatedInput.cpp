#include <iostream>
#include <optional>

std::optional<int> getValidatedInput(const int number, const int min, const int max);

int main()
{
    std::optional<int> validation = getValidatedInput(5, 3, 7);

    if (validation.has_value())
    {
        std::cout << "Valid Input: " << validation.value() << std::endl;
    }
    else
    {
        std::cout << "Invalid Input!" << std::endl;
    }

    return 0;
}

std::optional<int> getValidatedInput(const int number, const int min, const int max)
{
    if (number <= max && number >= min)
    {
        return number;
    }
    else
    {
        return std::nullopt;
    }
}
