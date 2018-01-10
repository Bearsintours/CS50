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

    for(int j = 0; j < strlen(argv[1]); j++){
        if(!isalpha(argv[1][j])){
            printf("Please enter valid key\n");
            return 1;
        }
    }

    string keys = argv[1];
    printf("plaintext: ");
    string p = get_string();
    char c;
    int index;
    int k;
    int keys_length = strlen(keys);
    printf("ciphertext: ");

    for(int i = 0, l = strlen(p); i < l; i++){
        k = keys[i % keys_length];
        k = tolower(k) - 97;
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
