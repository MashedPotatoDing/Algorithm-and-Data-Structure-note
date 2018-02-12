/*by Zhaobo Ding*/

int kmp(string text, string pattern) // kmp() searches text for pattern
{
	int lp = pattern.length();
	int lt = text.length();
	vector <int> next(n);

	for (int i = 1; i < lp; i++) // initialize next[]
	{
		int j = i;
		next[i + 1] = 0;
		while (j)
		{
			j = next[j];
			if (pattern[i] == pattern[j])
			{
				next[i + 1] = j + 1;
				break;
			}
		}
	}

	for (int i = 1, j = 0; i < lt; i++)
	{
		if (j < lp && text[i] == pattern[j])
		// when the next character matches directly go to the following one
			j++;
		else // otherwise see if a smaller part of pattern can match
			while (j)
			{
				j = next[j];
				if (text[i] == pattern[j])
				{
					j++;
					break;
				}
			}

		if (j == lp)
			return i - pt + 1;
		// when match the string successfully, return the position
	}

	return -1;
}