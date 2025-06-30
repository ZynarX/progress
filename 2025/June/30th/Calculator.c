#include <stdio.h>

int main()
{
    char operator = '\0';
    double firstNumber = 0.0;
    double secondNumber = 0.0;
    double result = 0.0;

    printf("========== Calculator ==========\nEnter the first number: ");
    scanf("%lf", &firstNumber);

    printf("Enter the operator: ");
    scanf(" %c", &operator);

    printf("Enter the second number: ");
    scanf("%lf", &secondNumber);

    switch(operator)
    {
        case '+':
            result = firstNumber + secondNumber;
            break;
        case '-':
            result = firstNumber - secondNumber;
            break;
        case '*':
            result = firstNumber * secondNumber;
            break;
        case '/':
            if(secondNumber == 0.0)
            {
                printf("Cannot divide by 0!\n");
            }
            else
            {
                result = firstNumber / secondNumber;
            }
            break;
        default:
            printf("Invalid operator!\n");
    }

    printf("Result: %.2lf\n", result);

    return 0;
}
