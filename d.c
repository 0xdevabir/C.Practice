#include <stdio.h>

struct movie {
	int id;
	char name[100];
	int duration;
	char language[100];
};

int main(void) {
	struct movie movies[5];
	int minimumDuration;

	for (int i = 0; i < 5; i++) {
		scanf("%d %99s %d %99s", &movies[i].id, movies[i].name,
			  &movies[i].duration, movies[i].language);

		if (i == 0 || movies[i].duration < minimumDuration) {
			minimumDuration = movies[i].duration;
		}
	}

	for (int i = 0; i < 5; i++) {
		if (movies[i].duration == minimumDuration) {
			printf("%s\n", movies[i].name);
		}
	}

	return 0;
}
