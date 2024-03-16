#import <cs50.h>
#import <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    // Prompt user for input
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1);

    // Print pyramid
    int spaces = height - 1;
    int bricks = 1;
    for (int i = 0; i < height; i++)
    {
        // Print row
        print_row(spaces, bricks);
        spaces--;
        bricks++;

        printf("\n");
    }
}

void print_row(int spaces, int bricks)
{
    // Print spaces
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }

    // Print bricks
    for (int j = 0; j < bricks; j++)
    {
        printf("#");
    }
}
