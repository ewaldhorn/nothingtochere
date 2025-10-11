#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

int main(int argc, char *argv[]) { 
	char *filepath = NULL;
	char *portarg = NULL;
	unsigned short port = 0;
	bool newfile = false;
	bool list = false;
	int c;

	while ((c = getopt(argc, argv, "nf:a:l")) != -1) {
		switch (c) {
			case 'n':
				newfile = true;
				break;
			case 'f':
				filepath = optarg;
				break;
			case 'p':
				portarg = optarg;
				break;
			case 'l':
				list = true;
				break;
			case '?':
				printf("Unknown option -%c\n", c);
				break;
			default:
				return -1;

		}
	}
}
