#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int count = 0;
    unsigned char c[512] = {0};
    char imgname[8] = {0};
    FILE *img = NULL;

    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else if (strcmp(argv[1], "card.raw") != 0)
    {
        printf("Can't open. File name must be 'card.raw'\n");
        return 1;
    }

    // read the file
    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
    {
        printf("problem");
        return 1;
    }

    while (fread(c, sizeof(c), 1, f) == 1)
    {
        if ((c[0] == 0xff && c[1] == 0xd8 && c[2] == 0xff) && ((c[3] & 0xf0) == 0xe0))
        {
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf(imgname, "%03i.jpg", count);
            img = fopen(imgname, "w");
            if (img == NULL)
            {
                printf("can't open\n");
                return 1;
            }
            fwrite(c, sizeof(c), 1, img);
            count++;
        }
        else
        {
            if (img != NULL)
            {
                fwrite(c, sizeof(c), 1, img);
            }
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    
    if (f != NULL)
    {
        fclose(f);
    }
    
    return 0;

}
