#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2 ; j++)
        {
            // making temp's
            int tempRed = image[i][j].rgbtRed;
            int tempBlue = image[i][j].rgbtBlue;
            int tempGreen = image[i][j].rgbtGreen;
            // the first pixel
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            // the second pixel
            image[i][width - j - 1].rgbtRed = tempRed;
            image[i][width - j - 1].rgbtGreen = tempGreen;
            image[i][width - j - 1].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bool isUp = false, isDown = false, isLeft = false, isRight = false;
            double counter = 1;
            if (i != 0)
            {
                isUp = true;
            }
            if (i != height - 1)
            {
                isDown = true;
            }
            if (j != 0)
            {
                isLeft = true;
            }
            if (j != width - 1)
            {
                isRight = true;
            }
            // Calculating Avg's
            int avgRed = 0, avgBlue = 0, avgGreen = 0;
            if (isUp)
            {
                avgRed += image[i - 1][j].rgbtRed;
                avgBlue += image[i - 1][j].rgbtBlue;
                avgGreen += image[i - 1][j].rgbtGreen;
                counter++;
                if (isLeft)
                {
                    avgRed += image[i - 1][j - 1].rgbtRed;
                    avgBlue += image[i - 1][j - 1].rgbtBlue;
                    avgGreen += image[i - 1][j - 1].rgbtGreen;
                    counter++;
                }
                if (isRight)
                {
                    avgRed += image[i - 1][j + 1].rgbtRed;
                    avgBlue += image[i - 1][j + 1].rgbtBlue;
                    avgGreen += image[i - 1][j + 1].rgbtGreen;
                    counter++;
                }
            }
            if (isDown)
            {
                avgRed += image[i + 1][j].rgbtRed;
                avgBlue += image[i + 1][j].rgbtBlue;
                avgGreen += image[i + 1][j].rgbtGreen;
                counter++;
                if (isLeft)
                {
                    avgRed += image[i + 1][j - 1].rgbtRed;
                    avgBlue += image[i + 1][j - 1].rgbtBlue;
                    avgGreen += image[i + 1][j - 1].rgbtGreen;
                    counter++;
                }
                if (isRight)
                {
                    avgRed += image[i + 1][j + 1].rgbtRed;
                    avgBlue += image[i + 1][j + 1].rgbtBlue;
                    avgGreen += image[i + 1][j + 1].rgbtGreen;
                    counter++;
                }
            }
            if (isLeft)
            {
                avgRed += image[i][j - 1].rgbtRed;
                avgBlue += image[i][j - 1].rgbtBlue;
                avgGreen += image[i][j - 1].rgbtGreen;
                counter++;
            }
            if (isRight)
            {
                avgRed += image[i][j + 1].rgbtRed;
                avgBlue += image[i][j + 1].rgbtBlue;
                avgGreen += image[i][j + 1].rgbtGreen;
                counter++;
            }
            avgRed += image[i][j].rgbtRed;
            avgBlue += image[i][j].rgbtBlue;
            avgGreen += image[i][j].rgbtGreen;
            // Calculating final result for the pixel
            temp[i][j].rgbtRed = round(avgRed / counter);
            temp[i][j].rgbtBlue = round(avgBlue / counter);
            temp[i][j].rgbtGreen = round(avgGreen / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // make temp picture
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // make bools to detect corners
            bool isUp = false, isDown = false, isLeft = false, isRight = false;
            double Gx_red = 0, Gy_red = 0;
            double Gx_blue = 0, Gy_blue = 0;
            double Gx_green = 0, Gy_green = 0;
            // haha
            if (i != 0)
            {
                isUp = true;
            }
            if (i != height - 1)
            {
                isDown = true;
            }
            if (j != 0)
            {
                isLeft = true;
            }
            if (j != width - 1)
            {
                isRight = true;
            }
            // Calculating Avg's
            int avgRed = 0, avgBlue = 0, avgGreen = 0;
            if (isUp)
            {
                // UP Gx
                Gx_red += image[i - 1][j].rgbtRed * 0;
                Gx_blue += image[i - 1][j].rgbtBlue * 0;
                Gx_green += image[i - 1][j].rgbtGreen * 0;
                // UP Gy
                Gy_red += image[i - 1][j].rgbtRed * -2;
                Gy_blue += image[i - 1][j].rgbtBlue * -2;
                Gy_green += image[i - 1][j].rgbtGreen * -2;
                if (isLeft)
                {
                    // UP_Left Gx
                    Gx_red += image[i - 1][j - 1].rgbtRed * -1;
                    Gx_blue += image[i - 1][j - 1].rgbtBlue * -1;
                    Gx_green += image[i - 1][j - 1].rgbtGreen * -1;
                    // UP_Left Gy
                    Gy_red += image[i - 1][j - 1].rgbtRed * -1;
                    Gy_blue += image[i - 1][j - 1].rgbtBlue * -1;
                    Gy_green += image[i - 1][j - 1].rgbtGreen * -1;
                }
                if (isRight)
                {
                    // UP_Right Gx
                    Gx_red += image[i - 1][j + 1].rgbtRed;
                    Gx_blue += image[i - 1][j + 1].rgbtBlue;
                    Gx_green += image[i - 1][j + 1].rgbtGreen;
                    // UP_Right Gy
                    Gy_red += image[i - 1][j + 1].rgbtRed * -1;
                    Gy_blue += image[i - 1][j + 1].rgbtBlue * -1;
                    Gy_green += image[i - 1][j + 1].rgbtGreen * -1;
                }
            }
            if (isDown)
            {
                // Down Gx
                /* Gx_red += image[i + 1][j].rgbtRed;
                 Gx_blue += image[i + 1][j].rgbtBlue;
                 Gx_green += image[i + 1][j].rgbtGreen;*/
                // Down Gy
                Gy_red += image[i + 1][j].rgbtRed * 2;
                Gy_blue += image[i + 1][j].rgbtBlue * 2;
                Gy_green += image[i + 1][j].rgbtGreen * 2;
                if (isLeft)
                {
                    // Down_Left Gx
                    Gx_red += image[i + 1][j - 1].rgbtRed * -1;
                    Gx_blue += image[i + 1][j - 1].rgbtBlue * -1;
                    Gx_green += image[i + 1][j - 1].rgbtGreen * -1;
                    // Down_Left Gy
                    Gy_red += image[i + 1][j - 1].rgbtRed;
                    Gy_blue += image[i + 1][j - 1].rgbtBlue;
                    Gy_green += image[i + 1][j - 1].rgbtGreen;
                }
                if (isRight)
                {
                    // Down_Right Gx
                    Gx_red += image[i + 1][j + 1].rgbtRed;
                    Gx_blue += image[i + 1][j + 1].rgbtBlue;
                    Gx_green += image[i + 1][j + 1].rgbtGreen;
                    // Down_Right Gy
                    Gy_red += image[i + 1][j + 1].rgbtRed;
                    Gy_blue += image[i + 1][j + 1].rgbtBlue;
                    Gy_green += image[i + 1][j + 1].rgbtGreen;
                }
            }
            if (isLeft)
            {
                // Left Gx
                Gx_red += image[i][j - 1].rgbtRed * -2;
                Gx_blue += image[i][j - 1].rgbtBlue * -2;
                Gx_green += image[i][j - 1].rgbtGreen * -2;
                // Left Gy
            }
            if (isRight)
            {
                // Right Gx
                Gx_red += image[i][j + 1].rgbtRed * 2;
                Gx_blue += image[i][j + 1].rgbtBlue * 2;
                Gx_green += image[i][j + 1].rgbtGreen * 2;
                // Right Gy
            }

            // Calculating final result for the pixel
            int temp1 = round(sqrt((Gx_red * Gx_red) + (Gy_red * Gy_red)));
            if (temp1 > 255)
            {
                temp[i][j].rgbtRed = 255;
            }
            else
            {
                temp[i][j].rgbtRed = temp1;
            }
            temp1 = round(sqrt((Gx_blue * Gx_blue) + (Gy_blue * Gy_blue)));
            if (temp1 > 255)
            {
                temp[i][j].rgbtBlue = 255;
            }
            else
            {
                temp[i][j].rgbtBlue = temp1;
            }
            temp1 = round(sqrt((Gx_green * Gx_green) + (Gy_green * Gy_green)));
            if (temp1 > 255)
            {
                temp[i][j].rgbtGreen = 255;
            }
            else
            {
                temp[i][j].rgbtGreen = temp1;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}
