#include <stdio.h>

int main() {
	int n = 0;
	while (n != 75) {
		if (n == 25) {
			printf("close\n");
			scanf("%d", &n);
			continue;
		} else if (n == 125) {
			printf("open\n");
			scanf("%d", &n);
			continue;
		} else {
			scanf("%d", &n);
			continue;
		}
	}
	printf("program end\n");
	return 0;
}