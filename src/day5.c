#include "day5.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define RANGELEN 182
// #define RANGELEN 4

int is_fresh(long long, long long[RANGELEN], long long[RANGELEN]);
bool insert_range(long long, long long, long long[RANGELEN], long long[RANGELEN], int*, int);

int day_driver(FILE *test, FILE *input) {
  const int p1_ans = 3;
  const long long p2_ans = 14;

  // assert(p1_ans == day5_p1(test));
  // printf("P1: %d\n", day5_p1(input));

  // rewind(test);
  // rewind(input);
  //
  // assert(p2_ans == day5_p2(test));
  printf("P2: %lld\n", day5_p2(input));

  return 0;
}

int day5_p1(FILE *file) {
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

long long day5_p2(FILE *file) {
  long long low[RANGELEN] = {};
  long long high[RANGELEN] = {};

  long long fresh = 0;

  char ch;
  long long left = 0;
  long long right = 0;
  int ranges = 0;
  bool next = false;
  int used = 0;
  while ((ch = (char)fgetc(file)) != EOF) {
    if (ch == '\n') {
      if (ranges < RANGELEN) {
        insert_range(left, right, low, high, &used, -1);
        ranges += 1;
        left = 0;
        right = 0;
        next = false;
        continue;
      }
      break;
    }

    if (ch == '-') {
      next = true;
    } else if (next) {
      right = right * 10 + (long long)(ch - '0');
    } else {
      left = left * 10 + (long long)(ch - '0');
    }
  }

  for (int i = 0; i < used; i++) {
    if (low[i] == 0 || high[i] == 0) { continue; }
    if (insert_range(low[i], high[i], low, high, &used, i)) {
      low[i] = 0;
      high[i] = 0;
      i = -1;
    }
  }

  for (int i = 0; i < used; i++) {
    if (low[i] == 0 || high[i] == 0) {
      continue;
    }

    printf("%lld-%lld: %lld\n", low[i], high[i], high[i] - low[i] + 1);
    fresh += high[i] - low[i] + 1;
  }

  printf("F: %lld\n", fresh);
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

bool insert_range(long long lr, long long hr, long long low[RANGELEN], long long high[RANGELEN], int *used, int idx) {
  int lim = (idx > 0)? *used : RANGELEN;
  for (int i = 0; i < lim; i++) {
    if (i == idx) { continue; }
    if (low[i] == 0 && high[i] == 0 && idx >= 0) {
      continue;
    }

    if (low[i] == 0 && high[i] == 0 && idx < 0) {
      low[i] = lr;
      high[i] = hr;
      *used += 1;
      return false;
    }

    if (low[i] == lr && high[i] == hr) {
      return true;
    }

    if (lr > low[i] && hr < high[i]) {
      return true;
    }

    if (lr <= low[i] && hr >= high[i]) {
      low[i] = lr;
      high[i] = hr;
      return true;
    }

    if (lr >= low[i] && lr <= high[i] && hr > high[i]) {
      high[i] = hr;
      return true;
    }

    if (hr <= high[i] && hr >= low[i] && lr < low[i]) {
      low[i] = lr;
      return true;
    }
  }

  return false;
}
