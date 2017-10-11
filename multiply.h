#include "stdafx.h"

#include <iostream>
using namespace std;

void testMultiply();
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int sizeOfInt(int number);
bool numberToArray(char numArray[], int number, int arrLength, int decPoint, bool isPositive);
int stripNegative(int num);
int convertFracToDec(int num, int den);
int addDigitToNum(int first, int last);
int reverseOrderOfInt(int num);
void display_array(char arr[]);

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	int numerator1 = 0;
	int denominator1 = 0;
	int numerator2 = 0;
	int denominator2 = 0;
	int finalNumerator = 0;
	int finalDenominator = 0;
	int finalChar = 0;
	int finalMantissa = 0;
	bool isNegative = false;

	//Check to see if a number is zero
	if (c1 == 0 && n1 == 0 || c2 == 0 && n2 == 0)
	{
		result[0] = 0 + '0';
		result[1] = '\0';
		display_array(result);
		return true;
	}

	//check for overflow
	unsigned long c1_test = c1;
	unsigned long c2_test = c2;
	unsigned long c_test = 0;
	c_test = c2_test * c1_test;
	if (c_test / c1_test != c2_test)
	{
		return false;

	}
	//clear out the array
	for (int i = 0; i < len - 1; i++)
	{
		result[i] = ' ';
	}
	//check to see if the end result will be negative or poitive and then strop negatives
	if (c1 < 0 && c2 > 0 || c1 > 0 && c2 < 0)
	{
		isNegative = true;
	}
	//strip the negatives
	c1 = stripNegative(c1);
	c2 = stripNegative(c2);
	// if the charictoristic is not 0 then convert to improper fraction
	if (c1 == 0)
	{
		//fraction with no whole number 
		numerator1 = n1;
		denominator1 = d1;
	}
	else if (n1 == 0)
	{
		//whole number no fraction 3 = 3/1
		numerator1 = c1;
		denominator1 = 1;
	}
	else
	{
		//mixed fraction 3 1/2 = 7/2
		numerator1 = (c1 * d1) + n1;
		denominator1 = d1;
	}
	//same as above for other fraction, could convert these into one function and pass values
	if (c2 == 0)
	{
		numerator2 = n2;
		denominator2 = d2;
	}
	else if (n2 == 0)
	{
		numerator2 = c2;
		denominator2 = 1;
	}
	else
	{
		numerator2 = (c2 * d2) + n2;
		denominator2 = d2;
	}

	//multiply the fractions
	finalNumerator = numerator1 * numerator2;
	finalDenominator = denominator1 * denominator2;

	//get the mixed fraction
	if (finalNumerator > finalDenominator)
	{
		finalChar = finalNumerator / finalDenominator;
		finalNumerator = finalNumerator % finalDenominator;
	}
	//if the result isnt fully reduced in a while number calculate mantissa
	if (finalNumerator != 0)
	{
		finalMantissa = convertFracToDec(finalNumerator, finalDenominator);
	}
	//put the charict and mantissa in provided array
	numberToArray(result, finalChar, finalMantissa, len, isNegative);

	//debug method
	//display_array(result);

	return false;
}
//--
void display_array(char arr[])
{

	for (int i = 0; arr[i] != '\0'; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

}
int convertFracToDec(int num, int den)
{
	int remainder = 0;
	int mantissa = 0;


	remainder = num * 10;
	while (true)
	{
		if (remainder % den == 0)
		{
			mantissa = addDigitToNum(mantissa, remainder / den);
			return mantissa;
		}
		mantissa = addDigitToNum(mantissa, remainder / den);
		remainder = (remainder % den) * 10;
	}
}

int addDigitToNum(int first, int last)
{
	first *= 10;
	first += last;
	return first;
}

bool numberToArray(char result[], int c, int m, int Len, bool isNegative)
{
	//check if any we dont need to create an array
	bool zeroChar = false;
	bool zeroMant = false;
	int endPosition = 0;
	int totalSize = sizeOfInt(c) + sizeOfInt(m) + 1;
	if (c == 0)
	{
		zeroChar = true;
		totalSize += 1;
	}
	if (m == 0)
	{
		zeroMant = true;
		totalSize -= 1;
	}
	//add a negative to if it is true
	if (isNegative)
	{
		result[0] = '-';
		endPosition = 1;
		totalSize += 1;
	}
	//reverse size of int so when i add to array its in the right order
	int charict = reverseOrderOfInt(c);
	int mantissa = reverseOrderOfInt(m);
	//fill the array

	bool dotAdded = false;
	result[Len - 1] = '\0';
	for (int i = endPosition; result[i] != '\0'; i++)
	{
		if (charict != 0)
		{
			result[i] = (charict % 10) + '0';
			charict = charict / 10;
		}
		else if (charict == 0 && dotAdded == false && zeroMant == false)
		{
			result[i] = '.';
			dotAdded = true;
		}
		else if (charict == 0 && mantissa != 0)
		{
			result[i] = (mantissa % 10) + '0';
			mantissa = mantissa / 10;
		}
		else if (mantissa == 0)
		{
			result[i] = '\0';
			break;
		}

	}

	return true;
}
//----
int sizeOfInt(int number)
{
	// takes an int and returns how many digits are in the int
	int count = 0;
	while (number != 0)
	{
		count++;
		number /= 10;
	}
	return count;
}
//----
int stripNegative(int num)
{
	if (num < 0)
	{
		num *= (-1);
	}
	return num;
}
//----
int reverseOrderOfInt(int num)
{
	int new_num = 0;
	while (num > 0)
	{
		new_num = new_num * 10 + (num % 10);
		num = num / 10;
	}
	return new_num;
}