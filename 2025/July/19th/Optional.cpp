// INTO TO OPTIONAL SEGMENT

#include <iostream>
#include <string>
#include <optional>

std::optional<std::string> getUserInput();

int main()
{
    std::optional<std::string> input = getUserInput();

    if (input != std::nullopt)
    {
        std::cout << input.value() << std::endl;
    }
    else
    {
        std::cout << "Invalid input!" << std::endl;
    }
}

std::optional<std::string> getUserInput()
{
    std::string input;

    std::cout << "Enter input: ";
    std::getline(std::cin >> std::ws, input);

    if (!input.empty())
    {
        return input;
    }

    return std::nullopt;
}
