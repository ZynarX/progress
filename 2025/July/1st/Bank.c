#include <stdio.h>

void CheckBalance(float balance);
float Deposit();
float Withdraw(float balance);

int main()
{
    int choice = 0;
    float balance = 0.0f;

    printf("===== BANK =====\n");

    do
    {
        printf("1. Check Balance\n2. Deposit\n3. Withdraw\n4. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                CheckBalance(balance);
                break;
            case 2:
                balance += Deposit();
                break;
            case 3:
                balance -= Withdraw(balance);
                break;
            case 4:
                printf("Exitting bank...\n");
                break;
            default:
                printf("Invalid choice!\n");
                // break;
        }

    } while (choice != 4);

    return 0;
}

void CheckBalance(float balance)
{
    printf("\nCurrent Balance: $%.2f\n", balance);
}

float Deposit()
{
    float amount = 0.0f;

    printf("\nEnter amount: $");
    scanf("%f", &amount);

    if(amount < 0)
    {
        printf("Invalid amount!\n");
        return 0.0f;
    }
    else
    {
        printf("Successfuly deposited $%.2f into account!\n", amount);
        return amount;
    }
}

float Withdraw(float balance)
{
    float amount = 0.0f;

    printf("\nEnter amount: $");
    scanf("%f", &amount);

    if(amount < 0)
    {
        printf("Invalid amount!\n");
        return 0.0f;
    }
    else if (amount > balance)
    {
        printf("Insufficient funds!\n");
        return 0.0f;
    }
    else
    {
        printf("Successfuly withdrew $%.2f from account!\n", amount);
        return amount;
    }
}
