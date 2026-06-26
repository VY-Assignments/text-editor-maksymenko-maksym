#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLENGTH 100

int main() {
	int	choice;
	char* buffer = malloc(MAXLENGTH * sizeof(char));

	if (buffer == NULL) {
		printf("Memory allocation failed!\n");
		return 1;
	}

	do
	{
		printf("1. Enter password\n");
		printf("2. exit\n");
		printf("Select an option.\n");
		if (fgets(buffer, MAXLENGTH, stdin) == NULL) {
			choice = 2;
			break;
		}
		if (buffer[0] == '\n' || buffer[0] == '\0') {
			printf("Invalid input\n");
			continue;
		}
		switch (buffer[0]) {
		case '1':
			choice = 1;
			break;
		case '2':
			choice = 2;
			break;
		default:
			choice = 0;
			break;
		}
		if (choice == 2) {
			printf("Exiting program\n");
		}
		else if (choice == 1) {
			printf("Enter password: ");
			if (fgets(buffer, MAXLENGTH, stdin) != NULL) {
				size_t len = strlen(buffer);
				if (len > 0 && buffer[len - 1] == '\n') {
					buffer[len - 1] = '\0';
					len--;
				}
				int score = 0;
				int has_space = 0;
				int has_lower = 0;
				int has_upper = 0;
				int has_digit = 0;
				int has_special = 0;

				int i = 0;
				while (buffer[i] != '\0') {
					char c = buffer[i];
					if (isspace(c)) {
						has_space = 1;
					}
					else if (islower(c)) {
						has_lower = 1;
					}
					else if (isupper(c)) {
						has_upper = 1;
					}
					else if (isdigit(c)) {
						has_digit = 1;
					}
					else if (ispunct(c)) {
						has_special = 1;
					}
					i++;
				}
				if (has_space) {
					score = 0;
					printf("you cant put space in password\n");
				}
				else if (len < 6) {
					score = 0;
					printf("your password should be longer than 6 symbols\n");
				}
				else {
					if (len >= 6 && len <= 10) {
						score += 1;
					}
					else if (len > 10) {
						score += 2;
					}

					if (has_upper && has_lower) {
						score += 2;
					}

					if (has_digit) {
						score += 2;
					}

					if (has_special) {
						score += 2;
					}
				}
				printf("Score: %d /8 \n", score);
				printf("Password Rate: ");
				if (score >= 6)
				{
					printf("Strong\n");
				}
				else if (score >= 4)
				{
					printf("Mediocre\n");
				}
				else
				{
					printf("Weak\n");
				}

				{
					int score = 99;
					int prosto = score + 1;
				}
			}
		}
		else {
			printf("unknown command \n");
		}
	} while (choice != 2);
	for (int i = 0; i < 1; i++) {
		free(buffer);
		buffer = NULL;
	}

	return 0;
}