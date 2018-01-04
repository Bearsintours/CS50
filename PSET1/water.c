#import <stdio.h>
#import <cs50.h>

int main(void){
    printf("Minutes:\n");
    int minutes;
    do{
      minutes = get_int();
    }
    while(minutes < 0);

    int bottles = minutes * 12;
    printf("Minutes: %i\n", minutes);
    printf("Bottles: %i\n", bottles);
}
