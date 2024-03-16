#include <cs50.h>
#include <stdio.h>

int get_change(int change_owed);

int main(void)
{
    // Prompt user for the change owed, cannot be n < 0
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);

    // Calculate how many coins needed for change
    printf("%i\n", get_change(change));
}

int get_change(int change)
{
    // Counter for coins
    int coins = 0;

    while (change > 0)
    {
        // 25 cents
        if (change >= 25)
        {
            change -= 25;
            coins++;
        }

        // 10 cents
        else if (change >= 10)
        {
            change -= 10;
            coins++;
        }

        // 5 cents
        else if (change >= 5)
        {
            change -= 5;
            coins++;
        }

        // 1 cent
        else
        {
            change--;
            coins++;
        }
    }

    return coins;
}
