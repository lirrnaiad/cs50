#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

void print_validity(long credit_number);
bool isValid(long number);
int check_digits(long number);

const double DECIMAL_DIVISOR = 10; // Constant divisor to iterate through the number (number / 10)
const int DIGIT_GET = 10;          // Constant to get the specific digit (number % 10)

int main(void)
{
    long credit_number = get_long("Number: ");
    print_validity(credit_number);
}

void print_validity(long credit_number)
{
    // If the card is invalid, well, print that it's invalid!
    if (!isValid(credit_number))
    {
        printf("INVALID\n");
        return;
    }

    int digits = check_digits(credit_number);
    int starting_digits;

    // Mastercard and Visa uses 16-digit numbers.
    if (digits == 16)
    {
        const double FIRST_TWO_DIGITS_GET =
            100000000000000; // Constant to automatically get first two digits.
        starting_digits = credit_number / FIRST_TWO_DIGITS_GET; // Get the first two digits.

        // Mastercard numbers start with 51, 52, 53, 54, or 55.
        if (starting_digits > 50 && starting_digits < 56)
        {
            printf("MASTERCARD\n");
            return;
        }

        // Visa numbers start with 4.
        else if (starting_digits / 10 == 4)
        {
            printf("VISA\n");
            return;
        }
    }

    // American Express uses 15-digit numbers.
    else if (digits == 15)
    {
        const double FIRST_TWO_DIGITS_GET =
            10000000000000; // Constant to automatically get first two digits.
        starting_digits = credit_number / FIRST_TWO_DIGITS_GET; // Get the first two digits.

        // American Express cards start with 34 or 37.
        if (starting_digits == 34 || starting_digits == 37)
        {
            printf("AMEX\n");
            return;
        }
    }

    // Visa also uses 13-digit cards.
    else if (digits == 13)
    {
        const double FIRST_DIGIT_GET =
            1000000000000; // Constant to automatically get first two digits.
        starting_digits = credit_number / FIRST_DIGIT_GET; // Get the first digit.

        // As mentioned previously, Visa cards start with 4.
        if (starting_digits == 4)
        {
            printf("VISA\n");
            return;
        }
    }

    // If nothing is satisfied, print invalid.
    printf("INVALID\n");
}

bool isValid(long number)
{
    // May be confusing, look up "Luhn's Algorithm" for a more detailed explanation.

    int digit; // Digit placeholder

    // Sums for the digits that were multiplied by 2 and not
    int sum_multiplied = 0;
    int sum_not_multiplied = 0;

    int loop_counter = 1; // Loop counter to check if even or odd.

    // Calculation
    while (number > 0)
    {
        // Initial loop
        if (loop_counter == 1)
        {
            digit = number % DIGIT_GET;
            sum_not_multiplied += digit;
            loop_counter++;
            continue;
        }

        // If loop counter is even, multiply the digit by 2.
        if (loop_counter % 2 == 0)
        {
            number = (double) number / DECIMAL_DIVISOR;
            digit = number % DIGIT_GET;
            int product = digit * 2;

            // If product is greater than 10, only add the digits, not the product itself
            if (product >= 10)
            {
                while (product > 0)
                {
                    sum_multiplied += product % DIGIT_GET;
                    product = (double) product / DECIMAL_DIVISOR;
                }
            }

            // Otherwise, if it's only one digit, add it normally
            else
            {
                sum_multiplied += product;
            }
        }

        // If loop counter is odd, add the digit normally
        else
        {
            number = (double) number / DECIMAL_DIVISOR;
            digit = number % DIGIT_GET;
            sum_not_multiplied += digit;
        }

        loop_counter++;
    }

    int total_sum = sum_multiplied + sum_not_multiplied;

    // If the total's sum last digit is a 0, it is valid.
    return total_sum % 10 == 0;
}

int check_digits(long number)
{
    int digits = 0;

    while (number > 0)
    {
        digits++;
        number = (double) number / 10;
    }

    return digits;
}
