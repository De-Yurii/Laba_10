#include "functions.h"

float find_average(int* grade, int amount_grades) {
	float average = 0;
	for (int i = 0; i < amount_grades; i++) {
		average += grade[i];
	}
	average /= amount_grades;
	return average;
}

void delete_student(struct student* student_to_delete, struct student* prev) {
	if (prev != NULL) {
		prev->next = student_to_delete->next;
	}
	free(student_to_delete->surname);
	free(student_to_delete->name);
	free(student_to_delete->birth_date);
	free(student_to_delete->grades);
	free(student_to_delete);
}

void delete_unscssfl_std(struct student** ppFirst, int* amount_of_students) {
	struct student* current_student = *ppFirst;
	struct student* prev = NULL;
	while (current_student->next != NULL) {
		if (current_student->average_grade < 4.5) {
			if (current_student == *ppFirst) {
				*ppFirst = current_student->next;
				prev = NULL;
				delete_student(current_student, prev);
				current_student = *ppFirst;
				*amount_of_students-=1;
			}
			else {
				delete_student(current_student, prev);
				current_student = prev;
				*amount_of_students-=1;
			}

		}
		else {
			prev = current_student;
			current_student = current_student->next;
		}

	}
	if (prev == NULL) {
		*ppFirst = NULL;
	}
}

int amount_of_grades(char* ptr) {
	int amount = 0;
	for (int i = 0; *ptr != '}'; i++) {
		if (isdigit(*ptr)) {
			amount++;
		}
		ptr++;
	}
	return amount;
}
int std1_std2(struct student student1, struct student student2) {
	if (student1.date.years < student2.date.years) {
		return 0;
	}
	else if (student1.date.years > student2.date.years) {
		return 1;
	}
	if (student1.date.months < student2.date.months) {
		return 0;
	}
	else if (student1.date.months > student2.date.months) {
		return 1;
	}
	if (student1.date.days < student2.date.days) {
		return 0;
	}
	else if (student1.date.days > student2.date.days) {
		return 1;
	}
	return 0;
}
void swap_structures(struct student* Student1, struct student* Student2, struct student* prev) {
	if (prev != NULL) {
		(*prev).next = Student2;
	}
	(*Student1).next = Student2->next;
	Student2->next = Student1;

}

struct student* sort_students(struct student* First, int amount_of_students) {
	struct student* p = First;
	struct student* pp;
	struct student* prev = NULL;
	for (int i = 0; i < amount_of_students - 1; i++) {
		for (int j = 0; j < amount_of_students - i - 1; j++) {
			if (p != NULL) {
				pp = p->next;
				if (std1_std2(*p, *pp)) {
					swap_structures(p, pp, prev);
					if (prev != NULL) {
						prev = pp;
					}
					if (p == First) {
						First = pp;
						prev = First;

					}
				}
				else {

					prev = p;
					p = p->next;
				}
				pp = p;
			}
		}
		p = First;
		prev = NULL;
	}
	return p;

}

int fetch_data(char* data, struct student* new_student) {
	char limits[] = " ";
	char* ptr;
	ptr = strtok(data, limits);
	char* surname = (char*)malloc((strlen(ptr) + 1) * sizeof(char));
	strcpy(surname, ptr);
	new_student->surname = surname;

	ptr = strtok(NULL, limits);
	char* name = (char*)malloc((strlen(ptr) + 1) * sizeof(char));
	strcpy(name, ptr);
	new_student->name = name;

	ptr = strtok(NULL, limits);
	char* date = (char*)malloc((strlen(ptr) + 1) * sizeof(char));
	strcpy(date, ptr);
	new_student->birth_date = date;
	ptr = strtok(NULL, limits);
	char* digit_pointer = ptr;
	int amount_grades = amount_of_grades(ptr);

	int* grades = (int*)malloc(amount_grades * sizeof(int));
	new_student->grades = grades;
	int current_grade = 0;
	for (int i = 0; *ptr != '}'; i++) {
		if (isdigit(*ptr)) {
			grades[current_grade] = atoi(ptr);
			current_grade++;
		}
		ptr++;
	}
	return amount_grades;
}

void seconds(char* birth_data, struct student* Student) {
	char* temp = (char*)malloc((strlen(birth_data) + 1) * sizeof(char));
	for (int i = 0; i < strlen(birth_data); i++) {
		temp[i] = birth_data[i];
	}
	char* ptr = strtok(temp, ".");
	int amount;
	amount = atoi(ptr);
	(*Student).date.days = amount;
	ptr = strtok(NULL, ".");
	amount = atoi(ptr);
	(*Student).date.months = amount;
	ptr = strtok(NULL, ".");
	amount = atoi(ptr);
	(*Student).date.years = amount;
	free(temp);
	temp = NULL;
}
struct student* input_student(struct student* First, struct student* p, int* amount_of_students) {
	FILE* file = fopen("Students.txt", "r");
	char* ptr;
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* data = (char*)malloc(size * sizeof(char));
	char limits[] = " ";
	while (!feof(file)) {

		fgets(data, size, file);
		int amount_grades = fetch_data(data, p);
		if (First->next == NULL) {
			First = p;
		}
		struct student* pp = (struct student*)malloc(sizeof(struct student));
		seconds(p->birth_date, p);
		p->average_grade = find_average(p->grades, amount_grades);
		p->next = pp;
		p = pp;
		(*amount_of_students)++;
	}
	fclose(file);
	free(data);
	data = NULL;
	p->next = NULL;
	return First;
}
void prntf_scssfl_std(const struct student* First) {
	struct student* p = First;
	while ((p->next) != NULL) {
		if (p->average_grade < 4.5)
			printf("%s %s %s %f\n", p->name, p->surname, p->birth_date, p->average_grade);
		p = p->next;
	}
}

void InsertSorted(struct student** First, struct student* new_student, int amount_of_students) {
	struct student* Current_Student;
	struct student* prev = NULL;
	Current_Student = *First;
	while (Current_Student->next != NULL) {
		if (std1_std2(*Current_Student, *new_student)) {
			if (Current_Student == *First) {
				new_student->next = Current_Student;
				*First = new_student;
				break;
			}
			else {
				prev->next = new_student;
				new_student->next = Current_Student;
				break;
			}
		}
		else if (Current_Student == *First && (Current_Student->next)->next == NULL) {
			Current_Student->next = new_student;
			break;
		}
		
		
		prev = Current_Student;
		Current_Student = Current_Student->next;
	}
	amount_of_students++;
}

void prnt_std(const struct student* First) {
	struct student* p = First;
	while ((p->next) != NULL) {
		printf("%s %s %s %f\n", p->name, p->surname, p->birth_date, p->average_grade);
		p = p->next;
	}
}
