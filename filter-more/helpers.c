#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float counter = 1;
            float sumred = copy[i][j].rgbtRed;
            float sumblue = copy[i][j].rgbtBlue;
            float sumgreen = copy[i][j].rgbtGreen;
            if (j > 0)
            {
                counter += 1;
                sumred += copy[i][j - 1].rgbtRed;
                sumblue += copy[i][j - 1].rgbtBlue;
                sumgreen += copy[i][j - 1].rgbtGreen;
            }
            if (i > 0)
            {
                counter += 1;
                sumred += copy[i - 1][j].rgbtRed;
                sumblue += copy[i - 1][j].rgbtBlue;
                sumgreen += copy[i - 1][j].rgbtGreen;
            }
            if (i < (height - 1))
            {
                counter += 1;
                sumred += copy[i + 1][j].rgbtRed;
                sumblue += copy[i + 1][j].rgbtBlue;
                sumgreen += copy[i + 1][j].rgbtGreen;
            }
            if (j < (width - 1))
            {
                counter += 1;
                sumred += copy[i][j + 1].rgbtRed;
                sumblue += copy[i][j + 1].rgbtBlue;
                sumgreen += copy[i][j + 1].rgbtGreen;
            }
            if (i > 0 && j > 0)
            {
                counter += 1;
                sumred += copy[i - 1][j - 1].rgbtRed;
                sumblue += copy[i - 1][j - 1].rgbtBlue;
                sumgreen += copy[i - 1][j - 1].rgbtGreen;
            }
            if (i < (height - 1) && j < (width - 1))
            {
                counter += 1;
                sumred += copy[i + 1][j + 1].rgbtRed;
                sumblue += copy[i + 1][j + 1].rgbtBlue;
                sumgreen += copy[i + 1][j + 1].rgbtGreen;
            }
            if (i > 0 && j < (width - 1))
            {
                counter += 1;
                sumred += copy[i - 1][j + 1].rgbtRed;
                sumblue += copy[i - 1][j + 1].rgbtBlue;
                sumgreen += copy[i - 1][j + 1].rgbtGreen;
            }
            if (i < (height - 1) && j > 0)
            {
                counter += 1;
                sumred += copy[i + 1][j - 1].rgbtRed;
                sumblue += copy[i + 1][j - 1].rgbtBlue;
                sumgreen += copy[i + 1][j - 1].rgbtGreen;
            }
            int avgred = round((sumred) / counter);
            int avggreen = round((sumgreen) / counter);
            int avgblue = round((sumblue) / counter);

            image[i][j].rgbtRed = avgred;
            image[i][j].rgbtGreen = avggreen;
            image[i][j].rgbtBlue = avgblue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    int GxKernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int GyKernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < (height); i++)
    {
        for (int j = 0; j < (width); j++)
        {

            float Gxred = 0;
            float Gxgreen = 0;
            float Gxblue = 0;

            float Gyred = 0;
            float Gygreen = 0;
            float Gyblue = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if ((i + di) >= 0 && (i + di) < height && (j + dj) >= 0 && (j + dj) < width)
                    {
                        Gxred += copy[i + di][j + dj].rgbtRed * GxKernel[di + 1][dj + 1];
                    }
                }
            }
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if ((i + di) >= 0 && (i + di) < height && (j + dj) >= 0 && (j + dj) < width)
                    {
                        Gxgreen += copy[i + di][j + dj].rgbtGreen * GxKernel[di + 1][dj + 1];
                    }
                }
            }
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if ((i + di) >= 0 && (i + di) < height && (j + dj) >= 0 && (j + dj) < width)
                    {
                        Gxblue += copy[i + di][j + dj].rgbtBlue * GxKernel[di + 1][dj + 1];
                    }
                }
            }

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if ((i + di) >= 0 && (i + di) < height && (j + dj) >= 0 && (j + dj) < width)
                    {
                        Gyred += copy[i + di][j + dj].rgbtRed * GyKernel[di + 1][dj + 1];
                    }
                }
            }
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if ((i + di) >= 0 && (i + di) < height && (j + dj) >= 0 && (j + dj) < width)
                    {
                        Gygreen += copy[i + di][j + dj].rgbtGreen * GyKernel[di + 1][dj + 1];
                    }
                }
            }
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if ((i + di) >= 0 && (i + di) < height && (j + dj) >= 0 && (j + dj) < width)
                    {
                        Gyblue += copy[i + di][j + dj].rgbtBlue * GyKernel[di + 1][dj + 1];
                    }
                }
            }

            int Gred = round(sqrt(Gxred * Gxred + Gyred * Gyred));
            int Ggreen = round(sqrt(Gxgreen * Gxgreen + Gygreen * Gygreen));
            int Gblue = round(sqrt(Gxblue * Gxblue + Gyblue * Gyblue));

            image[i][j].rgbtRed = Gred > 255 ? 255 : Gred;
            image[i][j].rgbtGreen = Ggreen > 255 ? 255 : Ggreen;
            image[i][j].rgbtBlue = Gblue > 255 ? 255 : Gblue;
        }
    }
    return;
}
