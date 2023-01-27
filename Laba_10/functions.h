#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
struct int_date {
	int days;
	int months;
	int years;
};
struct student
{
	char* surname;
	char* name;
	char* birth_date;
	int* grades;
	float average_grade;
	struct int_date date;
	struct student* next;
};
float find_average(int* grade, int amount_grades);
int amount_of_grades(char* ptr);
int std1_std2(struct student student1, struct student student2);
void swap_structures(struct student* Student1, struct student* Student2, struct student* prev);
struct student* sort_students(struct student* First, int amount_of_students);
int fetch_data(char* data, struct student* new_student);
void seconds(char* birth_data, struct student* Student);
struct student* input_student(struct student* First, struct student* p, int* amount_of_students);
void prntf_scssfl_std(const struct student* First);
void InsertSorted(struct student** First, struct student* new_student, int amount_of_students);
void prnt_std(const struct student* First);
void delete_student(struct student* student_to_delete, struct student* prev);
void delete_unscssfl_std(struct student** ppFirst, int* amount_of_students);
#endif