#include <iostream>
#include <variant>

void GetHeld(std::variant<int, float, bool>& variant);

int main()
{
    std::variant<int, float, bool> variant;

    variant = true;
    variant = 19;
    variant = 175.5f;

    GetHeld(variant);

    return 0;
}

void GetHeld(std::variant<int, float, bool>& variant)
{
    if (std::holds_alternative<int>(variant))
    {
        // try
        // {
            int intval = std::get<int>(variant);

            std::cout << "Holding Int of Value: " << intval;
        // }
        // catch(const std::bad_variant_access&)
        // {
        //     std::cerr << "Varaint doesn't hold integer!\n";
        // }
        
    }
    else if (std::holds_alternative<float>(variant))
    {
        // try
        // {
            float floatval = std::get<float>(variant);

            std::cout << "Holding Float of Value: " << floatval;
        // }
        // catch(const std::bad_variant_access&)
        // {
        //     std::cerr << "Variant doesn't hold float!\n";
        // }
    }
    else if (std::holds_alternative<bool>(variant))
    {
        // try
        // {
            bool boolval = std::get<bool>(variant);

            std::cout << "Holding Bool of Value: " << boolval;
        // }
        // catch(const std::bad_variant_access&)
        // {
        //    std::cerr << "Variant doesn't hold boolean!\n";
        // }
    }
    else
    {
        std::cout << "Not holding any value!\n";
    }
}
