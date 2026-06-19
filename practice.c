#include <stdio.h>
#include <string.h>

int main(void) {
	char s[100005];
	if (fgets(s, sizeof s, stdin) == NULL) return 0;

	int counts[26] = {0};
	for (int i = 0; s[i] && s[i] != '\n'; ++i) {
		if (s[i] >= 'a' && s[i] <= 'z')
			counts[s[i] - 'a']++;
	}

	for (int i = 0; i < 26; ++i) {
		if (counts[i] > 0)
			printf("%c : %d\n", 'a' + i, counts[i]);
	}

	return 0;
}

