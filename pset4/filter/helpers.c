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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    RGBTRIPLE x;
    x.rgbtRed = 0;
    x.rgbtGreen = 0;
    x.rgbtBlue = 0;

    float gxr;
    float gxb;
    float gxg;
    float gyr;
    float gyb;
    float gyg;

    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(i == 0 && j == 0)
            {
                gxr = (2.0 * copy[i][j+1].rgbtRed) + (copy[i+1][j+1].rgbtRed);
                gxg = (2.0 * copy[i][j+1].rgbtGreen) + (copy[i+1][j+1].rgbtGreen);
                gxb = (2.0 * copy[i][j+1].rgbtBlue) + (copy[i+1][j+1].rgbtBlue);

                gyr = (2.0 * copy[i+1][j].rgbtRed) + (copy[i+1][j+1].rgbtRed);
                gyg = (2.0 * copy[i+1][j].rgbtGreen) + (copy[i+1][j+1].rgbtGreen);
                gyb = (2.0 * copy[i+1][j].rgbtBlue) + (copy[i+1][j+1].rgbtBlue);
            }

            else if(i == 0 && j == (width-1))
            {

                gxr = (-2.0 * copy[i][j-1].rgbtRed) + (-1.0 * copy[i+1][j-1].rgbtRed);
                gxg = (-2.0 * copy[i][j-1].rgbtGreen) + (-1.0 * copy[i+1][j-1].rgbtGreen);
                gxb = (-2.0 * copy[i][j-1].rgbtBlue) + (-1.0 * copy[i+1][j-1].rgbtBlue);

                gyr = (copy[i+1][j-1].rgbtRed) + (2.0 * copy[i+1][j].rgbtRed);
                gyg = (copy[i+1][j-1].rgbtGreen) + (2.0 * copy[i+1][j].rgbtGreen);
                gyb = (copy[i+1][j-1].rgbtBlue) + (2.0 * copy[i+1][j].rgbtBlue);
            }

            else if(j == 0 && i == (height-1))
            {

                gxr = (copy[i-1][j+1].rgbtRed) + (2.0 * copy[i][j+1].rgbtRed);
                gxg = (copy[i-1][j+1].rgbtGreen) + (2.0 * copy[i][j+1].rgbtGreen);
                gxb = (copy[i-1][j+1].rgbtBlue) + (2.0 * copy[i][j+1].rgbtBlue);

                gyr = (-2.0 * copy[i-1][j].rgbtRed) + (-1.0 * copy[i-1][j+1].rgbtRed);
                gyg = (-2.0 * copy[i-1][j].rgbtGreen) + (-1.0 * copy[i-1][j+1].rgbtGreen);
                gyb = (-2.0 * copy[i-1][j].rgbtBlue) + (-1.0 * copy[i-1][j+1].rgbtBlue);
            }

            else if(i == (height-1) && j == (width-1))
            {
                gxr = (-2.0 * copy[i][j-1].rgbtRed) + (-1.0 * copy[i-1][j-1].rgbtRed);
                gxg = (-2.0 * copy[i][j-1].rgbtGreen) + (-1.0 * copy[i-1][j-1].rgbtGreen);
                gxb = (-2.0 * copy[i][j-1].rgbtBlue) + (-1.0 * copy[i-1][j-1].rgbtBlue);

                gyr = (-2.0 * copy[i-1][j].rgbtRed) + (-1.0 * copy[i-1][j-1].rgbtRed);
                gyg = (-2.0 * copy[i-1][j].rgbtGreen) + (-1.0 * copy[i-1][j-1].rgbtGreen);
                gyb = (-2.0 * copy[i-1][j].rgbtBlue) + (-1.0 * copy[i-1][j-1].rgbtBlue);
            }

            else if(j == 0 && i > 0 && i < (height-1))
            {
                gxr = (copy[i-1][j+1].rgbtRed) + (2.0 * copy[i][j+1].rgbtRed) + (copy[i+1][j+1].rgbtRed);
                gxg = (copy[i-1][j+1].rgbtGreen) + (2.0 * copy[i][j+1].rgbtGreen) + (copy[i+1][j+1].rgbtGreen);
                gxb = (copy[i-1][j+1].rgbtBlue) + (2.0 * copy[i][j+1].rgbtBlue) + (copy[i+1][j+1].rgbtBlue);

                gyr = (-2.0 * copy[i-1][j].rgbtRed) + (-1.0 * copy[i-1][j+1].rgbtRed) + (2.0 * copy[i+1][j].rgbtRed) + (1.0 * copy[i+1][j+1].rgbtRed);
                gyg = (-2.0 * copy[i-1][j].rgbtGreen) + (-1.0 * copy[i-1][j+1].rgbtGreen) + (2.0 * copy[i+1][j].rgbtGreen) + (1.0 * copy[i+1][j+1].rgbtGreen);
                gyb = (-2.0 * copy[i-1][j].rgbtBlue) + (-1.0 * copy[i-1][j+1].rgbtBlue) + (2.0 * copy[i+1][j].rgbtBlue) + (1.0 * copy[i+1][j+1].rgbtBlue);
            }

            else if(i == 0 && j > 0 && j < (width-1))
            {
                gxr = (-2.0 * copy[i][j-1].rgbtRed) + (-1.0 * copy[i+1][j-1].rgbtRed) + (2.0 * copy[i][j+1].rgbtRed) + (1.0 * copy[i+1][j+1].rgbtRed);
                gxg = (-2.0 * copy[i][j-1].rgbtGreen) + (-1.0 * copy[i+1][j-1].rgbtGreen) + (2.0 * copy[i][j+1].rgbtGreen) + (1.0 * copy[i+1][j+1].rgbtGreen);
                gxb = (-2.0 * copy[i][j-1].rgbtBlue) + (-1.0 * copy[i+1][j-1].rgbtBlue) + (2.0 * copy[i][j+1].rgbtBlue) + (1.0 * copy[i+1][j+1].rgbtBlue);

                gyr = (copy[i+1][j-1].rgbtRed) + (2.0 * copy[i+1][j].rgbtRed) + (copy[i+1][j+1].rgbtRed);
                gyg = (copy[i+1][j-1].rgbtGreen) + (2.0 * copy[i+1][j].rgbtGreen) + (copy[i+1][j+1].rgbtGreen);
                gyb = (copy[i+1][j-1].rgbtBlue) + (2.0 * copy[i+1][j].rgbtBlue) + (copy[i+1][j+1].rgbtBlue);
            }

            else if(j == (width-1) && i > 0 && i < (height-1))
            {
                gxr = (-1.0 * copy[i-1][j-1].rgbtRed) + (-2.0 * copy[i][j-1].rgbtRed) + (-1.0 * copy[i+1][j-1].rgbtRed);
                gxg = (-1.0 * copy[i-1][j-1].rgbtGreen) + (-2.0 * copy[i][j-1].rgbtGreen) + (-1.0 * copy[i+1][j-1].rgbtGreen);
                gxb = (-1.0 * copy[i-1][j-1].rgbtBlue) + (-2.0 * copy[i][j-1].rgbtBlue) + (-1.0 * copy[i+1][j-1].rgbtBlue);

                gyr = (-2.0 * copy[i-1][j].rgbtRed) + (-1.0 * copy[i-1][j-1].rgbtRed) + (2.0 * copy[i+1][j].rgbtRed) + (1.0 * copy[i+1][j-1].rgbtRed);
                gyg = (-2.0 * copy[i-1][j].rgbtGreen) + (-1.0 * copy[i-1][j-1].rgbtGreen) + (2.0 * copy[i+1][j].rgbtGreen) + (1.0 * copy[i+1][j-1].rgbtGreen);
                gyb = (-2.0 * copy[i-1][j].rgbtBlue) + (-1.0 * copy[i-1][j-1].rgbtBlue) + (2.0 * copy[i+1][j].rgbtBlue) + (1.0 * copy[i+1][j-1].rgbtBlue);
            }

            else if(i == (height-1) && j > 0 && j < (width-1))
            {
                gxr = (-2.0 * copy[i][j-1].rgbtRed) + (-1.0 * copy[i-1][j-1].rgbtRed) + (2.0 * copy[i][j+1].rgbtRed) + (1.0 * copy[i-1][j+1].rgbtRed);
                gxg = (-2.0 * copy[i][j-1].rgbtGreen) + (-1.0 * copy[i-1][j-1].rgbtGreen) + (2.0 * copy[i][j+1].rgbtGreen) + (1.0 * copy[i-1][j+1].rgbtGreen);
                gxb = (-2.0 * copy[i][j-1].rgbtBlue) + (-1.0 * copy[i-1][j-1].rgbtBlue) + (2.0 * copy[i][j+1].rgbtBlue) + (1.0 * copy[i-1][j+1].rgbtBlue);

                gyr = (-1.0 * copy[i-1][j-1].rgbtRed) + (-2.0 * copy[i-1][j].rgbtRed) + (-1.0 * copy[i-1][j+1].rgbtRed);
                gyg = (-1.0 * copy[i-1][j-1].rgbtBlue) + (-2.0 * copy[i-1][j].rgbtBlue) + (-1.0 * copy[i-1][j+1].rgbtBlue);
                gyb = (-1.0 * copy[i-1][j-1].rgbtGreen) + (-2.0 * copy[i-1][j].rgbtGreen) + (-1.0 * copy[i-1][j+1].rgbtGreen);
            }

            else
            {
                gxr = (-1.0 * copy[i-1][j-1].rgbtRed) + (copy[i-1][j+1].rgbtRed) + (-1.0 * copy[i+1][j-1].rgbtRed) + (copy[i+1][j+1].rgbtRed) + (-2.0 * copy[i][j-1].rgbtRed) + (2.0 * copy[i][j+1].rgbtRed);
                gxg = (-1.0 * copy[i-1][j-1].rgbtGreen) + (copy[i-1][j+1].rgbtGreen) + (-1.0 * copy[i+1][j-1].rgbtGreen) + (copy[i+1][j+1].rgbtGreen) + (-2.0 * copy[i][j-1].rgbtGreen) + (2.0 * copy[i][j+1].rgbtGreen);
                gxb = (-1.0 * copy[i-1][j-1].rgbtBlue) + (copy[i-1][j+1].rgbtBlue) + (-1.0 * copy[i+1][j-1].rgbtBlue) + (copy[i+1][j+1].rgbtBlue) + (-2.0 * copy[i][j-1].rgbtBlue) + (2.0 * copy[i][j+1].rgbtBlue);

                gyr = (-1.0 * copy[i-1][j-1].rgbtRed) + (-2.0 * copy[i-1][j].rgbtRed) + (-1.0 * copy[i-1][j+1].rgbtRed) + (copy[i+1][j-1].rgbtRed) + (2.0 * copy[i+1][j].rgbtRed) + (copy[i+1][j+1].rgbtRed);
                gyg = (-1.0 * copy[i-1][j-1].rgbtGreen) + (-2.0 * copy[i-1][j].rgbtGreen) + (-1.0 * copy[i-1][j+1].rgbtGreen) + (copy[i+1][j-1].rgbtGreen) + (2.0 * copy[i+1][j].rgbtGreen) + (copy[i+1][j+1].rgbtGreen);
                gyb = (-1.0 * copy[i-1][j-1].rgbtBlue) + (-2.0 * copy[i-1][j].rgbtBlue) + (-1.0 * copy[i-1][j+1].rgbtBlue) + (copy[i+1][j-1].rgbtBlue) + (2.0 * copy[i+1][j].rgbtBlue) + (copy[i+1][j+1].rgbtBlue);
            }


            int a = round(sqrt(gxr * gxr + gyr * gyr));
            int b = round(sqrt(gxg * gxg + gyg * gyg));
            int c = round(sqrt(gxb * gxb + gyb * gyb));

            if (a < 255)
            {
                image[i][j].rgbtRed =  a;
            }
            else
            {
               image[i][j].rgbtRed = 255;
            }
            if(b < 255)
            {
                image[i][j].rgbtGreen = b;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if(c < 255)
            {
                image[i][j].rgbtBlue = c;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
    return;
}
