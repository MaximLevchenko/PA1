#include <stdio.h>
#include <math.h>
#define MAX_SIZE 100 //define max size for the array(because we are in C and we cannot dynamically allocate)
/** 
 * @param accepts size of the current number, numeric system we count in
 * @returns the count of digits in the previous range of the size 
*/
long long int findPreviousCountDigits(long long int size, long long int numericSystem)
{ //function to find the count of digits in the previous range of size
    long long int previous_size = size - 1, times = 2, previous_count_digits = (numericSystem - 1);
    while (times <= previous_size)
    {
        previous_count_digits = previous_count_digits + pow(numericSystem, times - 1) * (numericSystem - 1) * times;
        times++;
    }
    return previous_count_digits;
}
/** 
 * @param accepts position we entered in the console, numeric system we count in and 3 pointers we want to be global in future calculations
 * @returns the size of the current number we point to
*/
long long int findCurrentSize(long long int position, long long int numericSystem, long long int *count, long long int *number_count, long long int *max_number)
{ //function to find the size of the number we point on
    long long int count_digits = (numericSystem - 1), temp = (numericSystem - 1);

    long long int current_size = 1;
    while (count_digits < position)
    {
        current_size++;
        count_digits = count_digits + pow(numericSystem, current_size - 1) * (numericSystem - 1) * current_size;
        temp = temp + pow(numericSystem, current_size - 1) * (numericSystem - 1);
    }

    *count = count_digits;                                    //number digits of the current and previous ranges of sizes
    *number_count = (count_digits - position) / current_size; //number counting from the end range of the size
    *max_number = temp;                                       //max number in the current range of the size
    return current_size;
}
/** 
 * @param accepts number we want to convert, size of the number and numeric system we entered in the console
 * @returns nothing but prints out the array
*/
void convertToCurrentNumberSystem(long long int number_to_convert, long long int size, long long int number_system)
{
    long long int number = number_to_convert;
    int array_to_convert[MAX_SIZE]; //array should exactly contain
    for (int i = 0; i < size; i++)
    {
        array_to_convert[i] = number % number_system;
        number = number / number_system;
    }
    for (int j = size - 1; j >= 0; j--) //reversing an array
    {
        if (array_to_convert[j] > 9) //if there is a DIGIT bigger then 9 in the array, then it gets converted according to ASCII table
            printf("%c", 'a' + (array_to_convert[j] - 10));
        else
            printf("%d", array_to_convert[j]);
    }
    printf("\n");
}
int main()
{
    long long int total_count_digits, number_count_end, max_number;
    long long int position = 0, numericSystem = 0, size = 0, read = 0,
                  previous_count_digits = 0, number_found = 0, arrow_position = 0;
    printf("Pozice a soustava:\n");
    //minimize error inputs
    while ((read = scanf("%lld %lld", &position, &numericSystem)) != EOF) //until we have not pressed CTRL+D, we will continue the input
    {
        if (read != 2 || numericSystem > 36 || numericSystem < 2 || position < 0)
        {
            printf("Nespravny vstup.\n");
            return 1; //error
        }
        size = findCurrentSize(position, numericSystem, &total_count_digits, &number_count_end, &max_number);
        previous_count_digits = findPreviousCountDigits(size, numericSystem);
        number_found = max_number - number_count_end;               // the exact number we found
        arrow_position = (position - previous_count_digits) % size; // number, which points on the arrow position
        if (arrow_position == 0)                                    //if arrow position is 0, then it should point to the last digit
            arrow_position = size;
        if (numericSystem != 10) //if the numeric system is other than 10, then we should convert it
            convertToCurrentNumberSystem(number_found, size, numericSystem);
        else
            printf("%lld\n", number_found);
        for (int space = 0; space < (arrow_position - 1); space++)
        {
            printf(" ");
        }
        printf("^\n");
        printf("%lld is the amount of digits in the previous range\n", previous_count_digits);
        printf("%lld is the amount of digits in the current and previous ranges we point to\n", total_count_digits);
    }
    // printf("%lld is the size of the number we point on\n", size);
    // printf("%lld number counting from the end range of the size\n", number_count_end);
    // printf("%lld max number in the current range of the size\n", max_number);
    // printf("number we want to find is: %lld\n", number_found);
    return 0;
}