#include "functions.h"
int main() {
	char* ptr;
	char limits[] = " ";
	struct student* First = (struct student*)malloc(sizeof(struct student));
	First->next = NULL;
	struct student* p = (struct student*)malloc(sizeof(struct student));
	
	int amount_of_students = 0;
	First = input_student(First, p, &amount_of_students);
	First = sort_students(First, amount_of_students);
	prnt_std(First);
	delete_unscssfl_std(&First, &amount_of_students);
	int adding_new_students = 1;
	printf("\n");
	printf("Sucsessful student's: \n");
	if (First != NULL) {
		prnt_std(First);
	}
	else {
		printf("All student aren't successful");
	}
	struct student* pp = malloc(sizeof(struct student));
	pp->next = NULL;
	while (adding_new_students) {
		printf("Do you want to enter a new student? (0 if no, 1 if yes) ");
		if ((char)getc(stdin) == '0') {
			break;
		}
		else {
			while (getchar() != '\n');
			struct student* new_student = (struct student*)malloc(sizeof(struct student));
			char new_str_student[100];
			printf("\nPlease enter data of the student: ");
			
			fgets(new_str_student, 100, stdin);
			
			int amount_grades = fetch_data(new_str_student, new_student);
			seconds(new_student->birth_date, new_student);
			new_student->average_grade = find_average(new_student->grades, amount_grades);
			new_student->next = pp;
			if (First != NULL) {
				InsertSorted(&First, new_student, amount_of_students);
			}
			else {
				First = new_student;
				new_student->next = pp;
				amount_of_students++;
			}
			
		}
		p = First;
		while (p->next != NULL) {
				printf("%s %s %s %f\n", p->name, p->surname, p->birth_date, p->average_grade);
			p = p->next;
		}
		
	}
	printf("Work ended");
	return 0;
}
