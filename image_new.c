#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("USAGE: image <text-file>\n");
		return 1;
	}

	int c;
	int width = 0;
	int zeroes = 0;
	int ones = 1;
	FILE *file = fopen(argv[1], "r");
	for (int i = 0; i < 10; i++) {
		int j = 0;
		bool first_run = true;
		while ((c = getc(file)) != EOF) {
			if (j == i || first_run) {
				//printf("\n");
				j = 0;
				first_run = false;
			}
			else
				j++;
			if (c == '0') {
				//zeroes++;
				//printf("0");
			}
			else {
				//ones++;
				//printf("1");
			}
		}
		printf("\ni = %d, j = %d", i, j);
		if (i == j) {
			printf("\nwidth?: %d\n", i);
		}
		rewind(file);
	}
	fclose(file);
	printf("ones: %d\n", ones);
	printf("zeroes: %d\n", zeroes);
	return 0;
}
