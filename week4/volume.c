#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // TODO 1: Validate command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // TODO 2: Open input and output files
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open %s.\n", argv[2]);
        fclose(input);
        return 1;
    }

    // TODO 3: Read and write the WAV header (first 44 bytes) unchanged
    // We use uint8_t (1 byte) for raw byte-by-byte copying of the header
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // TODO 4: Read the volume factor from argv[3]
    float factor = atof(argv[3]);

    // ---------------------------------------------------------------------------
    // TODO 5: Read each audio sample, scale it, and write it out
    // ---------------------------------------------------------------------------
    // Audio samples in a .wav file are 16-bit signed integers (int16_t)
    int16_t sample;

    // fread returns the number of items successfully read. 
    // It will return 1 for each sample until it hits the end of the file.
    while (fread(&sample, sizeof(int16_t), 1, input) == 1)
    {
        // Multiply the current sample by the factor to modify the volume.
        // We cast the result to (int16_t) to ensure the type matches after multiplication.
        sample = (int16_t)(sample * factor);

        // Write the modified sample to the output file
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    // TODO 6: Close both files to free resources
    fclose(input);
    fclose(output);

    return 0;
}
