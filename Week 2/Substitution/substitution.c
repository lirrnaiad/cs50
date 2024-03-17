#import <cs50.h>
#import <ctype.h>
#import <stdio.h>
#import <stdlib.h>
#import <string.h>

void encrypt(char key[], int size, string text);

int main(int argc, string argv[])
{
    // 1 argument only, if not, print proper usage.
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Key must only contain alphabetical letters, if not, prompt again.
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    // Key must have 26 characters, if not, print proper usage.
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Key cannot have duplicate characters both in uppercase and lowercase
    for (int i = 1, n = strlen(argv[1]); i < n; i++)
    {
        // Check left side of i for duplicates
        for (int j = i - 1; j > -1; j--)
        {
            if (argv[1][i] == argv[1][j])
            {
                return 1;
            }
        }

        // Check right side of i for duplicates
        for (int k = i + 1; k < n; k++)
        {
            if (argv[1][i] == argv[1][k])
            {
                return 1;
            }
        }
    }

    // If argument is valid, put the key in a char array
    int size = strlen(argv[1]);
    char key[size];
    for (int i = 0; i < size; i++)
    {
        key[i] = toupper(argv[1][i]);
    }

    // Prompt user for the plaintext
    string plaintext = get_string("plaintext:  ");

    // Encrypt and print ciphertext
    encrypt(key, strlen(plaintext), plaintext);
    return 0;
}

void encrypt(char key[], int size, string text)
{
    char cipher_letter;

    for (int i = 0; i < size; i++)
    {
        // Ignore if not alphabetical
        if (!isalpha(text[i]))
            continue;

        // If uppercase
        else if (isupper(text[i]))
        {
            cipher_letter = key[(text[i] - 65) % 26];
        }

        // If lowercase
        else if (islower(text[i]))
        {
            cipher_letter = tolower(key[(text[i] - 97) % 26]);
        }

        text[i] = cipher_letter;
    }

    printf("ciphertext: %s\n", text);
}
