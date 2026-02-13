/*
* name: sagnik bhattacharjee
* roll: 2025ITB006
* date: jan 30, 2026
*/

#include <stdio.h>
#include <stdlib.h>

void pattern1(int n) {
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j <= i; ++j) {
        printf("* ");
    }
    printf("\n");
  }
}

void pattern2(int n) {
  for(int i = n; i > 0; --i){
    for(int j = 0; j < i; ++j) {
      printf("* ");
    }
    printf("\n");
  }
}

void pattern3(int n) {
  for(int i = n; i > 0; --i) {
    for(int j = 0; j < i - 1; ++j) {
      printf("  ");
    }
    for(int k = 0; k <= n - i; k++) {
      printf("* ");
    }
    printf("\n");
  }
}

void pattern4(int n) {
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j <= i - 1; ++j) {
      printf("  ");
    }
    for(int k = 0; k < n - i; k++) {
      printf("* ");
    }
    printf("\n");
  }
}

void pattern5(int n) {
  // combine 3 and 1 
  for(int i = n; i > 0; --i) {
    for(int j = 0; j < i - 1; ++j) {
      printf("  ");
    }
    for(int k = 0; k <= ((n - i)*2); k++) {
      printf("* ");
    }
    printf("\n");
  }
}
void pattern6(int n) {
  // combine 4 and 2
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j <= i - 1; ++j) {
      printf("  ");
    }
    for(int k = 0; k <= ((n - i)*2) - 2; k++) {
      printf("* ");
    }
    printf("\n");
  }
}

void pattern7(int n) {
  for(int i = 0; i < n; ++i) {
    for(int j = n - i; j > 0; --j) {
        printf(" ");
    }
    for(int j = 0; j <= i; ++j) {
        printf("* ");
    }
    printf("\n");
  }
}

void pattern8(int n) {
  for(int i = 0; i < n; i++) {
    for(int j = n - i; j > 0; --j) {
        printf(" ");
    }
    for(int j = 0; j < n; j++) {
      printf("* ");
    }
    printf("\n");
  }
}

void pattern9(int n) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j <= i; ++j) {
        printf(" ");
    }
    for(int j = 0; j < n; j++) {
      printf("* ");
    }
    printf("\n");
  }
}

void pattern10(int n) {
  // combine 1 and 2
  pattern1(n);
  pattern2(n);
}

void pattern11(int n) {
  pattern4(n);
  pattern3(n);
}

void pattern12(int n) {
  pattern2(n);
  pattern1(n);
}

void pattern13(int n) {
  n--;
  for(int i = 0; i <= n; ++i) {
    for(int j = 0; j <= i; ++j) {
        printf("* ");
    }
    for(int j = 0; j <= ((n - i)*2) - 1; ++j) {
      printf("  ");
    }
    for(int j = 0; j <= i; ++j) {
        printf("* ");
    }
    printf("\n");
  }
  for(int i = n + 1; i >= 0; --i){
    for(int j = 0; j <= i - 1; ++j) {
      printf("* ");
    }
    for(int k = 0; k < ((n + 1 - i)*2); k++) {
      printf("  ");
    }
    for(int j = 0; j <= i - 1; ++j) {
      printf("* ");
    }
    printf("\n");
  }
}

void pattern14(int n) {
  for(int i = n; i > 0; --i) {
    for(int j = 0; j < i - 1; ++j) {
      printf("  ");
    }
    for(int k = 0; k <= n - i; k++) {
      printf("* ");
    }
    for(int j = 0; j <= n - i - 1; ++j) {
      printf("* ");
    }
    printf("\n");
  }
  // for(int i = 0; i < (n * 2) - 1; i++)
    // printf("* ");
  // printf("\n");
  n--;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j <= i; ++j) {
        printf("  ");
    }
    for(int j = 0; j <= ((n - i)*2) - 2; ++j) {
      printf("* ");
    }
    for(int j = 0; j <= i; ++j) {
        printf("  ");
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  // fundamental patterns
  printf("PATTERN 1\n");
  pattern1(n);
  printf("PATTERN 2\n");
  pattern2(n);
  printf("PATTERN 3\n");
  pattern3(n);
  printf("PATTERN 4\n");
  pattern4(n);
  
  // semi compound patterns
  printf("PATTERN 5\n");
  pattern5(n);
  printf("PATTERN 6\n");
  pattern6(n);
  
  printf("PATTERN 7\n");
  pattern7(n);
  printf("PATTERN 8\n");
  pattern8(n);
  printf("PATTERN 9\n");
  pattern9(n);
  
  // compound patterns
  printf("PATTERN 10\n");
  pattern10(n);
  printf("PATTERN 11\n");
  pattern11(n);
  printf("PATTERN 12\n");
  pattern12(n);
  printf("PATTERN 13\n");
  pattern13(n);
  printf("PATTERN 14\n");
  pattern14(n);
}
