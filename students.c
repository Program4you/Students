#include <stdio.h>
#include <string.h>

typedef struct Student {
	char surname[11]; // фамилия
	char name[10]; // имя
	char patronymic[10]; // отчество
	int scores[5]; // массив с баллаи за экзамены
} Student;

// считывание студентов из файла
void readFromFile(const char *path, Student *s, int *n) {
	FILE *f = fopen(path, "r");

	int i = 0;
	char buf[100];

	while (fgets(buf, sizeof(buf), f)) {
		sscanf(buf, "%s %s %s %d %d %d %d %d", &s[i].surname, &s[i].name, &s[i].patronymic, &s[i].scores[0], &s[i].scores[1], &s[i].scores[2], &s[i].scores[3], &s[i].scores[4]);
		i++;
	}

	fclose(f);

	*n = i;
}

// сортировка студентов по ФИО
void sortStudents(Student *s, int n) {
	int isSorted = 0;

	while (!isSorted) {
		isSorted = 1;

		for (int i = 0; i < n - 1; i++) {
			if (strcmp(s[i].surname, s[i + 1].surname) > 0 || 
				strcmp(s[i].surname, s[i + 1].surname) == 0 && strcmp(s[i].name, s[i + 1].name) > 0 ||
				strcmp(s[i].surname, s[i + 1].surname) == 0 && strcmp(s[i].name, s[i + 1].name) == 0 && strcmp(s[i].patronymic, s[i + 1].patronymic) > 0) {
				Student tmp = s[i];
				s[i] = s[i + 1];
				s[i + 1] = tmp;
				isSorted = 0;
			}
		}
	}
}

// вывод студентов
void printStudents(Student *s, int n) {
	printf("+-------------+------------+------------+-------------------+---------+\n");
	printf("|   Surname   |    Name    | Patronymic | Scores in session | Average |\n");
	printf("+-------------+------------+------------+---+---+---+---+---+---------+\n");
	for (int i = 0; i < n; i++) {
		double avg = 0;

		for (int j = 0; j < 5; j++)
			avg += s[i].scores[j];

		avg /= 5;

		printf("| %11s | %10s | %10s | %d | %d | %d | %d | %d | %7.2lf |\n", s[i].surname, s[i].name, s[i].patronymic, s[i].scores[0], s[i].scores[1], s[i].scores[2], s[i].scores[3], s[i].scores[4], avg);
	}

	printf("+-------------+------------+------------+-------------------+---------+\n");
}

// вывод тех студентов, чей средний балл выше 4
void printWithScore(Student *s, int n) {
	printf("\n\n");
	printf("+-------------+------------+------------+-------------------+---------+\n");
	printf("|               Students with average score more than 4               |\n");
	printf("+-------------+------------+------------+-------------------+---------+\n");
	printf("|   Surname   |    Name    | Patronymic | Scores in session | Average |\n");
	printf("+-------------+------------+------------+---+---+---+---+---+---------+\n");

	int count = 0;

	for (int i = 0; i < n; i++) {
		double avg = 0;

		for (int j = 0; j < 5; j++)
			avg += s[i].scores[j];

		avg /= 5;

		if (avg > 4) {
			printf("| %11s | %10s | %10s | %d | %d | %d | %d | %d | %7.2lf |\n", s[i].surname, s[i].name, s[i].patronymic, s[i].scores[0], s[i].scores[1], s[i].scores[2], s[i].scores[3], s[i].scores[4], avg);
			count++;
		}
	}

	if (count == 0)
		printf("\nNo students with average score more 4\n");

	printf("+-------------+------------+------------+---+---+---+---+---+---------+\n");
}

int main() {
	Student students[100];
	int n;

	readFromFile("file.txt", students, &n);

	sortStudents(students, n);
	printStudents(students, n);
	printWithScore(students, n);
}