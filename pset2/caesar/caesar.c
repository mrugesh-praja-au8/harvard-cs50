#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


int main(int argc,string argv[])
{
    if(argc==2 && isdigit(*argv[1]))
    {
    int k = atoi(argv[1]);

    if(k<0)
    {
        printf("key must be positive integer\n");
        return 1;
    }


    string s=get_string("plain Text: ");
    printf("ciphertext: ");

    for( int i=0; i< strlen(s); i++)
    {
        if(isupper(s[i]))
        {
            printf("%c",(s[i]-65+k)%26+65);
        }
        else if(islower(s[i]))
        {
            printf("%c",(s[i]-97+k)%26+97);
        }
        else
           {
               printf("%c",s[i]);
           }
    }
     printf("\n");
    return 0;
    }


    else
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
}