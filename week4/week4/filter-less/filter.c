// filter.c
// CS50x — Week 4, Problem Set 4
// 
// This file orchestrates the image filtering process.

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "helpers.h"

int main(int argc, char *argv[])
{
    // ---------------------------------------------------------------------------
    // 1. ARGUMENT PARSING
    // ---------------------------------------------------------------------------
    // Uses getopt to check which filter flag was provided (-b, -g, -r, or -s).
    // It ensures the user provided exactly one valid flag and the correct files.

    // ---------------------------------------------------------------------------
    // 2. FILE HANDLING
    // ---------------------------------------------------------------------------
    // Opens the input BMP file for reading ('rb') and the output for writing ('wb').
    // It reads the BITMAPFILEHEADER and BITMAPINFOHEADER (54 bytes total) to
    // verify if the file is a valid 24-bit uncompressed BMP.

    // ---------------------------------------------------------------------------
    // 3. MEMORY ALLOCATION
    // ---------------------------------------------------------------------------
    // Uses calloc to dynamically allocate memory on the HEAP for the entire image.
    // The 'image' variable is a 2D array of RGBTRIPLE structs.
    
    // ---------------------------------------------------------------------------
    // 4. HANDLING PADDING
    // ---------------------------------------------------------------------------
    // BMP scanlines must be a multiple of 4 bytes. If the width of the image
    // isn't a multiple of 4, the file adds 'padding' bytes (0x00) at the end 
    // of each row. This code calculates and skips those bytes during reading.

    // ---------------------------------------------------------------------------
    // 5. CALLING YOUR HELPERS
    // ---------------------------------------------------------------------------
    // Depending on the flag, it calls:
    // blur(), grayscale(), reflect(), or sepia().
    
    // ---------------------------------------------------------------------------
    // 6. WRITING THE RESULT
    // ---------------------------------------------------------------------------
    // Writes the headers and the modified 2D array of pixels back into the 
    // output file, making sure to re-add the necessary padding bytes.

    // ---------------------------------------------------------------------------
    // 7. CLEANUP
    // ---------------------------------------------------------------------------
    // Frees the allocated memory and closes the files to prevent memory leaks.
}
