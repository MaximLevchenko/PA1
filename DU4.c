#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 1000000 //max array for all connections 
#define MAX_USER 100000 //max array for unique users 
#define HALF_SIZE 500000 //size for the final range array 
/**
 * @brief 
 * Counts unique elements in the array 
 * @param[in] array accepts array in which we want to count unique elements
 * @param[in] length accepts length of the array 
 * @returns count of the unique elements in the array 
 */
int countUnique(int array[], int length)
{
    int res = 0, temp = 0;
    while (temp < length) //iterating through all length of an array
    {
        while (temp < length - 1 && array[temp] == array[temp + 1])
        {
            temp += 1;
        }
        res += 1;
        temp += 1;
    }
    return res;
}

/**
 * Quicksort comparator function.
 * 
 * Used to compare integer objects.
 *  	
 * @returns Returns ​a negative integer value if the first argument is less than the second,
 *  a positive integer value if the first argument is greater than the second
 *  and zero if the arguments are equivalent. 
 */
int compare(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

/**
 * @brief 
 * Makes an array in the given range
 * @param[in] array accepts array with all visits
 * @param[in] start_range starting point for making new array 
 * @param[in] end_range end point for making new array
 */
void makeArrayInRange(int array[], int start_range, int end_range)
{
    int arr_range[HALF_SIZE], //array to store all visits in the given range
        unique_count = 0, length = 0;
    length = end_range - start_range + 1;
    for (int n = 0; n < length; n++, start_range++) //iterate through the array
        arr_range[n] = array[start_range];
    qsort(arr_range, length, sizeof(int), compare); //quick sort
    unique_count = countUnique(arr_range, length);  //count of the unique elements in the range
    printf("> %d / %d\n", unique_count, length);    //how many uniques in range
}

/**
 * @brief 
 * Prints out number of visits
 * @param[in] visit_number accepts number to print out the amount of visits
 */
void printVisits(int visit_number)
{
    if (visit_number == 1) //validation of the input
        printf("> prvni navsteva\n");
    else
        printf("> navsteva #%d\n", visit_number);
}

/**
 * @brief 
 * Validation of the input for '+'
 * @param[in] id_guest id of the new user 
 * @param[in] count_elements count of the users
 * @returns 1 if validated successfully, otherwise 0
 */
bool checkForPlus(int id_guest, int count_elements)
{

    if (id_guest < 0 || id_guest > 99999 || count_elements > 1000000) //validation of the input
        return false;
    return true;
}
/**
 * @brief 
 * Validation of the input for '?'
 * 
 * @param[in] count_elements length of the array
 * @param[in] from start of the range
 * @param[in] to end of the range
 * @returns 1 if validated successfully, otherwise 0
 */
bool checkForQuestion(int count_elements, int from, int to)
{
    if (to >= count_elements || from > to || from < 0 || to < 0) //validation of the input
        return false;
    return true;
}

int main(int argc, char *argv[])
{
    int id_guest = 0, start_range = 0, end_range = 0,
        id_position = 0, count_elements = 0, read = 0, visit_number = 0;
    char sign;
    int arr_unique_user[MAX_USER]; //array for unique connections
    int arr_full[MAX_SIZE];        //array for all connections
    printf("Pozadavky:\n");
    while ((read = scanf(" %c", &sign)) != EOF && read == 1)
    {
        switch (sign)
        {
        case '+': //if user have entered "+", we execute this part
        {
            if (scanf(" %d", &id_guest) != 1 || !checkForPlus(id_guest, count_elements)) // checking if the char is valid
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
            arr_unique_user[id_guest] += 1; //iterating the pos. of the corresponding user id
            arr_full[id_position] = id_guest;
            visit_number = arr_unique_user[id_guest]; //the amount of existing connections
            printVisits(visit_number);                //printing the amount of visits
            id_position++, count_elements++;
            break;
        }
        case '?': //if user have entered "?", we execute this part
        {
            if (scanf("%d %d", &start_range, &end_range) != 2 ||               // checking if the char is valid
                checkForQuestion(count_elements, start_range, end_range) == 0) //validation of the input
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
            makeArrayInRange(arr_full, start_range, end_range); // making new array in the given range
            break;
        }
        default:
            printf("Nespravny vstup.\n");
            return 1;
            break;
        }
    }
    return 0;
}