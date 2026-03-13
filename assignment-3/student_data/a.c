#include "student.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    printf("Students: ");
    scanf("%d", &n);

    Student* s = malloc(sizeof(Student) * n);

    for (int i = 0; i < n; i++) {
        in_basic(&s[i]);
        in_res(&s[i]);
    }

    for (int i = 0; i < n; i++)
        print(&s[i]);

    return 0;
}