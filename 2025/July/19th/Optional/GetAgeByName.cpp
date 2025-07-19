#include <iostream>
#include <string>
#include <map>
#include <optional>

std::optional<int> GetAgeByName(std::map<std::string, int>& people, const std::string& name);

int main()
{
    std::map<std::string, int> people = {
        {"Bob", 19},
        {"Mike", 23},
        {"Elsa", 17},
        {"Sarah", 25}
    };

    std::string name = "Elsa";
    std::optional<int> age = GetAgeByName(people, name);

    if (age != std::nullopt)
    {
        std::cout << "The age of " << name << " is: " << age.value() << std::endl;
    }
    else
    {
        std::cout << "Couldn't find the age of " << name << "!" << std::endl;
    }

    return 0;
}

std::optional<int> GetAgeByName(std::map<std::string, int>& people, const std::string& name)
{
    for(auto& pair : people)
    {
        if (pair.first == name)
        {
            return pair.second;
        }
    }

    return std::nullopt;
}
