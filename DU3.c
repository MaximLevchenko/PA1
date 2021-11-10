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

/**
 * @brief 
 * Function to check if year is leap or not
 * @param year first year
 * @return true or false
 */
bool is_leap(int year)
{
    if ((year % 4 == 0 && year % 100 != 0 && year % 4000 != 0) || year % 400 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

} /**
 * @brief 
 * Function to check if 2 equal years are leap and if they month1<3&&month2>3
 * @param year1 first year
 * @param year2 second year
 * @param month1 first month
 * @param month2 second month 
 * @return 1 if true or 0 if false
 */
bool is_in_1year_leap(int year1, int year2, int month1, int month2)
{
    if (is_leap(year1) && year1 == year2 && month1 < 3 && month2 > 2)
        return true;
    return false;
}
/**
 * @brief 
 * Function to count leap years
 * @param year1 first year 
 * @param year2 second year
 * @param month1 first month
 * @param month2 second month
 * @return long long int count of leap years
 */
long long int countLeapYears(int year1, int year2, int month1, int month2, int *times_iterated1, int *times_iterated2)
{
    *times_iterated1=1967;
    if (year1 == year2)
        return 0;
    int leap_year_counter = 0;
    int year2_4 = year2 / 4;
    int year2_100 = year2 / 100;
    int year2_400 = year2 / 400;
    int year2_4000 = year2 / 4000;
    int year1_4 = year1 / 4;
    int year1_100 = year1 / 100;
    int year1_400 = year1 / 400;
    int year1_4000 = year1 / 4000;
    int res2 = year2_4 - year2_100 + year2_400 - year2_4000;
    int res1 = year1_4 - year1_100 + year1_400 - year1_4000;
    leap_year_counter = res2 - res1;
    if (is_leap(year1) && month1 < 3)
        leap_year_counter++;
    if (is_leap(year2) && month2 < 3)
        leap_year_counter--;
    return leap_year_counter;
}
/**
 * @brief 
 * Function to count jouls between two years
 * @param year1 first year
 * @param year2 second year
 * @return long long int count of joules between two years
 */
long long int countYearJoules(int year1, int year2)
{
    if (year1 == year2)
        return 0;
    return year2 - year1;
}
/**
 * @brief 
 * Function to count jouls between months
 * @param month1 first month
 * @param month2 second month
 * @param arr_month array with the amount of jouls in 1 month
 * @return long long int amount of jouls between months
 */
long long int countMonthJoules(int month1, int month2, int arr_month[])
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
/**
 * @brief 
 * Function to count jouls between minutes days and hours
 * @param num1 min or hour or day 1 
 * @param num2 min or hour or day 2
 * @param arr_dec array of joul amount in tens
 * @param arr_dig array of joul amount in digits
 * @return int amount of jouls between two numbers
 */
int countMinuteHourDayJoules(int num1, int num2, int arr_dec[], int arr_dig[])
{
    int result_num = 0;
    if (num1 == num2)
        return result_num;

    int count_dec1 = num1 / 10, count_dig1 = num1 % 10;                 //finding tens and digits of the number for first minute
    int dec1 = arr_dec[count_dec1 - 1], dig1 = arr_dig[count_dig1 - 1]; //accessing the value of the tens and digits through the array
    int count_dec2 = num2 / 10, count_dig2 = num2 % 10;                 //for second minute doing the same
    int dec2 = arr_dec[count_dec2 - 1], dig2 = arr_dig[count_dig2 - 1];
    int joule_count_num1 = dec1 + dig1;               //counting sum of tens and digits for the first
    int joule_count_num2 = dec2 + dig2;               //for the second doing the same
    result_num = joule_count_num1 - joule_count_num2; //counting the difference in Joules beetwen two given numbers
    if (num1 > num2 || num2 > num1)
    {
        result_num = result_num * (-1);
    }
    return result_num;
}
/**
 * @brief 
 * Function to validate the date
 * @param y1 year1
 * @param m1 month
 * @param d1 day1
 * @param h1 hour1
 * @param i1 minute1
 * @param y2 year2
 * @param m2 month2
 * @param d2 day2
 * @param h2 hour2
 * @param i2 minute2
 * @return true or false
 */
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
    int difference_minutes = countMinuteHourDayJoules(i1, i2, arr_dec, arr_dig);          //value of the difference in Joules beetwen minutes
    if (difference_minutes >= 0)
        difference_minutes += abs(i1 - i2) * MINUTE_JOULE;
    else
        difference_minutes -= abs(i1 - i2) * MINUTE_JOULE;
    int difference_hours = countMinuteHourDayJoules(h1, h2, arr_dec, arr_dig); //value of the difference in Joules beetwen hours
    if (difference_hours >= 0)
        difference_hours += abs(h1 - h2) * HOUR_JOULE;
    else
        difference_hours -= abs(h1 - h2) * HOUR_JOULE;
    int difference_days = abs(d1 - d2) * DAY_JOULE;
    if (d1 > d2)
        difference_days *= (-1);
    long long int difference_months = countMonthJoules(m1, m2, arr_month);
    printf("%lld\n", difference_months);

    long long int number_leap_years = countLeapYears(y1, y2, m1, m2, &year_to_add1, &year_to_add2);
    printf("%d nice cock bro\n", year_to_add1);
    if (is_in_1year_leap(y1, y2, m1, m2))
    {
        number_leap_years += 1;
    }
    printf("%lld number leap year\n", number_leap_years);
    long long int difference_years = countYearJoules(y1, y2) * YEAR_JOULE;
    printf("%d, %d\n", year_to_add1, year_to_add2);
    long long int leap_counter_joul = number_leap_years * DAY_JOULE;
    printf("%lld cok\n", leap_counter_joul);
    *consumption = difference_minutes + difference_hours +
                   difference_days + difference_months +
                   difference_years + leap_counter_joul; //number_leap_years DAY_JOULE +year2 +year1#FIXME:

    if (dateExists(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2))
        return 1;
    else
        return 0;
    return 1;
}
#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    long long int consumption;
    energyConsumption(1961, 3, 27, 7, 8, 2161, 4, 4, 20, 26, &consumption);
    printf("%lld\n", consumption);
    return 0;
}
#endif /* __PROGTEST__ */