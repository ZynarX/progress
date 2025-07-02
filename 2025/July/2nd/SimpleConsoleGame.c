#include <stdio.h>
#include <ctype.h>

typedef struct
{
    char name[50];
    char symbol;
    int x;
    int y;
} Player;

typedef struct
{
    Player* player;
    int width;
    int height;
} Game;

void RenderGame(Game* game);

int main()
{
    Player player = {"Bob", 'B', 0, 0};

    Game game = {&player, 10, 10};

    char option;

    printf("===== Simple Console Game =====\n");

    do
    {
        RenderGame(&game);

        printf("Choose an option (W,A,S,D, Q to Quit): ");
        scanf(" %c", &option);

        option = toupper(option);

        switch (option)
        {
            case 'W':
                if(player.y > 0)
                    player.y -= 1;
                break;
            case 'A':
                if(player.x > 0)
                    player.x -= 1;
                break;
            case 'S':
                if(player.y < 9)
                    player.y += 1;
                break;
            case 'D':
                if(player.x < 9)
                    player.x += 1;
                break;
            case 'Q':
                printf("Quitting...\n");
                break;
            default:
                printf("Invalid input!\n");
                break;
        }
    } while (option != 'Q');
    
    return 0;
}

void RenderGame(Game* game)
{
    for(int i = 0; i < game->width; i++)
    {
        printf("*");
    }

    printf("\n");

    for(int i = 0; i < game->height; i++)
    {
        for(int j = 0; j < game->width; j++)
        {
            if(j == game->player->x && i == game->player->y)
            {
                printf("%c", game->player->symbol);
            }
            else
            {
                printf(".");
            }
        }

        printf("\n");
    }

    for(int i = 0; i < game->width; i++)
    {
        printf("*");
    }

    printf("\n");
}
