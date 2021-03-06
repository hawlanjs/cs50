// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;  //Read Only

typedef uint8_t ONE_BYTE;
typedef int16_t AUDIO_BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r"), *output = fopen(argv[2], "w");
    if (!input || !output)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    ONE_BYTE header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file
    AUDIO_BYTE buffer;
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
