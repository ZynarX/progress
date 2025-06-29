#include <stdio.h>

int main()
{
    float celsius = 0.0f;
    float fahrenheit = 0.0f;
    int choice = 0;

    printf("==== Temperature Conversion Calculator ====\n1. Celsius to Fahrenheit\n2. Fahrenheit to Celsius\nChoose an option: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        printf("Enter the temperature in Celsius (C): ");
        scanf("%f", &celsius);

        fahrenheit = (celsius * 9 / 5 ) + 32;

        printf("%.2f celsius is %.2f fahrenheit\n", celsius, fahrenheit);
    }
    else if(choice == 2)
    {
        printf("Enter the temperature in Fahrenheit (F): ");
        scanf("%f", &fahrenheit);

        celsius = (fahrenheit - 32) / (9/5);

        printf("%.2f degrees fahrenheit is %.2f degrees celsius\n", fahrenheit, celsius);
    }
    else
    {
        printf("Invalid option!\n");
    }

    return 0;
}
