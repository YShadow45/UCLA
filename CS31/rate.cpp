#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <cassert>
#include <cctype>
using namespace std;

const int MAX_WORD_LENGTH = 20;
void isValidPattern(char word1[][MAX_WORD_LENGTH + 1], 
	char word2[][MAX_WORD_LENGTH + 1], 
	int seperation[],
	int nPatterns);
int makeProper(char word1[][MAX_WORD_LENGTH + 1],
	char word2[][MAX_WORD_LENGTH + 1],
	int separation[],
	int nPatterns);
int rate(const char document[],
	const char word1[][MAX_WORD_LENGTH + 1],
	const char word2[][MAX_WORD_LENGTH + 1],
	const int separation[],
	int nPatterns);

int main()
{
	char wor1[8][MAX_WORD_LENGTH + 1] = {
		"mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS"
	};
	char wor2[8][MAX_WORD_LENGTH + 1] = {
		"scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT"
	};
	int separations[8] = {
		1, 3, 0, 2, 1, 0, 12, 0
	};
	int nPattern = 8;
	assert(makeProper(wor1, wor2, separations, nPattern) == 4 && wor2[2][1] == 'l');  // plot
	assert(makeProper(wor1, wor2, separations, nPattern) == 4 && wor2[3][2] == 'd'); // mad

	//int makeProper
	const int TEST1_NRULES = 4;
	char test1w1[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"mad",       "deranged", "nefarious", "have"
	};
	char test1w2[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"scientist", "robot",    "plot",      "mad"
	};
	int test1dist[TEST1_NRULES] = {
		1,           3,          0,           12
	};

	//int makeProper(char word1[][MAX_WORD_LENGTH + 1],

	assert(rate(" ",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);  //to test the empty input
	assert(rate(" ",
		test1w1, test1w2, test1dist, -1) == 0);  //to test the negative nPatterns
	assert(rate("UCLA m1ad scie1n-ti3s?t relea",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);  //to test the input with a non-letter in the middle
	assert(rate("The mAd UCLA SciEntIst unleashed a deranged evil giant robot.",  //to test the input with some upper case
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("**** 2018 ****",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("  That plot: NEFARIOUS!",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("deranged deranged robot deranged robot robot",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	cout << "All tests succeeded" << endl;
}

void isValidPattern(char word1[][MAX_WORD_LENGTH + 1],
	char word2[][MAX_WORD_LENGTH + 1],
	int seperation[],
	int n)
{
	for (int j = 0; word1[n][j] != '\0'; j++)
	{
		word1[n][j] = tolower(word1[n][j]);
		if (!(isalpha(word1[n][j])))
			word1[n][0] = '\0';
	}
	for (int j = 0; word2[n][j] != '\0'; j++)
		{
		word2[n][j] = tolower(word2[n][j]);
		if (!(isalpha(word2[n][j])))
			word1[n][0] = '\0';
		}
	if (seperation[n] < 0)
		word1[n][0] = '\0';
}

int makeProper(char word1[][MAX_WORD_LENGTH + 1],
	char word2[][MAX_WORD_LENGTH + 1],
	int separation[],
	int nPatterns)
{
	for (int i = 0; i < nPatterns; i++)
	{
		isValidPattern(word1, word2, separation, i);
	}

	for (int i = 0; i < nPatterns; i++)
	{
		for (int j = i + 1; j < nPatterns; j++)
		{
			if ((strcmp(word1[i], word1[j]) == 0 && strcmp(word2[i], word2[j]) == 0)||
				(strcmp(word1[i], word2[j]) == 0 && strcmp(word2[i], word1[j]) == 0))
				if (separation[i] >= separation[j])
					word1[j][0] = '\0';
		}
	}

	for (int i = 0; i < nPatterns; i++)
	{
		for (int j = 0; j < nPatterns - 1; j++)
			if (word1[j][0] == '\0' && word1[j + 1][0] != '\0')
			{
				swap(word1[j], word1[j + 1]);
				swap(word2[j], word2[j + 1]);
				swap(separation[j], separation[j + 1]);
			}
	}
	
	int count = 0;
	for (int i = 0; word1[i][0] != '\0'; i++)
	{
		count++;
	}
	return count;
}


int rate(const char document[],
	const char word1[][MAX_WORD_LENGTH + 1],
	const char word2[][MAX_WORD_LENGTH + 1],
	const int separation[],
	int nPatterns)
{
	int rate = 0;
	char document1[250];
	int j = 0;
	for (int i = 0; i < 250; i++)  //create a new document array with only lower-case letters and space
	{
		if (document[i] == '\0')
			break;
		if (document[i] == ' ' || isalpha(document[i]))
		{
			if (isalpha(document[i]))
				document1[j] = tolower(document[i]);
			else
				document1[j] = document[i];
			j++;
		}
	}

	char newDocument[251][251];
	int pos = 0, r = 0, c = 0;  //create a 2D char array to separate the words in every row of the array
	while (pos < j)
	{
		while (isalpha(document1[pos]))
		{
			if (pos == j)
			{
				newDocument[r][c] = '\0';
				break;
			}
			newDocument[r][c] = document1[pos];
			c++;
			pos++;
			if (pos == j)
			{
				newDocument[r][c] = '\0';
				break;
			}
		}
		if (pos == j)
		{
			newDocument[r][c] = '\0';
			break;
		}
		while (document1[pos] == ' ')
		{
			if (pos == j)
			{
				newDocument[r][c] = '\0';
				break;
			}
			pos++;
			if (pos == j)
			{
				newDocument[r][c] = '\0';
				break;
			}
		}
		newDocument[r][c] = '\0';
		r++;
		c = 0;
	}

	
	
	int num = 0;  
	while (num < nPatterns)  //traverse the array and calculate the rate
	{
		int temp = num;
		for (int a = 0; a < r + 1; a++)
		{
			for (int b = a + 1; b < r + 1; b++)
			{
				if ((strcmp(newDocument[a], word1[num]) == 0 && strcmp(newDocument[b], word2[num]) == 0) ||
					(strcmp(newDocument[a], word2[num]) == 0 && strcmp(newDocument[b], word1[num]) == 0))
					if (b - a - 1 <= separation[num])
					{
						rate++;
						num++;
					}
			}
		}
		if (temp == num)  //if num is not changed, num++; if num is changed during the loop, exucate the loop again.
			num++;
	}
	return rate;
}

