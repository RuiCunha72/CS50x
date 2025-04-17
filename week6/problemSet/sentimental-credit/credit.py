def main():
    while(True):
        try:
            number = int(input("Number: "))
        except ValueError:
            False
        else:
            is_valid(number)
            break

def is_valid(number):
    if len(str(number)) > 12 and len(str(number)) < 17:
        lun_algorithm(number)
    else:
        print("INVALID")

def lun_algorithm(number):
    #digitos nas posições pares (da direita para a esquerda)
    credit_card_number_without_the_last_digit = number // 10
    first_sum = 0
    while(credit_card_number_without_the_last_digit > 0):
        digit = (credit_card_number_without_the_last_digit % 10) * 2
        if digit > 9:
            digit = (digit // 10) + (digit % 10)
        first_sum += digit
        credit_card_number_without_the_last_digit //= 100
    #digitos nas posições ímpares (da direita para a esquerda)
    second_sum = 0
    tmp = number
    while tmp > 0:
        digit = tmp % 10
        second_sum += digit
        tmp //= 100
    #ultimo digito da soma total = 0?
    sum_total = first_sum + second_sum
    if sum_total % 10 == 0:
        card_type(number)
    else:
        print("INVALID")


def card_type(number):
    if 12 < len(str(number)) < 17 and str(number)[:1] == "4":
        print("VISA")
    elif len(str(number)) == 15 and str(number)[:2] in ["34", "37"]:
        print("AMEX")
    elif len(str(number)) == 16 and 50 < int(str(number)[:2]) < 56:
        print("MASTERCARD")
    else:
        print("INVALID")
 
main()