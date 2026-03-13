#include "student.h"
#include <stdio.h>
#include <stdlib.h>

void in_basic(Student* s)
{
    printf("ID: ");
    scanf("%d", &s->id);

    printf("Name: ");
    scanf("%49s", s->name);

    printf("Year: ");
    scanf("%d", &s->year);

    printf("Semesters: ");
    scanf("%d", &s->sem_count);
}

void in_res(Student* s)
{
    s->res = malloc(sizeof(float) * s->sem_count);
    for (int i = 0; i < s->sem_count; i++) {
        printf("Result sem %d: ", i + 1);
        scanf("%f", &s->res[i]);
    }
}

void in_books(Student* s)
{
    s->books = malloc(sizeof(int) * s->sem_count);
    for (int i = 0; i < s->sem_count; i++) {
        printf("Books sem %d: ", i + 1);
        scanf("%d", &s->books[i]);
    }
}

void print(Student* s)
{
    printf("\nID: %d\n", s->id);
    printf("Name: %s\n", s->name);
    printf("Year: %d\n", s->year);

    for (int i = 0; i < s->sem_count; i++) {
        printf("Sem %d Result: %.2f\n", i + 1, s->res[i]);
    }

    if (s->books) {
        for (int i = 0; i < s->sem_count; i++) {
            printf("Sem %d Books: %d\n", i + 1, s->books[i]);
        }
    }

    if (s->gpa)
        printf("GPA: %.2f\n", s->gpa);
}