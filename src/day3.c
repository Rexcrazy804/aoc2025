#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day3.h"

int day_driver(FILE *test, FILE *input) {
  const int p1_ans = 357;
  const long int p2_ans = 4174379265;

  assert(p1_ans == day3_p1(test));
  printf("P1: %d\n", day3_p1(input));

  rewind(test);
  rewind(input);

  // assert(p2_ans == day3_p2(test));
  // printf("P2: %ld\n", day3_p2(input));

  return 0;
}

int day3_p1(FILE *file) {
  int sum = 0, left = 0, right = 0;

  char cur;
  int cur_int;
  int prev_left = 0;
  while ((cur = (char)fgetc(file)) != EOF) {
    if (cur == '\n') {
      if (!right) {
        right = left;
        left = prev_left;
      }
      sum += left * 10 + right;
      left = 0;
      right = 0;
      continue;
    }

    // today I learned I don't need atoi() for this :D
    // fricking dumbass amiright?
    cur_int = (int) cur - '0';

    if (left < cur_int) {
      // silly trick to not look ahead
      prev_left = left;
      left = cur_int;
      right = 0;
    } else if (right < cur_int) {
      right = cur_int;
    }
  }

  return sum;
}
