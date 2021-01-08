// ----------------------------- driver.cpp -----------------------------------

// James Truong CSS501A

// Created: 15/10/2020

// Last Modified: 31/10/2020

// ----------------------------------------------------------------------------

// A driver that reads two strings from an input file and computes the longest
// common subsequence length and the resulting string and prints them. Accepts
// user inputs for testing the time complexity of iterating and recursively
// iterating the longest common sequence of a string of length 1 to user input
// of 1 to user from the same input file and prints out the time it takes for
// each iteration to compute a string size of 1 to input string length.

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.
// Given input file must contain at least 2 strings.
// Assumes user input for the lcs_it function is greater than zero and
// less than or equal to the string lengths of the smallest given string.
// Assumes user input for lcs_re function is greater than zero and less than
// 20 due to runtime.

// ----------------------------------------------------------------------------

#include <iostream>
#include <fstream>  // for read/write files
#include <ctime>  // for logging function time
using namespace std;

const string INPUT_FILE = "input.txt";

/**Returns the length of the longest common subsequence between string X with
* length n and string Y with length m using the given 2D array C. If n is less
* than length of string X and/or m is less than length of string Y, returns the
* lcs between the substring of X with length n and the substring of Y with
* length m.
* precondition: C is a n by m array. n <= X length and m <= Y length.
* postcondition: a length of the longest common subsequence between X and Y.
*/
int lcs_it(int** C, string X, string Y, int m, int n);

/**Returns the string representing longest common subsequence between string X
* with length n and string Y with length m using the given 2D array C. If n is
* less than length of string X and/or m is less than length of string Y,
* returns the lcs between the substring of X with length n and the substring
* of Y with length m.
* precondition: C is a n by m array. n <= X length and m <= Y length.
* postcondition: a string that represents the longest common subsequence
* between string X and Y.
*/
string backtrack(int** C, string X, string Y, int m, int n);

/**Returns the length of the longest common subsequence between string X with
* length n and string Y with length m. If n is less than length of string X
* and/or m is less than length of string Y, returns the lcs between the
* substring of X with length n and the substring of Y with length m.
* precondition: n <= X length and m <= Y length.
* postcondition: a length of the longest common subsequence between X and Y.
*/
int lcs_it_test(string X, string Y, int m, int n);

/**Returns the length of the longest common subsequence between string X with
* length n and string Y with length m. If n is less than length of string X
* and/or m is less than length of string Y, returns the lcs between the
* substring of X with length n and the substring of Y with length m.
* precondition: n <= X length and m <= Y length.
* postcondition: a length of the longest common subsequence between X and Y.
*/
int lcs_re(string X, string Y, int m, int n);


int main()
{
	// Part 1
	string X, Y;
	ifstream infile;
	infile.open(INPUT_FILE, ios::in);
	if (infile.is_open())
	{
		infile >> X >> Y;
	}

	int m = X.size();

	int n = Y.size();

	int** C = new int* [m + 1];
	for (int i = 0; i < m + 1; ++i)
	{
		C[i] = new int[n + 1] { 0 };
	}

	int len = lcs_it(C, X, Y, m, n);

	cout << "X is " << X << endl;
	cout << "Y is " << Y << endl;
	cout << "LCS length is " << len << endl;
	cout << "LCS is " << backtrack(C, X, Y, m, n) << endl << endl << endl;

	// checking output is the same for both lcs_it and lcs_re
	int test_it_output = lcs_it_test("JAES", "JAMES", 4, 5);
	int test_re_output = lcs_re("JAES", "JAMES", 4, 5);
	if (test_it_output != test_re_output)
	{
		cout << "fails to have the same output for iterative and recursive " \
			"functions for lcs." << endl;
		cout << "lcs_it results: " << test_it_output << endl;
		cout << "lcs_re results: " << test_re_output << endl;
	}

	// Part 2
	int trial_it;
	int trial_re;
	cout << "Enter trial time for iterative version (less than min(|X|, |Y|))"
		<< endl;
	cin >> trial_it;
	cout << "Enter trial time for recursive version (less than 20)" << endl;
	cin >> trial_re;

	double start_s, stop_s;

	// iterative test
	for (int i = 1; i <= trial_it; ++i)
	{
		start_s = clock();
		lcs_it_test(X, Y, i, i);
		stop_s = clock();

		clog << i << "\t" << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000
			<< endl;
	}

	cout << endl;

	// recursive test
	for (int i = 1; i <= trial_re; ++i)
	{
		start_s = clock();
		lcs_re(X, Y, i, i);
		stop_s = clock();

		clog << i << "\t" << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000
			<< endl;
	}
}

/**Returns the length of the longest common subsequence between string X with
* length n and string Y with length m using the given 2D array C. If n is less
* than length of string X and/or m is less than length of string Y, returns the
* lcs between the substring of X with length n and the substring of Y with
* length m.
* precondition: C is a n by m array. n <= X length and m <= Y length.
* postcondition: a length of the longest common subsequence between X and Y.
*/
int lcs_it(int** C, string X, string Y, int m, int n)
{
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (X[i - 1] == Y[j - 1])
			{
				C[i][j] = C[i - 1][j - 1] + 1;
			}
			else
			{
				C[i][j] = max(C[i][j - 1], C[i - 1][j]);
			}
		}
	}
	return C[m][n];
}

/**Returns the string representing longest common subsequence between string X
* with length n and string Y with length m using the given 2D array C. If n is
* less than length of string X and/or m is less than length of string Y,
* returns the lcs between the substring of X with length n and the substring
* of Y with length m.
* precondition: C is a n by m array. n <= X length and m <= Y length.
* postcondition: a string that represents the longest common subsequence
* between string X and Y.
*/
string backtrack(int** C, string X, string Y, int m, int n)
{
	if (m < 0 || n < 0)
	{
		return "";
	}
	else if (X[m] == Y[n])
	{
		return backtrack(C, X, Y, m - 1, n - 1) + X[m];
	}
	else if (C[m][n - 1] > C[m - 1][n])
	{
		return backtrack(C, X, Y, m, n - 1);
	}
	else
	{
		return backtrack(C, X, Y, m - 1, n);
	}
}

/**Returns the length of the longest common subsequence between string X with
* length n and string Y with length m. If n is less than length of string X
* and/or m is less than length of string Y, returns the lcs between the
* substring of X with length n and the substring of Y with length m.
* precondition: n <= X length and m <= Y length.
* postcondition: a length of the longest common subsequence between X and Y.
*/
int lcs_it_test(string X, string Y, int m, int n)
{
	// for initializing a 2D array, you need pointers to a pointer of arrays
	int** C = new int* [m + 1];
	for (int i = 0; i <= m; ++i)
	{
		C[i] = new int[n + 1] { 0 };
	}

	// traverse the array
	int len = lcs_it(C, X, Y, m, n);

	// must delete each allocated array then the array that carrys them to free memory
	for (int i = 0; i <= m; ++i)
	{
		// to free the subarray
		delete[] C[i];
	}
	// to free the array of pointers
	delete[] C;
	return len;
}

/**Returns the length of the longest common subsequence between string X with
* length n and string Y with length m. If n is less than length of string X
* and/or m is less than length of string Y, returns the lcs between the
* substring of X with length n and the substring of Y with length m.
* precondition: n <= X length and m <= Y length.
* postcondition: a length of the longest common subsequence between X and Y.
*/
int lcs_re(string X, string Y, int m, int n)
{
	if (m == 0 || n == 0)
	{
		return 0;
	}
	else if (X[m - 1] == Y[n - 1])
	{
		return 1 + lcs_re(X, Y, m - 1, n - 1);
	}
	else
	{
		return max(lcs_re(X, Y, m - 1, n), lcs_re(X, Y, m, n - 1));
	}
}