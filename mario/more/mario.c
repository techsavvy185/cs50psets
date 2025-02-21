#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n=get_int("Height: ");
    }
    while (n<1);

    for(int i=0; i<n; i++)
    {
        for (int k=n; k>i; k--)
        {
            printf(" ");
        }
        for (int j=0; j<i+1; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int l=0; l<i+1; l++)
        {
            printf("#");
        }

        printf("\n");
    }
}
