#include<string>
#include<cassert>
#include<iostream>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);

int main()
{
	//int appendToAll(string a[], int n, string value);
	string test[4] = { "abc","abs","abcd","bcde" };
	assert(appendToAll(test, -2, "!!!") == -1);  //a negative input would return -1
	assert(appendToAll(test, 3, "???") == 3 && test[2] == "abcd???");
	assert(appendToAll(test, 1, "???") == 1 && test[0] == "abc??????");

	//int lookup(const string a[], int n, string target);
	string test1[5] = { "aBc","bcde","abc","abcd","bcde" };
	assert(lookup(test1, 0, "aBc") == -1);
	assert(lookup(test1, -5, "aBc") == -1); //invalid input
	assert(lookup(test1, 5, "bcde") == 1); //two same strings
	assert(lookup(test1, 3, "abc") == 2); //different cases
	assert(lookup(test1, 5, "aBcd") == -1); //no such string

	//int positionOfMax(const string a[], int n);
	string test2[5] = { "aBc","bcde","bcd","abcd","bcdef" };
	assert(positionOfMax(test2, 0) == -1); //invalide input
	assert(positionOfMax(test2, 3) == 1);
	assert(positionOfMax(test2, 5) == 4);

	//int rotateLeft(string a[], int n, int pos);
	string test3[5] = { "aBc","bcde","bcd","abcd","bcdE" };
	assert(rotateLeft(test3, 2, 2) == -1 && test3[0] == "aBc");
	assert(rotateLeft(test3, 2, -1) == -1 && test3[2] == "bcd");
	assert(rotateLeft(test3, 0, 2) == -1);  //invalid inputs
	assert(rotateLeft(test3, 2, 0) == 0 && test3[1] == "aBc");
	string test31[5] = { "aBc","bcde","bcd","abcd","bcdE" };
	assert(rotateLeft(test31, 5, 2) == 2 && test31[3] == "bcdE");
	string test32[5] = { "aBc","bcde","bcd","abcd","bcdE" };
	assert(rotateLeft(test32, 4, 1) == 1 && test32[0] == "aBc" && test32[1] == "bcd");

	//int countRuns(const string a[], int n);
	string test4[8] = { "LOL","LOL","DOTA","WAR3","War3","SC2","SC2","SC2" };
	assert(countRuns(test4, -1) == -1); //invalid input
	assert(countRuns(test4, 0) == 0);
	assert(countRuns(test4, 5) == 4);
	assert(countRuns(test4, 8) == 5);

	//int flip(string a[], int n);
	string test5[6] = { "LOL","DOTA","WAR3","War3","SC2","CSGO" };
	assert(flip(test5, -1) == -1 && test5[0] == "LOL"); //invalid input
	assert(flip(test5, 0) == 0 && test5[0] == "LOL");
	assert(flip(test5, 3) == 3 && test5[2] == "LOL");
	string test51[6] = { "LOL","DOTA","WAR3","War3","SC2","CSGO" };
	assert(flip(test51, 5) == 5 && test51[3] == "DOTA");

	//int differ(const string a1[], int n1, const string a2[], int n2);
	string folks[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
	string group[5] = { "betty", "john", "dianne", "", "xavier" };
	assert(differ(folks, -1, group, 0) == -1); //invalid input
	assert(differ(folks, 0, group, 0) == 0);
	assert(differ(folks, 6, group, 5) == 2);
	assert(differ(folks, 2, group, 1) == 1);

	//int subsequence(const string a1[], int n1, const string a2[], int n2);
	string names[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
	string names1[10] = { "gavin", "kevin", "greg" };
	string names2[10] = { "eleni", "greg" };
	assert(subsequence(names, 2, names1, 3) == -1);
	assert(subsequence(names, -1, names1, 0) == -1); //invalid input
	assert(subsequence(names, 2, names1, 0) == 0); //zero elements in names2
	assert(subsequence(names, 6, names1, 3) == 1);
	assert(subsequence(names, 5, names2, 2) == -1);

	//int lookupAny(const string a1[], int n1, const string a2[], int n2);
	string name[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
	string set1[10] = { "dianne", "betty", "greg", "gavin" };
	string set2[10] = { "xavier", "ed" };
	assert(lookupAny(name, -1, set2, 2) == -1);
	assert(lookupAny(name, 6, set2, -1) == -1);
	assert(lookupAny(name, 6, set1, 4) == 1);
	assert(lookupAny(name, 6, set2, 2) == -1);

	//int divide(string a[], int n, string divider);
	string test6[6] = { "LOL","DOTA","WAR3","War3","SC2","CSGO" };
	assert(divide(test6, 0, "E") == 0 && test6[0] == "LOL");
	assert(divide(test6, -1, "E") == -1 && test6[0] == "LOL");
	assert(divide(test6, 5, "M") == 2);
	string test61[6] = { "LOL","DOTA","WAR3","War3","SC2","CSGO" };
	assert(divide(test61, 6, "M") == 3);
	string test62[6] = { "LOL","DOTA","WAR3","War3","SC2","CSGO" };
	assert(divide(test62, 3, "E") == 1 && test62[0] == "DOTA");

	cout << "All tests succeeded!" << endl;
}


int appendToAll(string a[], int n, string value)
{
	if (n < 0)
		return -1;
	for (size_t k = 0; k < n; k++)
		a[k] += value;
	return n;
}

int lookup(const string a[], int n, string target)
{
	if (n <= 0)
		return -1;
	for (size_t k = 0; k < n; k++)
		if (a[k] == target)
			return k;
	return -1;
}

int positionOfMax(const string a[], int n)
{
	if (n <= 0)
		return -1;
	int pos = 0;
	string max = a[0];
	for (size_t k = 0; k < n; k++)
	{
		if (a[k] > max)
		{
			max = a[k];
			pos = k;
		}
	}
	return pos;
}

int rotateLeft(string a[], int n, int pos)
{
	if (n < 0 || pos > n - 1 || pos < 0)
		return -1;
	string temp = a[pos];
	for (size_t k = pos; k < n - 1; k++)
		a[k] = a[k + 1];
	a[n - 1] = temp;
	return pos;
}

int countRuns(const string a[], int n)
{
	if (n < 0)
		return -1;
	if (n == 0)
		return 0;
	int count = 1;
	for (size_t k = 0; k < n - 1; k++)
	{
		if (a[k] != a[k + 1])
			count += 1;
	}
	return count;
}

int flip(string a[], int n)
{
	if (n < 0)
		return -1;
	if (n % 2 == 0)  
		for (int k = 0; k < (n / 2) - 1; k++)
			swap(a[(n-1) / 2 - k], a[n / 2 + k]);
	else
		for (int k = 1; k < (n+1) / 2; k++)
			swap(a[(n-1) / 2 - k], a[(n-1) / 2 + k]);
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;
	int n = 0;
	if (n1 <= n2)
		n = n1;
	else
		n = n2;
	int pos = n - 1;
	for (size_t k = 0; k < n; k++)
	{
		if (a1[k] != a2[k])
			return k;
	}
	return n;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0 || n1 < n2)
		return -1;
	int k = 0;
	int i = 0;
	if (n2 == 0)
		return 0;
	while (k <= n1 - n2)
	{
		while (a1[k + i] == a2[i])
		{
			if (i == n2 - 1)
				return k;
			i++;
		}
		i = 0;
		k++;
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;
	for (size_t k = 0; k < n1; k++)
	{
		for (size_t j = 0; j < n2; j++)
		{
			if (a1[k] == a2[j])
				return k;
		}
	}
	return -1;
}

int divide(string a[], int n, string divider)
{
	if (n < 0)
		return -1;
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - 1; j++)
		{
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
		}
	for (int k = 0; k < n; k++)
		if (a[k] >= divider)
			return k;
	return n;
}