#import <cs50.h>
#import <ctype.h>
#import <stdio.h>
#import <stdlib.h>
#import <string.h>

void encrypt(string text, int key);

const char ALPHABET[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                         'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main(int argc, string argv[])
{
    if (argc != 2 || atoi(argv[1]) < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Checks if non-numeric key, exit if true
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);
    string text = get_string("plaintext:  ");

    encrypt(text, key);
}

void encrypt(string text, int key)
{
    char plain_letter;
    char ciphered_letter;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Ignore if not alphabetical
        if (!isalpha(text[i]))
            continue;

        // If uppercase
        if (isupper(text[i]))
        {
            // Convert it first so that A is 0, B is 1, and so on.
            plain_letter = text[i] - 65;
            ciphered_letter = ALPHABET[(plain_letter + key) % 26]; // Get ciphered letter
        }

        // If lowercase
        else if (islower(text[i]))
        {
            plain_letter = text[i] - 97; // Convert it first so that A is 0, B is 1, and so on.
            ciphered_letter =
                tolower(ALPHABET[(plain_letter + key) %
                                 26]); // Get ciphered letter and convert back to lowercase
        }

        text[i] = ciphered_letter; // Replace with ciphered letter
    }

    printf("ciphertext: %s\n", text);
}
