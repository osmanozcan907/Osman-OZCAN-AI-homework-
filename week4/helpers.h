#include "helpers.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r = image[i][j].rgbtRed, g = image[i][j].rgbtGreen, b = image[i][j].rgbtBlue;
            
            int sRed = round(.393 * r + .769 * g + .189 * b);
            int sGreen = round(.349 * r + .686 * g + .168 * b);
            int sBlue = round(.272 * r + .534 * g + .131 * b);

            image[i][j].rgbtRed = (sRed > 255) ? 255 : sRed;
            image[i][j].rgbtGreen = (sGreen > 255) ? 255 : sGreen;
            image[i][j].rgbtBlue = (sBlue > 255) ? 255 : sBlue;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) copy[i][j] = image[i][j];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int r = -1; r <= 1; r++) {
                for (int c = -1; c <= 1; c++) {
                    int ni = i + r, nj = j + c;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                        sumR += copy[ni][nj].rgbtRed;
                        sumG += copy[ni][nj].rgbtGreen;
                        sumB += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumR / count);
            image[i][j].rgbtGreen = round(sumG / count);
            image[i][j].rgbtBlue = round(sumB / count);
        }
    }
}
