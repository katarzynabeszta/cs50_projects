#include <cs50.h>
#include <stdio.h>
#include <math.h>

long getCardNumberFromUser(void);
int getDigitOfCardNumber(long cardNumber);
long getFirstTwoCardDigits(long cardNumber, int digitOfCardNumber);
int getCardChecksum(long cardNumber);
void validateCardAndPrintProvider(int digitOfCardNumber, long firstTwoCardDigits, int firstCardDigit, int sum);

int main (void)
{
    long cardNumber = getCardNumberFromUser();
    int digitOfCardNumber = getDigitOfCardNumber(cardNumber);

    long firstTwoCardDigits = getFirstTwoCardDigits(cardNumber, digitOfCardNumber);
    int firstCardDigit = firstTwoCardDigits % 10;

    int sum = getCardChecksum(cardNumber);
    validateCardAndPrintProvider(digitOfCardNumber, firstTwoCardDigits, firstCardDigit, sum);
}

long getCardNumberFromUser(void)
{
    long cardNumber;
    cardNumber = get_long("Type card number: ");
    printf("Card number is: %li\n", cardNumber);
    return cardNumber;
}

int getDigitOfCardNumber(long cardNumber)
{
    int digitOfCardNumber = 0;
    long tempCardNumber = cardNumber;
    do {
        tempCardNumber = tempCardNumber / 10;
        digitOfCardNumber = digitOfCardNumber + 1;
    }
    while (tempCardNumber > 0);
    return digitOfCardNumber;
}

long getFirstTwoCardDigits(long cardNumber, int digitOfCardNumber)
{
    long tempCardNumber = cardNumber;

    for (int i = 0; i < digitOfCardNumber - 2; i++)
    {
        tempCardNumber = tempCardNumber / 10;
    }
    return tempCardNumber;
}

int getCardChecksum(long cardNumber)
{
    int sum = 0;
    int lastDigit = cardNumber % 10;

    do {
        int tempLastDigit = cardNumber % 10;
        sum += tempLastDigit;
        cardNumber = cardNumber / 10;
        int secondLastDigit = cardNumber % 10;
        int lastDigitMultipliedByTwo = secondLastDigit * 2;
        if (lastDigitMultipliedByTwo>= 10)
        {
            int secondDigit = lastDigitMultipliedByTwo % 10;
            int firstDigit = lastDigitMultipliedByTwo / 10;
            sum += secondDigit + firstDigit;
        }
        else {
            sum += lastDigitMultipliedByTwo;
        }
        cardNumber = cardNumber / 10;
    }
    while (cardNumber > 0);
    return sum;
}

void validateCardAndPrintProvider(int digitOfCardNumber, long firstTwoCardDigits, int firstCardDigit, int sum)
{
    int lastDigitOfSum = sum % 10;
    if (lastDigitOfSum == 0)
    {
        printf("Card is VALID\n");
        if (digitOfCardNumber == 15 && (firstTwoCardDigits == 34 || firstTwoCardDigits == 37 ))
        {
            printf("This is AMEX\n");
        }
        else if (digitOfCardNumber == 16 && (firstTwoCardDigits >= 51 && firstTwoCardDigits <= 55))
        {
            printf("This is MASTERCARD\n");
        }
        else if ((digitOfCardNumber == 16 || digitOfCardNumber == 13) && (firstCardDigit == 4))
        {
            printf("This is VISA\n");
        }
        else
        {
             printf("Card is unknown\n");
        }
    }
    else {
        printf("Checksum failed. Card is NOT VALID\n");
    }
}