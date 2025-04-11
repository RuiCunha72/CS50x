#include <cs50.h>
#include <stdio.h>

int check_how_many_digits_the_card_has(long credit_number);
string check_if_valid(void);
bool check_luhns_algorithm(long credit_card_number);
long user_input(void);
string check_type_of_card(long credit_card_number);

int main(void)
{
    string result = check_if_valid();
    printf("%s", result);
}

int check_how_many_digits_the_card_has(long credit_number)
{
    long digits_of_credit_card = credit_number;
    int count = 0;
    while (digits_of_credit_card != 0)
    {
        digits_of_credit_card = digits_of_credit_card / 10;
        count++;
    }
    return count;
}

string check_if_valid(void)
{
    string result = "error";
    long credit_card_number = user_input();
    int count = check_how_many_digits_the_card_has(credit_card_number);
    if (count < 13 || count > 16)
    {
        result = "INVALID\n";
    }
    else
    {
        bool luhns_algorithm = check_luhns_algorithm(credit_card_number);
        if (luhns_algorithm == false)
        {
            result = "INVALID\n";
        }
        else
        {
            result = check_type_of_card(credit_card_number);
        }
    }
    return result;
}

bool check_luhns_algorithm(long credit_card_number)
{
    bool result = false;
    long credit_card_number_without_the_last_digit = credit_card_number / 10;
    int first_sum = 0;
    while (credit_card_number_without_the_last_digit > 0)
    {
        int digit = (credit_card_number_without_the_last_digit % 10) * 2;
        if (digit > 9)
        {
            digit = (digit / 10) + (digit % 10);
        }
        first_sum += digit;
        credit_card_number_without_the_last_digit /= 100;
    }
    int second_sum = 0;
    while (credit_card_number > 0)
    {
        int digit = credit_card_number % 10;
        second_sum += digit;
        credit_card_number /= 100;
    }
    int sum_total = first_sum + second_sum;
    if (sum_total % 10 == 0)
    {
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}

long user_input(void)
{
    long number = get_long("Number: ");
    return number;
}

string check_type_of_card(long credit_card_number)
{
    long credit_card = credit_card_number;
    while (credit_card >= 100)
    {
        credit_card /= 10;
    }
    int first_digit = credit_card / 10;
    int first_two_digits = credit_card;
    int count = check_how_many_digits_the_card_has(credit_card_number);
    if ((first_two_digits == 34 || first_two_digits == 37) && count == 15)
    {
        return "AMEX\n";
    }
    else if (first_two_digits >= 51 && first_two_digits <= 55 && count == 16)
    {
        return "MASTERCARD\n";
    }
    else if (first_digit == 4 && (count == 13 || count == 16))
    {
        return "VISA\n";
    }
    else
    {
        return "INVALID\n";
    }
}
