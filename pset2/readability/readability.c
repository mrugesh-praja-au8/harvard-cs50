#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int main(void)
{
    string text=get_string("Text: ");
    int letter_count=strlen(text);

    int letter=0;
    int word=1;
    int sentence=0;

    for(int i=0;i<letter_count;i++)
    {
        if(isalpha(text[i]))
        {
            letter++;
        }

        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentence++;
        }

        if(isalpha(text[i+1]) && isspace(text[i]))
        {
            word++;
        }

    }

    if(letter==0)
    {
        word=0;
    }

    float L=100*(float)letter/word;
    float S=100*(float)sentence/word;
    float grade = (0.0588*L)-(0.296*S)-15.8;

    int index=round(grade);
    if(index>=1 && index<=16)
    {
        printf("Grade %i\n",index);
    }
    else if(index<1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}