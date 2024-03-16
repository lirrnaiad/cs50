#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    // Prompt user for input
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Print pyramids
    int spaces = height - 1;
    int bricks = 1;
    for (int i = 0; i < height; i++)
    {
        print_row(spaces, bricks);
        spaces--;
        bricks++;

        printf("\n");
    }
}

void print_row(int spaces, int bricks)
{
    // Print spaces of first pyramid
    for (int space = 0; space < spaces; space++)
    {
        printf(" ");
    }

    // Print bricks of first pyramid
    for (int bricksLeft = 0; bricksLeft < bricks; bricksLeft++)
    {
        printf("#");
    }

    // Print spaces between
    for (int middleSpace = 0; middleSpace < 2; middleSpace++)
    {
        printf(" ");
    }

    // Print bricks of second pyramid
    for (int bricksRight = 0; bricksRight < bricks; bricksRight++)
    {
        printf("#");
    }
}
