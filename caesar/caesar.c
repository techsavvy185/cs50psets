#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {

        int key = 0;

        string keystring = argv[1];
        bool k = true;

        while (k == true)
        {
            for (int i = 0; i < strlen(keystring); i++)
            {
                if (isdigit(keystring[i]))
                {
                    int n = (keystring[i] - 48);
                    key = (key * 10) + n;
                    k = true;
                }
                else
                {
                    k = false;
                    break;
                }
            }

            if (k == true)
            {
                string plaintext = get_string("plaintext:  ");
                char ciphertext[strlen(plaintext) + 1];
                ciphertext[strlen(plaintext)] = '\0';

                for (int i = 0; i < strlen(plaintext); i++)
                {
                    if (isalpha(plaintext[i]))
                    {
                        if (islower(plaintext[i]))
                        {
                            ciphertext[i] = ((plaintext[i] + key - 'a') % 26) + 'a';
                        }

                        else if (isupper(plaintext[i]))
                        {
                            ciphertext[i] = ((plaintext[i] + key - 'A') % 26) + 'A';
                        }
                    }
                    else if (isspace(plaintext[i]) || ispunct(plaintext[i]))
                    {
                        ciphertext[i] = plaintext[i];
                    }
                }

                printf("ciphertext: ");
                for (int i = 0; i < strlen(plaintext); i++)
                {
                    printf("%c", ciphertext[i]);
                }
                printf("\n");
                return 0;
            }
        }
        if (k == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
