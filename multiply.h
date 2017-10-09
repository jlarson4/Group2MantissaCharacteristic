#pragma once
#include <iostream>
using namespace std;

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
int sizeOfInt(int number);
bool numberToArray(char numArray[], int number, int arrLength, int decPoint, bool isPositive);
int stripNegative(int num);

bool numberToArray(char numArray[], int number, int decPoint, int arrLength, bool isPositive)
{
	bool retVal = true;
	// if the num is + then the loop should end at array index 0 if not end at 1 
	int loopEnd = 0;

	//size of the number with decimal
	int sizeOfNum = sizeOfInt(number);

	// add a - if the number is negative
	//make the loop start 1 spot farther and stop one sooner 
	if (!isPositive)
	{
		numArray[0] = '-';
		sizeOfNum++;
		loopEnd = 1;
	}

	//check to see if number fits in bounds of array +1 for \0
	if (sizeOfNum + 1 > arrLength)
	{
		retVal = false;
		return retVal;
	}

	//add the ending to the array
	numArray[sizeOfNum + 1] = '\0';

	int count = 0;
	for (int i = sizeOfNum; i >= loopEnd; i--)
	{
		if (count == decPoint)
		{
			numArray[i] = '.';
		}
		else
		{
			numArray[i] = (number % 10) + '0';
			number /= 10;
		}
		count++;
	}
	return retVal;
}
//----
void convertToMultipleOfTen(int& num, int& den)
{
	int count = 0;
	while ()
	{
		if (den % 10 == 0)
		{
			break;
		}
		count++;
	}
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
