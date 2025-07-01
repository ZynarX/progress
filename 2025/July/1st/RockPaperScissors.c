#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int GetComputerChoice();
int GetUserChoice();
void CheckWinner(int User, int Computer);

int main()
{
    srand(time(NULL));

    printf("===== ROCK PAPER SCISSORS =====\n");

    int UserChoice = GetUserChoice();
    int ComputerChoice = GetComputerChoice();

    switch(UserChoice)
    {
        case 1:
            printf("You chose ROCK!\n");
            break;
        case 2:
            printf("You chose PAPAER!\n");
            break;
        case 3:
            printf("You chose SCISSORS!\n");
            break;
    }

    switch(ComputerChoice)
    {
        case 1:
            printf("Computer chose ROCK!\n");
            break;
        case 2:
            printf("Computer chose PAPAER!\n");
            break;
        case 3:
            printf("Computer chose SCISSORS!\n");
            break;
    }

    CheckWinner(UserChoice, ComputerChoice);

    return 0;
}

int GetComputerChoice()
{
    return (rand() % 3) + 1;
}

int GetUserChoice()
{
    int choice = 0;

    do
    {
        printf("Choose an ooption:\n1. Rock\n2. Paper\n3. Scissors\nEnter your choice: ");
        scanf("%d",&choice);
    } while (choice < 1 || choice > 3);
    
    return choice;
}

void CheckWinner(int User, int Computer)
{
    if(User == Computer)
    {
        printf("It's a TIE!\n");
    }
    else if(User == 1)
    {
        if(Computer == 3)
        {
            printf("You WIN!\n");
        }
        else if(Computer == 2)
        {
            printf("You LOSE!\n");
        }
    }
    else if(User == 2)
    {
        if(Computer == 1)
        {
            printf("You WIN!\n");
        }
        else if(Computer == 3)
        {
            printf("You LOSE!\n");
        }
    }
    else if(User == 3)
    {
        if(Computer == 1)
        {
            printf("You WIN!\n");
        }
        else if(Computer == 2)
        {
            printf("You LOSE!\n");
        }
    }
}
