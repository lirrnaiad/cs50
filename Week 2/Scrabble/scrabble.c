#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int convert_to_points(string s);
void check_winner(int player_one, int player_two);

int main(void)
{
    // Prompt the two players for their words
    string player_one = get_string("Player 1: ");
    string player_two = get_string("Player 2: ");

    check_winner(convert_to_points(player_one), convert_to_points(player_two));
}

int convert_to_points(string s)
{
    int total_points = 0;

    // Calculate points of word by iterating through each letter and getting their points
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Only convert alphabetical characters. If not alphabetical, ignore.
        if (isalpha(s[i]))
        {
            s[i] = toupper(s[i]); // Convert to uppercase
            total_points +=
                POINTS[(s[i] - 'A')]; // Calculate the letter's points and add it to the sum
        }
    }

    return total_points;
}

void check_winner(int player_one, int player_two)
{
    if (player_one > player_two)
    {
        printf("Player 1 wins!\n");
    }

    else if (player_two > player_one)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie!\n");
    }
}
