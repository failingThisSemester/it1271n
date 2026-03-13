#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    int id;
    char name[50];
    int year;
    int sem_count;
    float* res;
    int* books;
    float gpa;
} Student;

void in_basic(Student* s);
void in_res(Student* s);
void in_books(Student* s);
void print(Student* s);
void calc_gpa(Student* s);
void top(Student* s, int n);

#endif