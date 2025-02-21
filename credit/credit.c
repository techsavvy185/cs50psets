#include <stdio.h>
#include <cs50.h>

int coun(long a)
{
    int counter=0;
    while (a>0)
    {
        a/=10;
        counter=counter+1;
    }
    return counter;
}

int checksum(long b)
{
    int f=coun(b);
    int i;
    int sum1=0;
    int sum2=0;
    for (i=0; i<f; i=i+2)
    {
        int r=b%10;
        sum1=sum1+r;
        b=b/10;

        int s=b%10;
        int p=2*s;
        b=b/10;
        p=(p/10)+(p%10);
        sum2=sum2+p;
    }
    int sum=sum1+sum2;
    return sum;
}

int main(void)
{
    long n;
    n=get_long("Number: ");
    int check=checksum(n);
    int count=coun(n);

    if((count==15 && n/10000000000000==34 && check%10==0)||(count==15 && n/10000000000000==37 && check%10==0))
    {
        printf("AMEX\n");
    }

    else if((count==16 && n/100000000000000==51 && check%10==0)||(count==16 && n/100000000000000==52 && check%10==0)||(count==16 && n/100000000000000==53 && check%10==0)||(count==16 && n/100000000000000==54 && check%10==0)||(count==16 && n/100000000000000==55 && check%10==0)||(count==16 && n/100000000000000==22 && check%10==0))
    {
        printf("MASTERCARD\n");
    }

    else if((count==13 && n/1000000000000==4 && check%10==0)||(count==16 && n/1000000000000000==4 && check%10==0))
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }


}
