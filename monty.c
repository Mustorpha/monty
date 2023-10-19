/**
 * main - the main program entry
 * @argc: number of CL argument
 * @argv: array of CL arguments
 * return:
*/
int main(int argc, char *argv[]) {
	FILE *file;
	
	if (argc != 2) {
		printf("Usage: %s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL) {
		perror("Error: Can't open file %s", argv[0]);
		return 1; 
	}

	char line[1024]; // Adjust the buffer size as needed

	while (fgets(line, sizeof(line), file)) {
		printf("%s", line);
	}

	fclose(file);
	return 0; // Return success code
}
