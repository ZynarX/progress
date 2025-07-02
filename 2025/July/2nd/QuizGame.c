#include <stdio.h>
#include <ctype.h>

int main()
{
    char questions[][100] = {"What is the largest planet in the solar system?",
                             "What is the hottest planet in the solar system?",
                             "What planet has the most moons in the solar system?",
                             "Is the Earth flat?"};
    char options[][100] = {"A. Jupiter\nB. Saturn\nC. Uranus\nD. Neptune",
                           "A. Mercury\nb. Venus\nc. Earth\nd. Mars",
                           "A. Earth\nB. Mars\nC. Junpiter\nD. Saturn",
                           "A. Yes\nB. No\nC. Maybe\nD. Sometimes"};
    char answerKey[] = {'A', 'B', 'D', 'D'};

    char guess = '\0';

    int questionCount = sizeof(questions) / sizeof(questions[0]);
    int score = 0;

    printf("===== QUIZ GAME =====");

    for(int i = 0; i < questionCount; i++)
    {
        printf("\n%s\n", questions[i]);
        printf("\n%s\n", options[i]);
        printf("Choose an option: ");
        scanf(" %c", &guess);

        guess = toupper(guess);

        if(guess == answerKey[i])
        {
            printf("Correct!\n");
            score++;
        }
        else
        {
            printf("Wrong!\n");
        }
    }

    printf("\nYour score is %d out of %d points!\n", score, questionCount);

    return 0;
}
