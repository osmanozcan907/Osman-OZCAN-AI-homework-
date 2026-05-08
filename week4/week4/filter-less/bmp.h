// bmp.h
// CS50x — Week 4, Problem Set 4
// 
// Data types for BMP file structures.

#include <stdint.h>

// ---------------------------------------------------------------------------
// 1. Data Type Aliases
// ---------------------------------------------------------------------------
// These aliases make the code more readable and follow the Windows API style.
typedef uint8_t  BYTE;   // 1 byte (8 bits)
typedef uint32_t DWORD;  // 4 bytes (32 bits)
typedef int32_t  LONG;   // 4 bytes (32 bits signed)
typedef uint16_t WORD;   // 2 bytes (16 bits)

// ---------------------------------------------------------------------------
// 2. BITMAPFILEHEADER (14 bytes)
// ---------------------------------------------------------------------------
// Contains general information about the file.
typedef struct
{
    WORD   bfType;      // File type (must be 0x4d42, which is 'BM' in ASCII)
    DWORD  bfSize;      // Total size of the file in bytes
    WORD   bfReserved1; // Reserved (always 0)
    WORD   bfReserved2; // Reserved (always 0)
    DWORD  bfOffBits;   // The offset (starting address) of the pixel data
} __attribute__((__packed__))
BITMAPFILEHEADER;

// ---------------------------------------------------------------------------
// 3. BITMAPINFOHEADER (40 bytes)
// ---------------------------------------------------------------------------
// Contains detailed information about the image dimensions and format.
typedef struct
{
    DWORD  biSize;          // Size of this header (40 bytes)
    LONG   biWidth;         // Width of the image in pixels
    LONG   biHeight;        // Height of the image in pixels
    WORD   biPlanes;        // Number of color planes (must be 1)
    WORD   biBitCount;      // Bits per pixel (usually 24 for RGB)
    DWORD  biCompression;   // Type of compression (0 for uncompressed)
    DWORD  biSizeImage;     // Size of the raw bitmap data
    LONG   biXPelsPerMeter; // Horizontal resolution
    LONG   biYPelsPerMeter; // Vertical resolution
    DWORD  biClrUsed;       // Number of colors in the palette
    DWORD  biClrImportant;  // Number of important colors
} __attribute__((__packed__))
BITMAPINFOHEADER;

// ---------------------------------------------------------------------------
// 4. RGBTRIPLE (3 bytes)
// ---------------------------------------------------------------------------
// Represents a single pixel. Note that BMP format stores colors in 
// BGR order (Blue, Green, Red), not RGB.
typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;
