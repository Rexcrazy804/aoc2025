#include "day5.h"
#include <assert.h>
#include <stdio.h>

#define RANGELEN 182

int is_fresh(long long, long long[RANGELEN], long long[RANGELEN]);

int day_driver(FILE *test, FILE *input) {
  const long long p1_ans = 3;
  [[maybe_unused]] const long long p2_ans = 3121910778619;

  // assert(p1_ans == day5_p1(test));
  printf("P1: %lld\n", day5_p1(input));

  // rewind(test);
  // rewind(input);
  //
  // assert(p2_ans == day5_p2(test));
  // printf("P2: %lld\n", day5_p2(input));

  return 0;
}

long long day5_p1(FILE *file) {
  long long low[RANGELEN] = {};
  long long high[RANGELEN] = {};

  int fresh = 0;

  char ch;
  long long left = 0;
  long long right = 0;
  int ranges = 0;
  long long id = 0;
  bool next = false;
  while ((ch = (char)fgetc(file)) != EOF) {
    if (ch == '\n') {
      if (ranges < RANGELEN) {
        printf("L: %lld R: %lld\n", left, right);
        low[ranges] = left;
        high[ranges] = right;
        ranges += 1;
        left = 0;
        right = 0;
        next = false;
      } else if (id != 0) {
        fresh += is_fresh(id, low, high);
        id = 0;
      }
      continue;
    }

    if (ranges == RANGELEN) {
      id = id * 10 + (long long)(ch - '0');
      continue;
    }

    if (ch == '-') {
      next = true;
    } else if (next) {
      right = right * 10 + (long long)(ch - '0');
    } else {
      left = left * 10 + (long long)(ch - '0');
    }
  }

  printf("F: %d\n", fresh);
  return fresh;
}

int is_fresh(long long id, long long low[RANGELEN], long long high[RANGELEN]) {
  for (int i = 0; i < RANGELEN; i++) {
    if (low[i] <= id && id <= high[i]) {
      return 1;
    }
  }
  return 0;
}
