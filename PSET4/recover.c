#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // insure proper usage
    if(argc != 2){
        fprintf(stderr,"Usage: ./recover file\n");
        return 1;
    }

    // remember file name
    char *raw = argv[1];

    // open input file
    FILE *file = fopen(raw,"r");

    if(file == NULL){
        fprintf(stderr,"could not open %s\n", raw);
        return 2;
    }

    // create new file
    FILE *img = NULL;

    //create buffer
    BYTE buffer[512];

    // create counter to keep track of number of JPEG found
    int counter = 0;

    // read each block of 512 bytes until EOF
    while(fread(buffer, 1, 512, file) == 512){

        // check for JPEG header pattern
        if(buffer[0] == 0xff && buffer[1] == 0xd8
        && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){

            // if already reading JPEG -> close img before opening new one
            if(counter != 0){
                fclose(img);
            }

            // open new jpg file
            char pic[8];
            sprintf(pic, "%03i.jpg", counter);
            img = fopen(pic, "w");

            // write on new file
            fwrite(buffer, 1, 512, img);
            counter++;
        }

        // write next block to same img if no new JPEG header pattern found
        else if(img != NULL){
            fwrite(buffer, 1, 512, img);
        }
    }

    // close infile
    fclose(file);

    // close outfile
     fclose(img);
}
