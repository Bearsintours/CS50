#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char *crypt(const char *key, const char *salt);

int main(int argc, char * argv[]){
    if(argc != 2){
        printf("Please enter valid password\n");
        return 1;
    }
    else{
        string hashed = argv[1];
        char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char test[4];
        for(int i = 0, l = strlen(letters); i < l; i++){
            test[0] = letters[i];
            for(int j = 0; i < l; j++){
                test[1] = letters[j];
                for(int k = 0; k < l; k++){
                    test[2] = letters[k];
                    for(int h = 0; h < l; h++){
                        test[3] = letters[h];
                        if(strcmp(hashed,crypt(test, "50")) == 0){
                          printf("Password: %s\n", test);
                          return 0;
                        }
                    }
                }
            }
        }
    }
}
