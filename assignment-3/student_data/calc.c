#include "student.h"
#include <stdio.h>

void calc_gpa(Student* s)
{
    float sum = 0;
    for (int i = 0; i < s->sem_count; i++)
        sum += s->res[i];
    s->gpa = sum / s->sem_count;
}

void top(Student* s, int n)
{
    int t = 0;

    for (int i = 1; i < n; i++) {
        if (s[i].gpa > s[t].gpa)
            t = i;
    }

    printf("\nTopper: %s GPA %.2f\n", s[t].name, s[t].gpa);
}
c