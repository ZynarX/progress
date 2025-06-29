#include <stdio.h>
#include <math.h>

int main()
{
    double principal = 0.0;
    double rate = 0.0;
    int years = 0;
    int timesCompounded = 0;
    double total = 0.0;

    printf("---- Compund Intrest Calculator ----\n");
    printf("Enter Principal (P): ");
    scanf("%lf", &principal);

    printf("Enter Intrest Rate % (r): ");
    scanf("%lf", &rate);

    rate = rate / 100;

    printf("Enter No. of Years (t): ");
    scanf("%d", &years);

    printf("Enter No. Compounded per Year (n): ");
    scanf("%d", &timesCompounded);

    total = principal * pow((1 + (rate / timesCompounded)), timesCompounded * years);

    printf("After %d year/s, the total will be: $%.2lf\n", years, total);

    return 0;
}
