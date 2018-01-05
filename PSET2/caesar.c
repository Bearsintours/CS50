#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]){
    if(argc != 2){
        printf("Please enter valid key\n");
        return 1;
    }
    else{
        int k = atoi(argv[1]);
        printf("plaintext: ");
        string p = get_string();
        char c;
        int index;
        printf("ciphertext: ");

        for(int i = 0, l = strlen(p); i < l; i++){
            if(p[i] >= 'a' && p[i] <= 'z'){
                index = p[i] - 97;
                c = 97 + (index + k) % 26;
                printf("%c",c);
            }
            else if(p[i] >= 'A' && p[i] <= 'Z'){
                index = p[i] - 65;
                c = 65 + (index + k) % 26;
                printf("%c",c);
            }
            else printf("%c", p[i]);
        }
        printf("\n");
        return 0;
    }
}
