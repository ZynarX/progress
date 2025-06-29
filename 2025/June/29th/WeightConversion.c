#include <stdio.h>

int main()
{
    int choice = 0;
    float pounds = 0.0f;
    float kilograms = 0.0f;

    printf("==== Weight Conversion Calculator ====\n1. KG to LB\n2. LB to KG\nChoose an option: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter weight in KG (Kilograms): ");
        scanf("%f", &kilograms);

        pounds = kilograms * 2.20462;

        printf("%.2f Kilograms is %.2f Pounds\n", kilograms, pounds);
    }
    else if (choice == 2)
    {
        printf("Enter weight in LB (Pounds): ");
        scanf("%f", &pounds);

        kilograms = pounds / 2.20462;

        printf("%.2f LB is %.2f Kilograms\n", pounds, kilograms);
    }
    else
    {
        printf("Invalid option!\n");
    }

    return 0;
}
