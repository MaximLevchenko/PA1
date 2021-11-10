#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */
#include <math.h>
#include <stdbool.h>

#define MINUTE_JOULE 200
#define HOUR_JOULE 12200
#define DAY_JOULE 292886
#define MONTH_31_JOULE 9079466
#define MONTH_30_JOULE 8786580
#define MONTH_29_JOULE 8493694
#define MONTH_28_JOULE 8200808
#define YEAR_JOULE 106903390
//63 556 262+35 146 320+
//FIXME:     Try to find errors in the leap years         FIXME:  TODO:      Try to enhance the algorithm
//   I think there will be problems with the leap years and counting joules in months TODO:

long long int countYearJoules(int year1, int year2)
{
    if (year1 == year2)
        return 0;
    return year2 - year1;
}

//function to understand if the year is leap or not
bool is_leap(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//if two years are same and leap, we return true and then add 1 day
bool is_in_1year_leap(int year1, int year2, int month1, int month2)
{
    if (is_leap(year1) && year1 == year2 && month1 < 3 && month2 > 2)
        return true;
    return false;
}
//TODO: Maybe there will be errors
long long int countLeapYears(int year1, int year2, int month1, int month2, int *times_iterated1, int *times_iterated2)
{
    if (year1 == year2)
        return 0;
    long long int start_year1 = year1; //this will be needed when we count the amount of years we iterated in while loop
    long long int start_year2 = year2;
    long long int leap_year_counter = 0, minus_years = 0;
    while (!is_leap(year1))
    {
        year1++;
    }
    while (!is_leap(year2))
    {
        year2--;
    }
    *times_iterated1 = year1 - start_year1; //TODO:POINTER TO THIS   //difference beetween year in while loop and start year. MINUS THIS
    *times_iterated2 = start_year2 - year2;
    if (year1 == year2 && is_leap(year1) && month1 < 3 && month2 > 2) //checking if years are equal and leap and if they are, then return 1
        return leap_year_counter = 1;
    if (is_leap(year1) && month1 < 3)
        leap_year_counter++;
    else
        leap_year_counter--;
    if (is_leap(year2) && month2 > 2)
        leap_year_counter++;
    else
        leap_year_counter--;
    if ((is_leap(year1) && month1 < 3) && (is_leap(year2) && month2 > 2))
        leap_year_counter--;
    if ((is_leap(year1) && month1 > 2) && (is_leap(year2) && month2 < 3))
        leap_year_counter++;
    if (start_year2 - year2 > 0 && month2 < 3)
    {
        leap_year_counter++; //MAYBE
    }
    if (year1 - start_year1 > 0 && month1 > 2)
    {
        leap_year_counter++;
    }
    minus_years = start_year2 - start_year1; //difference in years
    long long int leap_4 = minus_years / 4;
    long long int leap_100 = minus_years / 100;
    long long int leap_400 = minus_years / 400;
    long long int leap_4000 = minus_years / 4000;
    leap_year_counter = leap_year_counter + leap_4 - leap_100 + leap_400 - leap_4000;
    return leap_year_counter;
}
// TODO:  I think we shouldn`t even write additional conditions for leap years,
// as we can just make adjustment using leap_year_counter and that i guess will do it
// function for finding Joules in months TODO:
long long int countMonthJoules(int month1, int month2, int arr_month[], int arr_month_leap_year[])
{
    int count_month_joul = 0;
    int month_joul1 = month1, month_joul2 = month2;
    if (month1 == month2) // if values of the months are equal, no need to do further equations
        return count_month_joul;
    if (month1 > month2)
    {
        month_joul1 = month2;
        month_joul2 = month1;
    }
    for (int i = month_joul1; i < month_joul2; i++) //for loop to go through elements of the array.
    {
        count_month_joul += arr_month[i - 1];
    }
    if (month1 > month2)
        return count_month_joul * (-1);
    return count_month_joul;
}

//function for finding Joules in minutes, hours and days
int countMinuteHourDayJoules(int num1, int num2, int arr_dec[], int arr_dig[])
{
    int result_num = 0;
    if (num1 == num2)
        return result_num;

    int count_dec1 = num1 / 10, count_dig1 = num1 % 10; //finding tens and digits of the number for first minute
    // printf("%d, %d\n", count_dec1, count_dig1);
    int dec1 = arr_dec[count_dec1 - 1], dig1 = arr_dig[count_dig1 - 1]; //accessing the value of the tens and digits through the array
    // printf("%d cock\n", dig1);
    int count_dec2 = num2 / 10, count_dig2 = num2 % 10; //for second minute doing the same
    int dec2 = arr_dec[count_dec2 - 1], dig2 = arr_dig[count_dig2 - 1];
    int joule_count_num1 = dec1 + dig1; //counting sum of tens and digits for the first
    // printf("%d\n", joule_count_num1);
    int joule_count_num2 = dec2 + dig2; //for the second doing the same
    // printf("%d\n", joule_count_num2);

    result_num = joule_count_num1 - joule_count_num2; //counting the difference in Joules beetwen two given numbers
    // printf("%d nice\n", result_num);
    if (num1 > num2 || num2 > num1)
    {
        result_num = result_num * (-1);
    }
    // printf("%d\n", result_num);
    return result_num;
}

bool dateExists(int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2)
{
    if (y1 < 1600 || y2 < 1600 || m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12 || d1 < 1 || d2 < 1 ||
        h1 < 0 || h1 > 23 || h2 < 0 || h2 > 23 || i1 < 0 || i1 > 59 || i2 < 0 || i2 > 59 ||
        ((m1 == 1 || m1 == 3 || m1 == 5 || m1 == 7 || m1 == 8 || m1 == 10 || m1 == 12) && d1 > 31) ||
        ((m2 == 1 || m2 == 3 || m2 == 5 || m2 == 7 || m2 == 8 || m2 == 10 || m2 == 12) && d2 > 31) ||
        ((m1 == 4 || m1 == 6 || m1 == 9 || m1 == 11) && d1 > 30) || ((m2 == 4 || m2 == 6 || m2 == 9 || m2 == 11) && d2 > 30) ||
        ((is_leap(y1) && m1 == 2) && d1 > 29) || ((!is_leap(y1) && m1 == 2) && d1 > 28) ||
        ((is_leap(y2) && m2 == 2) && d2 > 29) || ((!is_leap(y2) && m2 == 2) && d2 > 28) ||

        (y1 == y2 && m1 > m2) || (y1 > y2) ||
        (y1 == y2 && m1 == m2 && d1 > d2) || (y1 == y2 && m1 == m2 && d1 == d2 && h1 > h2) ||
        (y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 > i2))
    {
        return false;
    }
    return true;
}
int energyConsumption(int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2, long long int *consumption)
{

    int year_to_add1 = 0, year_to_add2 = 0;
    int arr_dec[5] = {34, 69, 101, 134, 167};             //array for tens value in Joules (range is 10-50)
    int arr_dig[10] = {4, 9, 11, 14, 17, 18, 23, 27, 28}; //array for digit value in Joules (range is 0-9)
    int arr_month[12] = {MONTH_31_JOULE, MONTH_28_JOULE, MONTH_31_JOULE, MONTH_30_JOULE,
                         MONTH_31_JOULE, MONTH_30_JOULE, MONTH_31_JOULE, MONTH_31_JOULE,
                         MONTH_30_JOULE, MONTH_31_JOULE, MONTH_30_JOULE, MONTH_31_JOULE}; //array of the values for each month in Joules
    int arr_month_leap_year[12] = {MONTH_31_JOULE, MONTH_29_JOULE, MONTH_31_JOULE, MONTH_30_JOULE,
                                   MONTH_31_JOULE, MONTH_30_JOULE, MONTH_31_JOULE, MONTH_31_JOULE,
                                   MONTH_30_JOULE, MONTH_31_JOULE, MONTH_30_JOULE, MONTH_31_JOULE}; //array of the values for each month in Joules
    int difference_minutes = countMinuteHourDayJoules(i1, i2, arr_dec, arr_dig);                    //value of the difference in Joules beetwen minutes
    if (difference_minutes >= 0)
        difference_minutes += abs(i1 - i2) * MINUTE_JOULE;
    else
        difference_minutes -= abs(i1 - i2) * MINUTE_JOULE;
    // printf("%d\n", difference_minutes);
    // printf("----------------\n");
    int difference_hours = countMinuteHourDayJoules(h1, h2, arr_dec, arr_dig); //value of the difference in Joules beetwen hours
    if (difference_hours >= 0)
        difference_hours += abs(h1 - h2) * HOUR_JOULE;
    else
        difference_hours -= abs(h1 - h2) * HOUR_JOULE;
    // printf("%d\n", difference_hours);
    // printf("----------------\n");
    int difference_days = abs(d1 - d2) * DAY_JOULE;
    if (d1 > d2)
        difference_days *= (-1);
    // int difference_days = countMinuteHourDayJoules(d1, d2, arr_dec, arr_dig); //value of the difference in Joules beetwen days
    // if (difference_days >= 0)
    //     difference_days += abs(d1 - d2) * DAY_JOULE;
    // else
    //     difference_days -= abs(d1 - d2) * DAY_JOULE;
    // printf("%d\n", difference_days);
    // printf("----------------\n");

    long long int difference_months = countMonthJoules(m1, m2, arr_month, arr_month_leap_year);
    printf("%lld\n", difference_months);
    // printf("----------------\n");
    long long int number_leap_years = countLeapYears(y1, y2, m1, m2, &year_to_add1, &year_to_add2);
    printf("%lld number leap year\n", number_leap_years); //#TODO: important for leap counter
    // printf("----------------\n");
    // int year1_add = year_to_add1;
    // int year2_add = year_to_add2;
    long long int difference_years = countYearJoules(y1, y2) * YEAR_JOULE;
    // printf("%lld\n", difference_years);
    // printf("----------------\n");
    printf("%d, %d\n", year_to_add1, year_to_add2);
    // printf("%d",number_leap_years*DAY_JOULE);
    long long int leap_counter_joul = number_leap_years * DAY_JOULE;
    printf("%lld cok\n", leap_counter_joul);
    *consumption = difference_minutes + difference_hours +
                   difference_days + difference_months +
                   difference_years + leap_counter_joul ; //number_leap_years DAY_JOULE +year2 +year1#FIXME:
    if (is_in_1year_leap(y1, y2, m1, m2))
    {
        *consumption += DAY_JOULE;
    }
    // printf("%lld\n", *consumption);
    if (dateExists(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return 1;
}
#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    long long int consumption;
    energyConsumption(1885, 11, 1, 21, 16, 1889, 5, 25, 3, 4, &consumption);

    // assert(energyConsumption(2021, 10, 1, 13, 15,
    //                          2021, 10, 1, 18, 45, &consumption) == 1 &&
    //        consumption == 67116LL);
    // assert(energyConsumption(2021, 10, 1, 13, 15,
    //                          2021, 10, 2, 11, 20, &consumption) == 1 &&
    //        consumption == 269497LL);
    // assert(energyConsumption(2021, 1, 1, 13, 15,
    //                          2021, 10, 5, 11, 20, &consumption) == 1 &&
    //        consumption == 81106033LL);
    // assert(energyConsumption(2024, 1, 1, 13, 15,
    //                          2024, 10, 5, 11, 20, &consumption) == 1 &&
    //        consumption == 81398919LL);
    // assert(energyConsumption(1900, 1, 1, 13, 15,
    //                          1900, 10, 5, 11, 20, &consumption) == 1 &&
    //        consumption == 81106033LL);
    // assert(energyConsumption(2021, 10, 1, 0, 0,
    //                          2021, 10, 1, 12, 0, &consumption) == 1 &&
    //        consumption == 146443LL);
    // assert(energyConsumption(2021, 10, 1, 0, 15,
    //                          2021, 10, 1, 0, 25, &consumption) == 1 &&
    //        consumption == 2035LL);
    // assert(energyConsumption(2021, 10, 1, 12, 0,
    //                          2021, 10, 1, 12, 0, &consumption) == 1 &&
    //        consumption == 0LL);
    // assert(energyConsumption(2021, 10, 1, 12, 0,
    //                          2021, 10, 1, 12, 1, &consumption) == 1 &&
    //        consumption == 204LL);
    // assert(energyConsumption(2021, 11, 1, 12, 0,
    //                          2021, 10, 1, 12, 0, &consumption) == 0);
    // assert(energyConsumption(2021, 10, 32, 12, 0,
    //                          2021, 11, 10, 12, 0, &consumption) == 0);
    // assert(energyConsumption(2100, 2, 29, 12, 0,
    //                          2100, 2, 29, 12, 0, &consumption) == 0);
    // assert(energyConsumption(2400, 2, 29, 12, 0,
    //                          2400, 2, 29, 12, 0, &consumption) == 1 &&
    //        consumption == 0LL);
    printf("%lld\n", consumption);
    return 0; //^year            //^year
}
#endif /* __PROGTEST__ */