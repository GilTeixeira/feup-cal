#include "StringAlgorithms.h"


static void pre_kmp(string pattern, vector<int> & prefix)
{
	size_t m = pattern.length();
	prefix[0] = -1;
	int k = -1;
	for (int q = 1; q<m; q++) {
		while (k>-1 && pattern[k + 1] != pattern[q])
			k = prefix[k];
		if (pattern[k + 1] == pattern[q]) k = k + 1;
		prefix[q] = k;
	}
}

int kmp(string text, string pattern)
{
	bool found{ false };
	size_t m = pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	size_t n = text.length();

	int q{ -1 };
	for (int i = 0; i<n && !found; i++) {
		while (q>-1 && pattern[q + 1] != text[i])
			q = prefix[q];
		if (pattern[q + 1] == text[i])
			q++;
		if (q == m - 1) {
			found = true;
			q = prefix[q];
		}
	}
	return found;
}

int editDistance(string pattern, string text)
{
	size_t n = text.length();
	vector<int> d(n + 1);
	int old, neww;
	for (int j = 0; j <= n; j++)
		d[j] = j;
	size_t m = pattern.length();
	for (int i = 1; i <= m; i++) {
		old = d[0];
		d[0] = i;
		for (int j = 1; j <= n; j++) {
			if (pattern[i - 1] == text[j - 1]) neww = old;
			else {
				neww = min(old, d[j]);
				neww = min(neww, d[j - 1]);
				neww = neww + 1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}