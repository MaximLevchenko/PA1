#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// strupr();
bool isValid(char *array) //checks whether the abbreviation is valid or not
{
    int length = strlen(array);
    for (int i = 0; i < length; i++)
    {
        if (array[i] != toupper(array[i])) //|| !isalpha(array[i])
            return false;
    }
    return true;
}
int index_count = 0; // position for the index of the letter to be uppercased

int findComb(char *final_array, char *abbreviation, int uppercase_array[], int start, int end, int letter_index)
{
    int start_before = start;
    for (int i = start; i < end-1; i++)
    {
        if (toupper(final_array[i]) == abbreviation[letter_index])
        {
            if (letter_index == (int)strlen(abbreviation))
            {
                for (int j = 0, array_index = 0; j < end; j++) // for loop for printing out uppercased string
                {
                    if (j == uppercase_array[array_index++])
                    {
                        printf("%c", toupper(final_array[j]));
                        continue;
                    }
                    printf("%c", final_array[j]);
                }
                printf("\n");
            }
            uppercase_array[index_count++] = i;
            findComb(final_array, abbreviation, uppercase_array, i, end, letter_index + 1);
        }
    }
    if (letter_index > 0)
        findComb(final_array, abbreviation, uppercase_array, start_before, end, letter_index - 1);
    return 1;
}

void allocateWords(char **whatAllocate, const int lengthWhatAllocate) //allocation
{
    (*whatAllocate) = (char *)malloc(lengthWhatAllocate * sizeof(**whatAllocate));
}
void makeString(char **final_str, char *str, int second_quote_pos, int first_quote_pos, int *str_length)
{
    *str_length = second_quote_pos - first_quote_pos - 1; //difference between indexes
    allocateWords(final_str, *str_length + 20);
    // for (int i = first_quote_pos, index = 0; i < second_quote_pos - 1; i++)
    // {
    //     *final_str[index++] = str[i];
    // }
    strncpy(*final_str, str + first_quote_pos + 1, *str_length);
}

//function to find positions of the quotes and checking if the input is valid
bool getPosition(char *abbreviation, char *buffer, int size, int *first_quote_pos, int *second_quote_pos)
{
    for (int i = 0, quotes_count = 0; i < size - 1; i++)
    {
        if (buffer[i] == '"')
        {
            quotes_count++;
            if (quotes_count == 1)
            {
                *first_quote_pos = i;
                printf("%d first pos\n", *first_quote_pos);
            }
            if (quotes_count == 2)
            {
                *second_quote_pos = i;
                printf("%d second pos\n", *second_quote_pos);
            }
        }
        if ((i == size - 2 && quotes_count < 2) || quotes_count > 2) //TODO: if size-1 for some reason doesnt work(maybe because of '\0)
        {
            printf("Nespravny vstup.\n");
            free(abbreviation), free(buffer);
            return false;
        }
    }
    return true;
}

int main()
{
    char *buffer = NULL, *final_string = NULL, *abbreviation = (char *)malloc(300 * sizeof(char));
    int str_length = 0, first_quote_pos = 0, second_quote_pos = 0, uppercase_array[200];
    size_t mem_allocated = 0, mem_allocated_abbreviation;
    ssize_t size = 0; //returns the size of an array with
    printf("Zkratka:\n");
    if (getline(&abbreviation, &mem_allocated_abbreviation, stdin) == 0 || !isValid(abbreviation))
    {
        printf("Nespravny vstup.\n");
        free(abbreviation);
        return 1;
    }
    printf("%ld\n", strlen(abbreviation));
    while ((size = getline(&buffer, &mem_allocated, stdin)) != feof(stdin))
    {
        if (feof(stdin) && size != 0)
        {
            free(buffer);
            return 1;
        }
        printf("%s %zu %ld\n", buffer, size, mem_allocated);
        if (getPosition(abbreviation, buffer, size, &first_quote_pos, &second_quote_pos) == false)
        {
            return 1;
        }
        makeString(&final_string, buffer, second_quote_pos, first_quote_pos, &str_length);
        final_string[str_length] = '\0';
        printf("\"%s\"\n", final_string);
        printf("%d\n", str_length);
        findComb(final_string, abbreviation, uppercase_array, 0, strlen(final_string), 0);
        // for (int j = 0; j < str_length; j++)
        //     printf("%c", final_string[j]);
        // printf("\n");
        free(final_string),
            final_string = NULL;
    }
    free(abbreviation), free(buffer);
    return 0;
}