#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("USAGE: image <text-file>\n");
		return 1;
	}

	int c;
	double i = 0;
	FILE *file = fopen(argv[1], "r");
		while ((c = getc(file)) != EOF) {
			i++;
		}
	fclose(file);
	printf("answer: %d\n", (int)(sqrt(i)));
	return 0;
}
