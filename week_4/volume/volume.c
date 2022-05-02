// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t header[HEADER_SIZE];
typedef int16_t buffer;


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    header file_header;
    fread(&file_header, sizeof(header), 1, input);
    fwrite(&file_header, sizeof(header), 1, output);

    // Read samples from input file and write updated data to output file
    buffer file_body;
    while (fread(&file_body, sizeof(buffer), 1, input))
    {
        file_body = file_body * factor;
        fwrite(&file_body, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
