#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int letter_count(string text);
int word_count(string text);
int sentence_count(string text);
void print_reading_level(string text);

int main(void)
{
    string text = get_string("Text: ");
    print_reading_level(text);
}

// Getting the number of letters in a text
int letter_count(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

// Getting the number of words in a text
int word_count(string text)
{
    int words = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }

    return words + 1; // Count the last word
}

// Getting the number of sentences in a text
int sentence_count(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }

    return sentences;
}

// Calculate the reading level and print it
void print_reading_level(string text)
{
    int letters = letter_count(text);
    int words = word_count(text);
    int sentences = sentence_count(text);

    float L = ((float) letters / (float) words) * 100; // Average number of letters per 100 words
    float S = ((float) sentences / (float) words) * 100; // Average number of sentences per 100 words

    double index = 0.0588 * L - 0.296 * S - 15.8; // Coleman-Liau index
    int grade_level = (int) round(index); // Round the result of the formula

    // Print grade level
    if (grade_level >= 16)
    {
        printf("Grade 16+\n");
    }

    else if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", grade_level);
    }
}
