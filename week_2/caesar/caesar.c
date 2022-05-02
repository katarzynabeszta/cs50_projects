#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char outputChar (char userInput, int asciiNumber, int key);

int main (int argc, string argv[])
{
    if (argc == 2)
    {
        printf("Key is: %s\n", argv[1]);

        // divide argv[1] to chars and check if each char is a number
        for(int i=0; i<strlen(argv[1]); i++)
        {
            if (argv[1][i] < 48 || argv[1][i] > 57)
            {
                printf("Usage: ./caesar key as a number\n");
                return 1;
            }
        }

        // change char from string to int
        int key = atoi(argv[1]);

        // ask user for input
        string userInput = get_string("Input: ");
        string output;
        printf("Output: ");

        for (int u=0; u<strlen(userInput); u++)
        {
            char outputCharacter = '\0';

            if (isupper(userInput[u]) != false)
            {
                outputCharacter = outputChar (userInput[u], 65, key);
            }
            else if (islower(userInput[u]) != false)
            {
                outputCharacter = outputChar (userInput[u], 97, key);
            }
            else
            {
                outputCharacter = userInput[u];
                printf("%c", outputCharacter);
            }
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
    }
    return 0;
}

char outputChar (char anyUserInput, int asciiNumber, int key)
    {
    int inputAsAlphabeticalIndex = (anyUserInput - asciiNumber);
    char outputAsASCII = ((inputAsAlphabeticalIndex + key) % 26) + asciiNumber;
    char charOutputCharacter = '\0';
    charOutputCharacter = charOutputCharacter + outputAsASCII;
    printf("%c", charOutputCharacter);
    return charOutputCharacter;
}