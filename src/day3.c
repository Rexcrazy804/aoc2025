#include <assert.h>
#include <stdio.h>

#include "day3.h"

long long process(int[], int);

int day_driver(FILE *test, FILE *input) {
  const int p1_ans = 357;
  const long long p2_ans = 3121910778619;

  assert(p1_ans == day3_p1(test));
  printf("P1: %d\n", day3_p1(input));

  rewind(test);
  rewind(input);

  assert(p2_ans == day3_p2(test));
  printf("P2: %lld\n", day3_p2(input));

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
    cur_int = (int)cur - '0';

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

// don't ask me how to pass an array as a reference
long long day3_p2(FILE *file) {
  long long sum = 0;
  int array[100];

  char cur;
  int i = 0;
  while ((cur = (char)fgetc(file)) != EOF) {
    if (cur == '\n') {
      sum += process(array, i);
      i = 0;
    } else {
      array[i++] = (int)cur - '0';
    }
  }

  return sum;
}

long long process(int array[], int arrlen) {
  const int selectN = 12;
  int selections = 0;
  int start = 0;
  int i;
  long long answer = 0;

  while (selections != selectN) {
    int largest = array[start];
    int largest_index = start;
    int end = arrlen - (selectN - selections) + 1;

    for (i = start + 1; i < end; i++) {
      if (largest < array[i]) {
        largest = array[i];
        largest_index = i;
      }
    }
    answer = answer * 10 + (long long)largest;
    start = largest_index + 1;
    selections += 1;
  }

  return answer;
}
