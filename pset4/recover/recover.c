#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // check if number of arguments is correct
    if (argc != 2)
    {
        printf("Unvalid command.\n");
        return 1;
    }
    // the target of the memory file
    char *memory = argv[1];
    // open the file
    FILE *input = fopen(memory, "r");
    // if couldn't open the file
    if (input == NULL)
    {
        printf("Couldn't open target file!\n");
        return 1;
    }
    // creating buffer to collect data to the memory
    BYTE buffer[512];
    int imagecounter = 0;
    // makeing file name
    char filename[8];
    // pointer for the output file
    FILE *output = NULL;
    // while there are bytes found
    while (fread(buffer, 512, 1, input))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (imagecounter > 0)
            {
                fclose(output);
            }
            sprintf(filename, "%03i.jpg", imagecounter++);
            output = fopen(filename, "w");
            if (output == NULL)
            {
                return 1;
            }
            fwrite(buffer, 512, 1, output);
        }
        else if (imagecounter > 0)
        {
            fwrite(buffer, 512, 1, output);
        }
    }
    fclose(output);
    fclose(input);
}
