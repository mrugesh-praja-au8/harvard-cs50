#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(image[i][j].rgbtBlue == image[i][j].rgbtGreen == image[i][j].rgbtRed)
            {
                int a = 1;
            }

            else
            {
            avg = 1.0 * (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtRed = round(avg);
            image[i][j].rgbtGreen = round(avg);
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float x = (.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue);
            float y = (.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue);
            float z = (.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue);

             if (y >= 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            image[i][j].rgbtGreen = roundf(y);
             if (x >= 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            image[i][j].rgbtRed = roundf(x);
            if (z >= 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            image[i][j].rgbtBlue = roundf(z);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        int k;
        int l;
        int n;
        int m = width;
        for(int j = 0;j < m; j++, m--)
        {
            k = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][m-1].rgbtBlue;
            image[i][m-1].rgbtBlue = k;

            l = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][m-1].rgbtRed;
            image[i][m-1].rgbtRed = l;

            n = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][m-1].rgbtGreen;
            image[i][m-1].rgbtGreen = n;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ogImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ogImage[i][j] = image[i][j];
        }
    }

    for (int i = 0, red, green, blue, counter; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = green = blue = counter = 0;

            if (i >= 0 && j >= 0)
            {
                red += ogImage[i][j].rgbtRed;
                green += ogImage[i][j].rgbtGreen;
                blue += ogImage[i][j].rgbtBlue;
                counter++;
            }
            if (i >= 0 && j - 1 >= 0)
            {
                red += ogImage[i][j-1].rgbtRed;
                green += ogImage[i][j-1].rgbtGreen;
                blue += ogImage[i][j-1].rgbtBlue;
                counter++;
            }
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                red += ogImage[i][j+1].rgbtRed;
                green += ogImage[i][j+1].rgbtGreen;
                blue += ogImage[i][j+1].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j >= 0)
            {
                red += ogImage[i-1][j].rgbtRed;
                green += ogImage[i-1][j].rgbtGreen;
                blue += ogImage[i-1][j].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                red += ogImage[i-1][j-1].rgbtRed;
                green += ogImage[i-1][j-1].rgbtGreen;
                blue += ogImage[i-1][j-1].rgbtBlue;
                counter++;
            }
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                red += ogImage[i-1][j+1].rgbtRed;
                green += ogImage[i-1][j+1].rgbtGreen;
                blue += ogImage[i-1][j+1].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                red += ogImage[i+1][j].rgbtRed;
                green += ogImage[i+1][j].rgbtGreen;
                blue += ogImage[i+1][j].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                red += ogImage[i+1][j-1].rgbtRed;
                green += ogImage[i+1][j-1].rgbtGreen;
                blue += ogImage[i+1][j-1].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                red += ogImage[i+1][j+1].rgbtRed;
                green += ogImage[i+1][j+1].rgbtGreen;
                blue += ogImage[i+1][j+1].rgbtBlue;
                counter++;
            }

            image[i][j].rgbtRed = round(red / (counter * 1.0));
            image[i][j].rgbtGreen = round(green / (counter * 1.0));
            image[i][j].rgbtBlue = round(blue / (counter * 1.0));
        }
    }

    return;
}