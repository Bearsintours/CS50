#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string name;
string initials;
char first_letter;

int main(void){

    printf("Full name:\n");
    name = get_string();

    int l = strlen(name);

    for (int i = 0; i < l; i++){

        if(i == 0 && name[i] != ' '){
            first_letter = name[i];
            printf("%c", toupper(first_letter));
        }

        if(name[i] == ' '){
            printf("%c", toupper(name[i+1]));
        }
    }
    printf("\n");
}
