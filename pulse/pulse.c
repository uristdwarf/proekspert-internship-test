#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("USAGE: pulse <text-file>\n");
		return 1;
	}

	int c;
	int l_paranths = 0;
	int r_paranths = 0;
	int length = 0;
	bool still_valid = true;
	

	FILE *file = fopen(argv[1], "r");
	while ((c = getc(file)) != EOF) {
		switch (c) {
			case '(':
				l_paranths++;
				length++;
				break;
			case ')':
				if (l_paranths > 0) {
					l_paranths--;
					length += 1;
					break;
				} else {
					still_valid = false;
					break;
				}
		}
		if (!still_valid) {
			break;
		}
	}
	fclose(file);
	printf("coefficient: %d\n", length);
	return 0;
}
