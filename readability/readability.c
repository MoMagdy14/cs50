#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // variables
    string text = get_string("Text:");
    double letters = 0;
    double words = 0;
    double sen = 0;
    int n = strlen(text);
    // count words,letter,sen
    for (int i = 0; i < n; i++)
    {
        // check
        if (isalpha(text[i]))
        {
            letters++;
        }
        // check
        if (i == 0 && text[i] != ' ')
        {
            words++;
        }
        // check
        if (i < n - 1 && text[i] == ' ' && text[i + 1] != ' ')
        {
            words++;
        }
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            sen++;
        }
    }
    // check L S
    double L = letters / (words / 100);
    double S = sen / (words / 100);
    double index =  0.0588 * L - 0.296 * S - 15.8;
    printf("%f\n", index);
    index = round(index);
    printf("%f\n", index);
    // print
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}