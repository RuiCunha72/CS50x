#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;
            float average = (blue+green+red)/(float)3;
            BYTE new_pixel = (average + 0.5);
            image[i][j].rgbtBlue = new_pixel;
            image[i][j].rgbtGreen = new_pixel;
            image[i][j].rgbtRed = new_pixel;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        int count = 0;
        for (int j = width - 1; j >= 0; j--)
        {
            image[i][count] = tmp[i][j];
            count++;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_blue = 0;
            int sum_green = 0;
            int sum_red = 0;
            int count = 0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX =  i + x;
                    int currentY = j + y;
                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        //Do nothing
                    }
                    else
                    {
                        sum_blue += image[currentX][currentY].rgbtBlue;
                        sum_green += image[currentX][currentY].rgbtGreen;
                        sum_red += image[currentX][currentY].rgbtRed;
                        count++;
                    }
                }
            }

            float average_blue = sum_blue / (float) count;
            float average_green = sum_green / (float) count;
            float average_red = sum_red / (float) count;
            BYTE new_pixel_blue = (average_blue + 0.5);
            BYTE new_pixel_green = (average_green + 0.5);
            BYTE new_pixel_red = (average_red + 0.5);
            tmp[i][j].rgbtBlue = new_pixel_blue;
            tmp[i][j].rgbtGreen = new_pixel_green;
            tmp[i][j].rgbtRed = new_pixel_red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        int count = 0;
        for (int j = 0; j < width; j++)
        {
            image[i][count] = tmp[i][j];
            count++;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_blueGx = 0;
            int sum_greenGx = 0;
            int sum_redGx = 0;
            int sum_blueGy = 0;
            int sum_greenGy = 0;
            int sum_redGy = 0;

            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    int currentX =  i - 1 + x;
                    int currentY = j - 1 + y;

                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }

                    sum_blueGx = sum_blueGx + (image[currentX][currentY].rgbtBlue * Gx[x][y]);
                    sum_greenGx = sum_greenGx + (image[currentX][currentY].rgbtGreen * Gx[x][y]);
                    sum_redGx = sum_redGx + (image[currentX][currentY].rgbtRed * Gx[x][y]);
                    sum_blueGy = sum_blueGy + (image[currentX][currentY].rgbtBlue * Gy[x][y]);
                    sum_greenGy = sum_greenGy + (image[currentX][currentY].rgbtGreen * Gy[x][y]);
                    sum_redGy = sum_redGy + (image[currentX][currentY].rgbtRed * Gy[x][y]);

                }

                int blue = round(sqrt(pow(sum_blueGx,2) + pow(sum_blueGy,2)));
                int green = round(sqrt(pow(sum_greenGx,2) + pow(sum_greenGy,2)));
                int red = round(sqrt(pow(sum_redGx,2) + pow(sum_redGy,2)));

                if (blue > 255)
                {
                    blue = 255;
                }

                if (green > 255)
                {
                    green = 255;
                }

                if (red > 255)
                {
                    red = 255;
                }

                tmp[i][j].rgbtBlue = blue;
                tmp[i][j].rgbtGreen = green;
                tmp[i][j].rgbtRed = red;
            }
        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
        }
    }
}
