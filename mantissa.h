
#pragma once
#include <iostream>

using namespace std;

bool mantissa(char numString[], int& numerator, int& denominator);
bool calculateDenominator(int& denominator, int numDenominators);
void calculateNumerator(int& numerator, int denominator, int numeratorIndex, int numDenominators, char numString[]);

bool mantissa(char numString[], int& numerator, int& denominator)
{
    numerator = 0;
    denominator = 1;

    // Iter is the length of the cstr.
    int iter = 0;
    char ch = numString[iter];

    // Numerator index is where the mantissa begins (the digits after the decimal).
    int numeratorIndex = 0;
    int numDenominators = 0;

    int numSpaces = 0;

    // Has the decimal been reached yet?
    bool reachedDecimal = false;
    // Has a sign character been found?
    bool reachedSign = false;
    // Is the mantissa negative (less than 0 but greater than -1)?
    bool isNegative = false;

    // Used below for trailing zeroes.
    int numZeroes = 0;

    // First, check if all the characters are valid (0-9 or a decimal)
    do
    {
        // If it's outside the range, AND not the decimal, return false.

        if ((ch < '0') || (ch > '9'))
        {
            if (ch == '.')
            {
                // Once the decimal is reached, set the number of characters counted equal to the numerator.
                numeratorIndex = iter;
                reachedDecimal = true;
            }
            // If it's a leading space, check to see if the decimal has been reached.
            // This is used to determine the size of the denominator (if there are extra spaces behind the digits).
            else if (ch == ' ')
            {
                if (reachedDecimal == true)
                {
                    numSpaces++;
                }
            }
            // If the sign character is found AND the previous character is a space or is the first character AND the sign
                // has not already been reached:
            else if ( ((ch == '+') || (ch == '-')) && ((numString[iter - 1] == ' ') || (iter == 0)) && (reachedSign == false) )
            {
                // If the characteristic is 0 but has a negative sign, the mantissa is negative.
                // The mantissa can only be negative if the value of the passed cstr reads as a fraction
                // between -1 and 0.
                if ( (ch == '-' && numString[iter + 1] == '0' && numString[iter + 2] == '.') || 
                    (ch == '-' && numString[iter + 1] == '.') )
                {
                    isNegative = true;
                }

                // The sign has been reached.
                reachedSign = true;
            }
            // Otherwise, if the char is not the terminator or another space, it's some garbage char, so return false (invalid cstr).
            else if ( (ch != '\0') && (ch != ' ') )
            {
                return false;
            }
                
        }
        // Account for trailing zeroes.
        // If the current ch is zero and we are past the decimal, it may be trailing zeroes.
        else if ((ch == '0') && (reachedDecimal == true))
        {
            // This might be the first of many trailing zeroes.
            numZeroes = 1;

            // Create a secondary iterator to continue moving through the cstr.
            int zeroIter = iter + 1;
            // This is the secondary iterator's character.
            char zeroCh = numString[zeroIter];
            // Assume that this 0 we've encountered is the first of many.
            bool trailingZeroes = true;

            while (zeroCh != '\0')
            {
                // If it's another 0, keep counting.
                if (zeroCh == '0')
                {
                    numZeroes++;
                }
                // If it's not another 0, it's something else, so the zeroes are not trailing.
                // Set the num of trailing zeroes to 0, mark this as false, and exit loop.
                else if (zeroCh != '\0')
                {
                    numZeroes = 0;
                    trailingZeroes = false;
                    break;
                }

                zeroIter++;
                zeroCh = numString[zeroIter];
            }

            // If trailing zeroes were encountered, we are done iterating/checking numString[].
            if (trailingZeroes == true)
            {
                break;
            }            
        }

        iter++;
        ch = numString[iter];
    }
    while (ch != '\0');

    // The numString of denominators is the total number of characters, minus 1 for the decimal, minus the numerators.
    numDenominators = iter - numeratorIndex - 1 - numSpaces;

    // Calculate the significant figures of the decimal by multiplying by 10.
    // If there is an overflow, return false.
    if ((calculateDenominator(denominator, numDenominators) == false) && (reachedDecimal == true))
    {
        return false;
    }

    // Calculate the numerator's value.
    // This is done by taking the precision of the decimal and multiplying each digit by a power of 10.
    calculateNumerator(numerator, denominator, numeratorIndex, numDenominators, numString);

    if (isNegative)
    {
        numerator = numerator * -1;
    }

    if (!reachedDecimal)
    {
        numerator = 0;
        denominator = 10;
    }

    return true;
}
//--
bool calculateDenominator(int& denominator, int numDenominators)
{
    for (int i = 0; i < numDenominators; i++)
    {
        denominator *= 10;

        // If the signed int overflows, return false and break.
        if (denominator < 0)
        {
            return false;
        }
    }

    return true;
}
//--
void calculateNumerator(int& numerator, int denominator, int numeratorIndex, int numDenominators, char numString[])
{
    int denominatorVals;
    int mantissaNumerHelper = denominator / 10;

    // Start at the numString after the decimal, numeratorIndex + 1.
    for (char i = numeratorIndex + 1; i != '\0'; i++)
    {
        denominatorVals = numString[i] - '0'; // - '0'

        numerator += mantissaNumerHelper * denominatorVals;
        mantissaNumerHelper /= 10;
    }
}