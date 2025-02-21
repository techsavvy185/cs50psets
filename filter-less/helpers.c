#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg =round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                  .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                    .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                   .131 * image[i][j].rgbtBlue);
            sepiaRed = sepiaRed > 255 ? 255 : sepiaRed;
            sepiaGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            sepiaBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

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

    for (int i=0; i<height; i++)
    {
        for (int j=0;j<width; j++)
        {
            copy[i][j]=image[i][j];
        }
    }
    for (int i=0; i<height; i++)
    {
        for (int j=0;j<width; j++)
        {
            float counter=1;
            float sumred = copy[i][j].rgbtRed;
            float sumblue = copy[i][j].rgbtBlue;
            float sumgreen = copy[i][j].rgbtGreen;
            if (j>0)
            {
                counter+=1;
                sumred+=copy[i][j-1].rgbtRed;
                sumblue+=copy[i][j-1].rgbtBlue;
                sumgreen+=copy[i][j-1].rgbtGreen;
            }
            if (i>0)
            {
                counter+=1;
                sumred+=copy[i-1][j].rgbtRed;
                sumblue+=copy[i-1][j].rgbtBlue;
                sumgreen+=copy[i-1][j].rgbtGreen;

            }
            if (i<(height-1))
            {
                counter+=1;
                sumred+=copy[i+1][j].rgbtRed;
                sumblue+=copy[i+1][j].rgbtBlue;
                sumgreen+=copy[i+1][j].rgbtGreen;
            }
            if (j<(width-1))
            {
                counter+=1;
                sumred+=copy[i][j+1].rgbtRed;
                sumblue+=copy[i][j+1].rgbtBlue;
                sumgreen+=copy[i][j+1].rgbtGreen;
            }
            if (i>0 && j>0)
            {
                counter+=1;
                sumred+=copy[i-1][j-1].rgbtRed;
                sumblue+=copy[i-1][j-1].rgbtBlue;
                sumgreen+=copy[i-1][j-1].rgbtGreen;
            }
            if (i<(height-1)&&j<(width-1))
            {
                counter+=1;
                sumred+=copy[i+1][j+1].rgbtRed;
                sumblue+=copy[i+1][j+1].rgbtBlue;
                sumgreen+=copy[i+1][j+1].rgbtGreen;
            }
            if (i>0 && j<(width-1))
            {
                counter+=1;
                sumred+=copy[i-1][j+1].rgbtRed;
                sumblue+=copy[i-1][j+1].rgbtBlue;
                sumgreen+=copy[i-1][j+1].rgbtGreen;
            }
            if (i<(height-1) && j>0)
            {
                counter+=1;
                sumred+=copy[i+1][j-1].rgbtRed;
                sumblue+=copy[i+1][j-1].rgbtBlue;
                sumgreen+=copy[i+1][j-1].rgbtGreen;
            }
            int avgred=round((sumred)/counter);
            int avggreen=round((sumgreen)/counter);
            int avgblue=round((sumblue)/counter);

            image[i][j].rgbtRed=avgred;
            image[i][j].rgbtGreen=avggreen;
            image[i][j].rgbtBlue=avgblue;
        }
    }


    return;
}
