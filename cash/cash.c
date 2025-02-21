#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n=get_int("Change owed: ");
    }

    while(n<1);

    int quarter=n/25;
    int rem=n%25;

    int dime=rem/10;
    rem%= 10;

    int nickel=rem/5;
    rem%=5;

    int total=quarter+dime+nickel+rem;
    printf("%d\n" , total);

}
