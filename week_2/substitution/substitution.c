#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main (int argc, string argv[])
{
    if (argc == 2)
    {
        // check length of the key
        int keyLength = strlen(argv[1]);
        if (keyLength == 26)
        {
            //check if all key chars are alphabet type
            for (int i=0; i<keyLength; i++)
            {
                char keyCharacter = argv[1][i];
                if (isalpha(keyCharacter) == 0)
                {
                    printf("Key must contain only alphabetical characters.\n");
                    return 1;
                }
            }

            //ask for input
            string userInput = get_string("Input: ");
            printf("Output: ");

            for (int j=0; j<strlen(userInput); j++)
            {
                char userInputChar = userInput[j];
                // for small letter input print small letter char output
                if (userInputChar >= 97 && userInputChar <= 122)
                {
                    for (int k=0; k<strlen(alphabet); k++)
                    {
                        if (toupper(userInputChar) == alphabet[k])
                        {
                            printf("%c", tolower(argv[1][k]));
                        }
                    }
                }
                // for big letter input print big letter char output
                else if (userInputChar >= 65 && userInputChar <= 90)
                {
                    for (int k=0; k<strlen(alphabet); k++)
                    {
                        if (userInputChar == alphabet[k])
                        {
                            printf("%c", argv[1][k]);
                        }
                    }
                }
                else
                {
                    printf("%c", userInputChar);
                }
            }
            printf("\n");
        }
        else
        {
            printf("Key must contain 26 characters.\n");
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
    }
}