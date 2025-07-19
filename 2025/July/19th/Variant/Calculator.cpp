#include <iostream>
#include <vector>
#include <variant>

void Calculate(std::vector<std::variant<int, float>>& variants, float* total, char& operand);

int main()
{
    std::variant<int, float> firstvariant;
    firstvariant = 10;
    
    std::variant<int, float> secfvariant;
    secfvariant = 5.5f;

    std::variant<int, float> secvariant;
    secvariant = 12;

    std::variant<int, float> secsvariant;
    secsvariant = 16.4f;

    float total = 0;

    char operand = '/';

    std::vector<std::variant<int, float>> variants = {firstvariant, secfvariant, secvariant, secsvariant};

    Calculate(variants, &total, operand);

    std::cout << "= " << total << std::endl;
}

void Calculate(std::vector<std::variant<int, float>>& variants, float* total, char& operand)
{
    std::cout << "Total: ";
    for(size_t i = 0; i < variants.size(); i++)
    {
        if (i >= (size_t)1)
        {
            std::cout << "/ ";
        }

        auto& variant = variants[i];

        float curTotal = 0.0f;

        std::visit([&](auto&& value){
            curTotal += static_cast<float>(value);
        }, variant);

        std::cout << curTotal << " ";

        if (i == (size_t)0)
        {
            *total += curTotal;
            continue;
        }
        
        switch(operand)
        {
            case '+':
                *total += curTotal;
                break;
            case '-':
                *total -= curTotal;
                break;
            case '*':
                *total *= curTotal;
                break;
            case '/':
                *total /= curTotal;
                break;
        }
    }
}
