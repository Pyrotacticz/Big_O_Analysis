
	// checking output is the same for both lcs_it and lcs_re
	int test_it_output = lcs_it_test(X, Y, m, n);
	int test_re_output = lcs_re(X, Y, m, n);
	if (test_it_output != test_re_output)
	{
		cout << "fails to have the same output for iterative and recursive " \
			"functions for lcs." << endl;
		cout << "lcs_it results: " << test_it_output << endl;
		cout << "lcs_re results: " << test_re_output << endl;
	}