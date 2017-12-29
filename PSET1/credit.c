#import<stdio.h>
#import<cs50.h>

long long cc_num;
long long num;
long long digits = 0;
long long other_digits = 0;
int digit = 0;
int result;
int count = 0;

int main(){
    do{
        // prompt to ender cc number until valid
        printf("Enter credit card number: \n");
        cc_num = get_long_long();
    }
    while(cc_num <= 0);

    for(long long i = cc_num/10; i > 0; i = i/100){
        digit = i % 10;
        num = digit * 2;
        if(num > 9){
            num = num % 10 + ((num/10) %10);
        }
        digits += num;
    }

    for(long long j = cc_num; j > 0; j = j/100){
        other_digits += j % 10;
    }

    result = digits + other_digits;

    if(result % 10 == 0){
        int first_digit;
        int first2_digits;
        for (long long k = cc_num; k > 0; k = k/10){
            count++;

            if(k >=10 && k < 100){
                first2_digits = k;
            }
            if(k < 10){
                first_digit = k;
            }
        }
        // check if amex
        if(count == 15 && (first2_digits == 34 || first2_digits == 37)){
            printf("AMEX\n");
        }
        // check if mastercard
        else if(count == 16 && first2_digits >= 51 && first2_digits <= 55){
            printf("MASTERCARD\n");
        }
        // check if visa
        else if((count == 13 || count == 16) && first_digit == 4){
            printf("VISA\n");
        }
        else{
            printf("INVALID\n");
        }
    }
    else{
        printf("INVALID\n");
    }
    return 0;
}
