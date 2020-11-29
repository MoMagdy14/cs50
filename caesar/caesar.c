#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void encrypt(string text, int key);  // Prototype Header

int main(int argc, string argv[]) // main
{
    // command line validation
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int n = strlen(argv[1]);
        for (int i = 0; i < n; i++)
        {
            // input validation
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // all is ok
        string text = get_string("plaintext:  ");
        int k = atoi(argv[1]);
        encrypt(text, k);
    }
    return 0;
}
// function to encrypt caesar cipher to get ciphertext
void encrypt(string text, int k)
{
    // actions
    string res = "";
    int n = strlen(text);
    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        // check if is alpha
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                printf("%c", 'A' + ((text[i] - 'A' + k) % 26));
            }
            else
            {
                printf("%c", 'a' + ((text[i] - 'a' + k) % 26));
            }
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}