#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool valid(int j[], int length);
int main(void)
{
    long number = get_long("Number: ");
    int length = (1 + log10(number));
    int ind[length];
    long d;
    long x = pow(10, length - 1);
    for (int i = 0; i <= length - 1; i++) 
    {
        //ind[i] = (number % d);
        ind[i] = number / x;
        number = number % x;
        //d *= 10;
        x /= 10;
        //printf("%i",ind[i]);
    }
    // check amex
    if (length == 15 && ind[0] == 3 && (ind[1] == 4 || ind[1] == 7) && valid(ind, length) == true)
    {
        printf("AMEX\n");
    }
    // check mastercard
    else if (length == 16 && ind[0] == 5 && (ind[1] >= 1 && ind[1] <= 5) && valid(ind, length) == true)
    {
        printf("MASTERCARD\n");
    }
    // check visa
    else if ((length == 13 || length == 16) && (ind[0] == 4) && valid(ind, length) == true)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
// printf("%li\n%i\n",number, length);
    // check validity
}
bool valid(int j[], int length)
{
    int x = 0;
    for (int i = length - 2; i >= 0; i = i - 2)
    {
        if (2 * j[i] < 9)
        {
            x += (2 * j[i]);
        }
        else
        {
            x += (2 * j[i] / 10);
            x += ((2 * j[i]) % 10);
        }
    }
    for (int i = length - 1; i >= 0; i = i - 2)
    {
        x += j[i];
    }
    if ((x % 10) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}  