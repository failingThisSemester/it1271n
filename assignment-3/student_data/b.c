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
        in_books(&s[i]);
    }

    s[0].sem_count++;

    s[0].res = realloc(s[0].res, sizeof(float) * s[0].sem_count);
    s[0].books = realloc(s[0].books, sizeof(int) * s[0].sem_count);

    printf("Extra result: ");
    scanf("%f", &s[0].res[s[0].sem_count - 1]);

    printf("Extra books: ");
    scanf("%d", &s[0].books[s[0].sem_count - 1]);

    for (int i = 0; i < n; i++)
        print(&s[i]);

    return 0;
}