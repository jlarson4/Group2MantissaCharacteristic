#include <iostream>
#pragma once

using namespace std;

void printArray(char arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i];
	}

	cout << endl;
}
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
void mymemset(char arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = '0';
	}
}
inline void easyCase(char arr[], int c1, int c2, int len)
{
	arr[0] = (c1 / c2) + '0';
	arr[1] = '.';

	for (int i = 2; i < len - 2; i++)
	{
		arr[i] = '0';
	}

	arr[len - 1] = '\0';
}

void longDivision(int top, int bottom,int len, char*& p_arr4);

void longDivision(int top, int bottom, int len, char*& p_arr2)
{
	//do long division
	p_arr2 = new char[len]; //for storing the answers

	int div1 = top * 10;
	int div2 = 0;
	int answer = 0;
	for (int i = 0; i < len; i++)
	{
		//div1 = top * 10;
		answer = div1 / bottom;
		p_arr2[i] = answer + '0';
		div2 = answer * bottom;
		div1 = (div1 - div2) * 10;
	}
}

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
	//cout << "Before" << endl;
	//printArray(result, len);
	//cout << "c1 = " << c1 << " c2 = " << c2 << " n1 = " << n1 << " n2 = " << n2 << " len = " << len << endl;

	mymemset(result, len);

	bool isNeg = false;
	if (c1 < 0)
	{
		c1 = c1 * -1;
		isNeg = true;
	}
	if (c2 < 0)
	{
		c2 = c2 * -1;
		if (isNeg == true)
			isNeg = false;
		else
			isNeg = true;
	}
	//can we divide?
	bool retval = true;
	//cannot divide by zero
	if ((c2 == 0) && (n2 == 0))
	{
		//division is not possible
		return false;
	}

	// If the numbers being passed in are integers without fractions,
	// this is the "easy" case.
	if ((c1 % c2 == 0) && (n1 == 0) && (n2 == 0))
	{
		//cout << "Easy case" << endl;
		easyCase(result, c1, c2, len);
		//cout << "After" << endl;
		//printArray(result, len);
		return true;
	}

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
	int num2 = divide;

	char* p_arr3 = new char[len];
	mymemset(p_arr3, len);
	int divCounter = 0;

	
	// If the numerator is bigger than the denominator:
	while (num2 != 0)
	{
		int last = num2 % 10;
		char lsd = last + '0';
		p_arr3[divCounter] = lsd;
		divCounter++;
		num2 = num2 / 10;

		//if the divide to big to fit in results?
		if (divCounter > len)
		{
			return false;
		}
	}

	char* p_arr4 = new char[len];
	mymemset(p_arr4, len);

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

	//cout << p_arr4 << endl;

	char* p_arr2 = new char[len];
	mymemset(p_arr2, len);

	longDivision(top, bottom, len, p_arr2);

	//Step 3: enter the value to the results
	//this helps us know how many chars are in the results
	int resultCounter = 0;
	if (isNeg == true)
	{
		result[resultCounter] = '-';
		resultCounter++;
	}
	for (int i = 0; i < numDivDigits; i++)
	{
		result[i] = p_arr4[i];
		resultCounter++;
	}
	if (resultCounter >(len - 1))//***use resultcounter instead of result.size()
	{
		cout << "ERROR - not enough length in results!" << endl;
		retval = false;
	}
	else if (resultCounter == (len - 1))//***use resultcounter instead of result.size()
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
		while (resultCounter < (len - 1))
		{
			result[resultCounter] = p_arr2[remainderCounter];
			remainderCounter++;
			resultCounter++;
		}
		result[len - 1] = '\0';//***remainder is broken - 1/2 translates to .1 - do long division
		retval = true;
	}
	
	//cout << __FUNCTION__ << " Result = " << result << endl;

	delete[] p_arr2;
	delete[] p_arr3;
	delete[] p_arr4;
	return retval;
}