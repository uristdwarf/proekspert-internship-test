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
	int i = 0;
	bool first_run = true;
	FILE *file = fopen(argv[1], "r");
	while ((c = getc(file)) != EOF) {
		if (i == 312 / 4 || first_run) {
			printf("\n");
			i = 0;
			first_run = false;
		} else {
			i++;
		}
		if (c == '0') {
			zeroes++;
			printf("0");
		}
		else {
			ones++;
			printf("1");
		}
	}
	rewind(file);
	fclose(file);
	printf("\nwidth?: %d\n", width / 4);
	printf("ones: %d\n", ones);
	printf("zeroes: %d\n", zeroes);
	return 0;
}
