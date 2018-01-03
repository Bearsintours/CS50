#import <stdio.h>
#import <cs50.h>

int main(void)
{
    // create variables
    int height;
    int spaces;
    int blocks;

    // get input > 0 and <= 23
    do
    {
        printf("Pyramid height :\n");
        height = get_int();
    }
    while (height < 0 || height > 23);

    // iterate over pyramid height
    for (int i = 0; i < height; i++)
    {
        // for each row: print spaces
        for (spaces = height - 1; spaces > i; spaces--)
        {
            printf(" ");
        }
        // for each row: print blocks
        for (blocks = 0; blocks <= i + 1; blocks++)
        {
            printf("#");
        }
        // go to next line
        printf("\n");
    }
}
