#include "day7.h"
#include <assert.h>
#include <stdio.h>

// #define WIDTH 15
#define WIDTH 141

int day_driver([[maybe_unused]] FILE *test, FILE *input) {
  [[maybe_unused]] const long int p1_ans = 21;
  [[maybe_unused]] const long long p2_ans = 14;

  // assert(p1_ans == day7_p1(test));
  printf("P1: %ld\n", day7_p1(input));

  // rewind(test);
  // rewind(input);
  //
  // assert(p2_ans == day7_p2(test));
  // printf("P2: %lld\n", day7_p2(input));

  return 0;
}

long int day7_p1(FILE *file) {
  long int answer = 0;
  int grid[WIDTH] = {};

  char ch;
  int col = 0;
  while ((ch = (char)fgetc(file)) != EOF) {
    switch (ch) {
      case 'S':
        grid[col] = 1;
        break;
      case '^':
        if (grid[col])  {
          answer += 1;
          // WARN
          // assumes no splitters in either edge
          // (works for my input, and test)
          grid[col] = 0;
          grid[col-1] = 1;
          grid[col+1] = 1;
        }
        break;
      case '.': break;
      case '\n': 
        col = -1;
        break;
    }
    col += 1;
  }

  return answer;
}
