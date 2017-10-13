#include <iostream>
#include "mantissa.h"
#pragma once

using namespace std;

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	//can we divide?
	bool retval = true;
	//step 1: put numbers into this form:
	//  x1   x2
	//  __ / __
	//  d1   d2
	unsigned int x1 = ((c1 * d1) + n1);
	unsigned int x2 = ((c2 * d2) + n2);
	// this translates to:
	//  x1   d2    top
	//  __ * __ = ______
	//  d1   x2   bottom
	unsigned int top = (x1 * d2);
	unsigned int bottom = (d1 * x2);
	//step 2: now we can divide.
	unsigned int divide = (top / bottom);
	//cout << divide << endl;
	//turn the divide into a char array
	//turn the remainder into a char array
	int num2 = divide;
	char* p_arr3 = new char[len];
	int divCounter = 0;
	while (num2 != 0)
	{
		int last = num2 % 10;
		char lsd = last + '0';
		p_arr3[divCounter] = lsd;
		divCounter++;
		num2 = num2 / 10;
	}
	char* p_arr4 = new char[len];
	int numDivDigits = divCounter;
	//cout << remCounter << endl;
	for (int i = 0; i < numDivDigits; i++)
	{
		p_arr4[i] = p_arr3[divCounter - 1];
		divCounter--;
	}
	for (int i = numDivDigits; i < len; i++)
	{
		p_arr4[i] = '0';
	}

	int remainder = (top % bottom);
	//cout << remainder << endl;

	//turn the remainder into a char array
	int num = remainder;
	char* p_arr = new char[len];
	int remCounter = 0;
	while (num != 0)
	{
		int last = num % 10;
		char lsd = last + '0';
		p_arr[remCounter] = lsd;
		remCounter++;
		num = num / 10;
	}
	char* p_arr2 = new char[len];
	int numRemDigits = remCounter;
	//cout << remCounter << endl;
	for (int i = 0; i < numRemDigits; i++)
	{
		p_arr2[i] = p_arr[remCounter - 1];
		remCounter--;
	}
	for (int i = numRemDigits; i < len; i++)
	{
		p_arr2[i] = '0';
	}

	//Step 3: enter the value to the results
	//this helps us know how many chars are in the results
	int resultCounter = 0;
	for (int i = 0; i < numDivDigits; i++)
	{
		result[i] = p_arr4[i];
		resultCounter++;
	}
	if (resultCounter >(len - 2))//***use resultcounter instead of result.size()
	{
		cout << "ERROR - not enough length in results!" << endl;
		retval = false;
	}
	else if (resultCounter == (len - 2))//***use resultcounter instead of result.size()
	{
		result[len] = '/0';
		retval = true;
	}
	else //we have more to fill
	{
		//add decimal
		result[resultCounter] = '.';
		resultCounter++;
		//loop while adding remainder
		int remainderCounter = 0;
		while (resultCounter < (len - 2))
		{
			result[resultCounter] = p_arr2[remainderCounter];
			remainderCounter++;
			resultCounter++;
		}
		result[len - 1] = '\0';//***remainder is broken - 1/2 translates to .1 - do long division
		retval = true;
	}
	delete[] p_arr;
	delete[] p_arr2;
	delete[] p_arr3;
	delete[] p_arr4;
	return retval;
}
