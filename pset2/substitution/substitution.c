#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool validate(string key);                   // to check key parameters
int main(int argc, string argv[])
{
    string key = argv[1];
    if (argc == 2 )                          //check cpmmand line
    {
       if (validate(key)==true)
       {
           string text = get_string("plain text:");
           printf("ciphertext:");


           for(int j = 0; j < strlen(text); j++)
           {
               if(isupper(text[j])!=0)
               {
                    printf("%c", toupper(key[(text[j]-65)]));
               }
               else if(islower(text[j])!=0)
               {
                    printf("%c", tolower(key[(text[j]-97)]));
               }
               else
               {
                   printf("%c", text[j]);
               }

           }
           printf("\n");
           return 0;
       }
       else
       {
           printf("Key must exact contain 26 different characters.\n");
           return 1;
       }

    }
    else
    {
        printf("Usage ./substitution key\n");
        return 1;
    }


}

bool validate( string key )
{
    if( strlen(key) == 26)
    {
        int match = 0;
        for ( char alpha = 'a'; alpha <= 'z'; alpha++)
        {
            for( int i = 0; i < 26; i++)
            {
                if( tolower(key[i]) == alpha)
                {
                    match++;
                    break;
                }
            }
        }
        if( match == 26)
        {
            return true;
        }
        else
        {

            return false;
            return 1;
        }

    }
    else
    {

        return false;
        return 1;
    }
}
