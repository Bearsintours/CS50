#import <stdio.h>
#import <cs50.h>
#include <math.h>

float change;
int coins = 0;

int main (void){
    do {
        printf("What is the change owed?\n");
        change = get_float();
    }
    while(change <= 0);

    change = roundf(change*100);

    while(change >= 25){
        coins++;
        change -= 25;
    }
    while(change >= 10){
        coins++;
        change -= 10;
    }
    while(change >= 5){
        coins++;
        change -= 5;
    }
    while(change >= 1){
        coins++;
        change -= 1;
    }

    printf("%i\n",coins);
}
