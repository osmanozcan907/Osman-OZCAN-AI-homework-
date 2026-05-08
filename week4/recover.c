#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ---------------------------------------------------------------------------
    // TODO 1: Validate command-line arguments
    // ---------------------------------------------------------------------------
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // ---------------------------------------------------------------------------
    // TODO 2: Open the memory card file for reading (binary mode)
    // ---------------------------------------------------------------------------
    FILE *card = fopen(argv[1], "rb");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // ---------------------------------------------------------------------------
    // TODO 3: Declare your variables
    // ---------------------------------------------------------------------------
    BYTE buffer[512];      // Memory cards store data in 512-byte blocks
    int count = 0;         // Keep track of how many JPEGs we find
    FILE *img = NULL;      // Pointer for the current output file
    char filename[8];      // Buffer to store name like "000.jpg\0"

    // ---------------------------------------------------------------------------
    // TODO 4: Main loop — read one 512-byte block at a time
    // ---------------------------------------------------------------------------
    while (fread(buffer, 1, 512, card) == 512)
    {
        // STEP A: Check if this block starts a new JPEG
        // Look for the specific 4-byte signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && 
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // STEP B: If we already have an open file, close it before opening a new one
            if (img != NULL)
            {
                fclose(img);
            }

            // STEP C: Open a new output file
            // Generate filename with leading zeros (e.g., 001.jpg)
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "wb");
            
            if (img == NULL)
            {
                printf("Could not create output file %s.\n", filename);
                return 1;
            }

            count++;
        }

        // STEP D: If we currently have an open output file, write the block
        // This continues writing blocks even if they don't have a header,
        // because they belong to the current JPEG until a new header is found.
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // ---------------------------------------------------------------------------
    // TODO 5: Close any remaining open file and close the card
    // ---------------------------------------------------------------------------
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);

    return 0;
}
