/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n){

    // MAKE SURE WE HAVE AN ARRAY
    if(n < 0){
        return false;
    }

    int left = 0;
    int right = n-1;
    int m = (left + right) / 2;
    int l = n;

    // DO THIS WHILE ARRAY LENGTH > 0
    do{

        // IF VALUE IS FOUND ON THE START, LEFT OR MIDDLE OF THE ARRAY -> RETURN TRUE
        if(value == values[left] || value == values[right] || value == values[m]){
            return true;
        }

        // IF VALUE > NEW MIDDLE -> SEARCH RIGHT
        else if(value > values[m]){
            left = m + 1;
            m = (left + right) / 2;
            l = right - left;
        }

        // IF VALUE < NEW MIDDLE -> SEARCH LEFT
        else if (value < values[m]){
            right = m - 1;
            m = (left + right) / 2;
            l = right - left;
        }
    }
    while(l > 0);

    // IF VALUE NOT FOUND -> RETURN FALSE
    return false;
}

/**
 * Sorts array of n values.
 */

void sort(int values[], int n)
{

    int min, old_min, min_val;

    // ITERATE OVER ARRAY
    for(int i = 0; i < n; i++){
       min = i;

       // ITERATE OVER ARRAY FROM i+1 AND COMPARE EACH ELEMENT WITH ARRAY[i]
       for(int j = i+1; j < n; j++){
           if(values[j] < values[min]){
               min = j;
               min_val = values[j];
           }
        }

        // IF NEW MINIMUM VALUE FOUND -> SWAP VALUES
        if(min != i){
            old_min = values[i];
            values[i] = min_val;
            values[min] = old_min;
        }
    }
    return;
}
