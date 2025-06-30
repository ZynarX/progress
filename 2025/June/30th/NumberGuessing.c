#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    int guess = 0;
    int tries = 0;
    int MIN = 1;
    int MAX = 100;

    int random_number = (rand() % (MAX - MIN + 1)) + MIN;

    printf("===== Number Guessing Game =====\n");

    do
    {
        printf("Guess a number between (%d->%d): ", MIN, MAX);
        scanf("%d", &guess);

        tries++;

        if(guess > random_number)
        {
            printf("Too high!\n");
        }
        else if(guess < random_number)
        {
            printf("Too low!\n");
        }
        else
        {
            printf("Correct!\n\n");
        }
    } while (guess != random_number);

    printf("The answer was: %d\n", random_number);
    printf("It took you %d tries to guess it!", tries);

    return 0;
}
