#pragma once
#include <iostream>

using namespace std;

bool characteristic(char numString[], int& c);

bool characteristic(char numString[], int& c)
{
    int numOfChars = 0;

    c = 0;

    int iterator = 0;
	int numOfLeadingSpaces = 0;
	int numOfTrailingSpaces = 0;

    bool isNegative = false;
	bool hasPositive = false;
	bool foundDecimal = false;

    while (numString[iterator] != '\0')
    {
        if (numString[iterator] == ' ')
        {
			if (foundDecimal == false)
			{
				numOfLeadingSpaces++;
			}
			else
			{
				numOfTrailingSpaces++;
			}
        }
        else if (numString[iterator] == '-')
        {
            isNegative = true;
        }
        else if (numString[iterator] == '+')
        {
            hasPositive = true;
        }
        else if (numString[iterator] == '.')
        {
			foundDecimal = true;
			break;
        }
        else if ((numString[iterator] < '0') || (numString[iterator] > '9'))
        {
            return false;
        }
        else
        {
            numOfChars++;
        }

        iterator++;
    }

    int chartist = 0;
    int pow = 1;

    for (int j = 0; j < numOfChars; j++)
    {
        pow *= 10;
    }

    pow /= 10;

    int k = numOfLeadingSpaces;

    if ((isNegative) || (hasPositive))
    {
        k++;
    }

	if (foundDecimal)
	{
		while (numString[k] != '.')
		{
			chartist = chartist + (pow * (numString[k] - '0'));
			k++;
			pow /= 10;
		}

	}
	else
	{
		int x = 0;
		while (numString[x] != '\0')
		{
			if ((numString[x] != ' ') && (numString[x] != '-'))
			{
				chartist = chartist + (pow * (numString[x] - '0'));
				pow /= 10;
			}

			x++;
		}
	}

	if (isNegative)
	{
		chartist *= -1;
	}
	
	c = chartist;

    return true;
}
