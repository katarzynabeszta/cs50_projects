#include <cs50.h>
#include <stdio.h>
#include <math.h>

int change_converted (int change_left, int x_coin);
int coins_left (int change_left, int change_in_x_coins, int x_coin);
int total_used_coins (int change_in_quarter, int change_in_dime, int change_in_nickle, int change_in_cent);

double changeFromUser;
int quarterCoin = 25;
int dimeCoin = 10;
int nickelCoin = 5;
int centCoin = 1;
int changeInQuarterCoins = 0;
int changeInDimeCoins = 0;
int changeInNickelCoins = 0;
int changeInCentCoins = 0;
int changeLeft = 0;
int totalUsedCoins = 0;

int main(void)
{
    // Get change value from user
    do
    {
        changeFromUser = get_double("What change need to be returned? Provide as per example format: 1.05 (1 dolar and 5 penny)\n");
    }
    while (changeFromUser <= 0);
    printf("Change from user is: %f dolar\n", changeFromUser);

    // Convert user change to cents
    int changeConvertedToCents = changeFromUser * 100;
    printf("Change converted to cents is: %i cents\n", changeConvertedToCents);

    // Check how many each type of coins have to be used
    if (changeConvertedToCents >= quarterCoin)
    {
        changeInQuarterCoins = change_converted (changeConvertedToCents, quarterCoin);
        changeLeft = coins_left (changeConvertedToCents, changeInQuarterCoins, quarterCoin);
        if (changeLeft<quarterCoin && changeLeft>=dimeCoin)
        {
            changeInDimeCoins = change_converted (changeLeft, dimeCoin);
            changeLeft = coins_left (changeLeft, changeInDimeCoins, dimeCoin);
            if (changeLeft<dimeCoin && changeLeft>=nickelCoin)
            {
                changeInNickelCoins = change_converted (changeLeft, nickelCoin);
                changeLeft = coins_left (changeLeft, changeInNickelCoins, nickelCoin);
                if (changeLeft<nickelCoin && changeLeft>=centCoin)
                {
                    changeInCentCoins = change_converted (changeLeft, centCoin);
                    totalUsedCoins = total_used_coins(changeInQuarterCoins, changeInDimeCoins, changeInNickelCoins, changeInCentCoins);
                    printf("Number of coins used in total: %i\n", totalUsedCoins);
                }
                else
                {
                    totalUsedCoins = total_used_coins(changeInQuarterCoins, changeInDimeCoins, changeInNickelCoins, 0);
                    printf("Number of coins used in total: %i\n", totalUsedCoins);
                }
            }
            else if (changeLeft<nickelCoin && changeLeft>=centCoin)
            {
                changeInCentCoins = change_converted (changeLeft, centCoin);
                totalUsedCoins = total_used_coins(changeInQuarterCoins, changeInDimeCoins, changeInNickelCoins, changeInCentCoins);
                printf("Number of coins used in total: %i\n", totalUsedCoins);
            }
            else
            {
                totalUsedCoins = total_used_coins(changeInQuarterCoins, changeInDimeCoins, 0, 0);
                printf("Number of coins used in total: %i\n", totalUsedCoins);
            }
        }
        else if (changeLeft<dimeCoin && changeLeft>=nickelCoin)
        {
            changeInNickelCoins = change_converted (changeLeft, nickelCoin);
            changeLeft = coins_left (changeLeft, changeInNickelCoins, nickelCoin);
            if (changeLeft<nickelCoin && changeLeft>=centCoin)
            {
                changeInCentCoins = change_converted (changeLeft, centCoin);
                totalUsedCoins = total_used_coins(changeInQuarterCoins, changeInNickelCoins, changeInCentCoins, 0);
                printf("Number of coins used in total: %i\n", totalUsedCoins);
            }
            else
            {
                totalUsedCoins = changeInQuarterCoins + changeInNickelCoins;
                printf("Number of coins used in total: %i\n", totalUsedCoins);
            }
        }
        else if (changeLeft<nickelCoin && changeLeft>=centCoin)
        {
            changeInCentCoins = change_converted (changeLeft, centCoin);
            totalUsedCoins = total_used_coins(0, 0, changeInQuarterCoins, changeInCentCoins);
            printf("Number of coins used in total: %i\n", totalUsedCoins);
        }
        else
        {
            totalUsedCoins = changeInQuarterCoins;
            printf("Number of coins used in total: %i\n", totalUsedCoins);
        }
    }
    else if (changeConvertedToCents<quarterCoin && changeConvertedToCents>=dimeCoin)
    {
        changeInDimeCoins = change_converted (changeConvertedToCents, dimeCoin);
        changeLeft = coins_left (changeConvertedToCents, changeInDimeCoins, dimeCoin);
        if (changeLeft<dimeCoin && changeLeft>=nickelCoin)
        {
            changeInNickelCoins = change_converted (changeLeft, nickelCoin);
            changeLeft = coins_left (changeLeft, changeInNickelCoins, nickelCoin);
            if (changeLeft<nickelCoin && changeLeft>=centCoin)
            {
                changeInCentCoins = change_converted (changeLeft, centCoin);
                totalUsedCoins = total_used_coins(changeInDimeCoins, changeInNickelCoins, changeInCentCoins, 0);
                printf("Number of coins used in total: %i\n", totalUsedCoins);
            }
            else
            {
                totalUsedCoins = changeInDimeCoins + changeInNickelCoins + changeInCentCoins;
                printf("Number of coins used in total: %i\n", totalUsedCoins);
            }
        }
        else if (changeLeft<nickelCoin && changeLeft>=centCoin)
        {
            changeInCentCoins = change_converted (changeLeft, centCoin);
            totalUsedCoins = total_used_coins(changeInDimeCoins, changeInNickelCoins, changeInCentCoins, 0);
            printf("Number of coins used in total: %i\n", totalUsedCoins);
        }
        else
        {
            totalUsedCoins = changeInDimeCoins;
            printf("Number of coins used in total: %i\n", totalUsedCoins);
        }
    }
    else if (changeConvertedToCents<dimeCoin && changeConvertedToCents>=nickelCoin)
    {
        changeInNickelCoins = change_converted (changeConvertedToCents, nickelCoin);
        changeLeft = coins_left (changeConvertedToCents, changeInNickelCoins, nickelCoin);

        if (changeLeft<nickelCoin && changeLeft>=centCoin)
        {
            changeInCentCoins = change_converted (changeLeft, centCoin);
            totalUsedCoins = total_used_coins(0, 0, changeInNickelCoins, changeInCentCoins);
            printf("Number of coins used in total: %i\n", totalUsedCoins);
        }
        else
        {
            totalUsedCoins = changeInNickelCoins;
            printf("Number of coins used in total: %i\n", totalUsedCoins);
        }
    }
    else
    {
        changeInCentCoins = change_converted (changeConvertedToCents, centCoin);
    }
}

// Check how many coins have to be used
int change_converted (int change_left, int x_coin)
{
    int change_in_x_coins = change_left / x_coin;
    printf("You need to use %i coins of nomine %i\n", change_in_x_coins, x_coin);
    return change_in_x_coins;
}

// Check how many coins left
int coins_left (int change_left, int change_in_x_coins, int x_coin)
{
    int final_change_left = change_left - (x_coin * change_in_x_coins);
    printf("Change left is %i coins\n", change_left);
    return final_change_left;
}

// Check how many coins is used in total by adding them all
int total_used_coins (int change_in_quarter, int change_in_dime, int change_in_nickle, int change_in_cent)
{
    int total_coins = change_in_quarter + change_in_dime + change_in_nickle + change_in_cent;
    printf("Number of coins used in total: %i\n", total_coins);
    return total_coins;
}
