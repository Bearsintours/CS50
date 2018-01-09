#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void){

    printf("Full name:\n");
    string name = get_string();
    int l = strlen(name);
    char first_letter;

    for (int i = 0; i < l; i++){

        if(i == 0 && name[i] != ' '){
            first_letter = name[i];
            printf("%c", toupper(first_letter));
        }
        if(name[i] == ' '){
            if(name[i+1] != ' ' && name[i+1] != '\0'){
                printf("%c", toupper(name[i+1]));
            }
        }
    }
    printf("\n");
}
