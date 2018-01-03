#import <stdio.h>
#import <cs50.h>

int main(void){

    int height;
    int spaces;
    int blocks;

    do{
        printf("Pyramid height :\n");
        height = get_int();
    }
    while (height < 0 || height > 23);

    for(int i = 0; i < height; i++){

        for (spaces = height-1; spaces > i; spaces--){
           printf(" ");
        }
        for (blocks = 0; blocks <= i; blocks++){
            printf("#");
        }
        printf("  ");
        for (blocks = 0; blocks <= i; blocks++){
            printf("#");
        }
     printf("\n");
    }
}
