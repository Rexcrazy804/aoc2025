#include "day2.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

static long int get_invalid_sum(long int, long int, int, int);
static long int get_invalid_sum2(long int, long int, int, int);
static int get_digit_count(int, int, long int);
static long int power(int, int);

long int day2_p1(FILE *file) {
  long int sum_invalids = 0;
  long int range1 = 0;
  long int range2 = 0;
  int range1len = 0;
  int range2len = 0;
  bool next = false;

  char current;
  while ((current = (char)fgetc(file)) != EOF) {
    if (current == ',' || current == '\n') {
      sum_invalids += get_invalid_sum(range1, range2, range1len, range2len);
      range1 = 0;
      range2 = 0;
      range1len = 0;
      range2len = 0;
      next = false;
    } else if (current == '-') {
      next = true;
    } else if (strchr("0123456789", current) != NULL) {
      if (!next) {
        range1 = range1 * 10 + atoi(&current);
        range1len += 1;
        continue;
      }
      range2 = range2 * 10 + atoi(&current);
      range2len += 1;
    }
  }

  return sum_invalids;
}

long int day2_p2(FILE *file) {
  long int sum_invalids = 0;
  long int range1 = 0;
  long int range2 = 0;
  int range1len = 0;
  int range2len = 0;
  bool next = false;

  char current;
  while ((current = (char)fgetc(file)) != EOF) {
    if (current == ',' || current == '\n') {
      sum_invalids += get_invalid_sum2(range1, range2, range1len, range2len);
      range1 = 0;
      range2 = 0;
      range1len = 0;
      range2len = 0;
      next = false;
    } else if (current == '-') {
      next = true;
    } else if (strchr("0123456789", current) != NULL) {
      if (!next) {
        range1 = range1 * 10 + atoi(&current);
        range1len += 1;
        continue;
      }
      range2 = range2 * 10 + atoi(&current);
      range2len += 1;
    }
  }

  return sum_invalids;
}

static long int get_invalid_sum(long int r1, long int r2, int r1l, int r2l) {
  if (r1 < 0 || r2 < 0) {
    printf("R: %ld %ld\n", r1, r2);
    exit(1);
  }

  // if the two ranges share the same digit count and its not even,
  // return 0, there can't be invalid ranger between them
  if (r1l == r2l && r1l % 2) {
    return 0;
  }

  long int sum = 0;

  long int i;
  for (i = r1; i <= r2; i += 1) {
    int diglen = get_digit_count(r1l, r2l, i);

    // Eliminate what is false ~ Brume | Reverse 1999
    if (diglen % 2 != 0) {
      i = power(10, diglen) - 1;
      continue;
    }

    long int ten = power(10, diglen / 2);
    long int lefthalf = i / ten;
    long int righthalf = i % ten;

    if (lefthalf == righthalf) {
      // printf("%d: %d %d\n", i, lefthalf, righthalf);
      sum += i;
    } else {
      // printf("%d\n", i);
    };
  }

  return sum;
}

static long int get_invalid_sum2(long int r1, long int r2, int r1l, int r2l) {
  if (r1 < 0 || r2 < 0) {
    // overflow check
    printf("R: %ld %ld\n", r1, r2);
    exit(1);
  }

  long int sum = 0;

  long int i;
  for (i = r1; i <= r2; i += 1) {
    int diglen = get_digit_count(r1l, r2l, i);

    long int j;
    int subdiglen = 0;
    for (j = 10; j <= power(10, diglen); j *= 10) {
      subdiglen += 1;
      long int subdigits = i % j;

      if (subdiglen > diglen / 2) {
        break;
      }

      if (subdigits == 0) {
        continue;
      }

      // filter out sub digits that that contain less than j / 10 digits
      // i.e. if we are diving by 100
      // we NEEED 2 digit numbers
      if (subdigits < j / 10) {
        continue;
      }

      if (diglen % subdiglen != 0) {
        continue;
      }

      long int sequence = i / subdigits;
      int seqlen = get_digit_count(0, diglen, sequence);

      if ((seqlen - 1) % subdiglen) {
        continue;
      }

      long int seq_c = sequence;
      bool break_f = false;
      bool has_zero = false;
      long int prev = 0;

      while (seq_c > 0) {
        long int digit = seq_c % 10;
        if (digit == 0) {
          has_zero = true;
        }
        if (digit > 1) {
          break_f = true;
          break;
        }

        if (j == 10 && digit != 1) {
          break_f = true;
          break;
        }

        // prune sequences with consecutive 1's if j is not 10
        if (prev == 1 && digit == 1 && j != 10) {
          break_f = true;
          break;
        }

        seq_c = seq_c / 10;
        prev = digit;
      }

      if (j != 10 && seq_c) {
        continue;
      }

      if (break_f || sequence == 1 || sequence % 10 != 1) {
        continue;
      }

      if (j != 10 && !has_zero) {
        continue;
      }

      printf("num: %ld, len: %ld, seq %ld\n", i, j, sequence);
      sum += i;
      break;

      // printf("%ld\n", i);
      // break;
    }
  }

  return sum;
}

// a funny function that returns the length of a number
// ASSUMES d1 < d2
static int get_digit_count(int d1, int d2, long int num) {
  if (d1 == d2) {
    return d1;
  }

  int i;
  for (i = d1; i <= d2; i += 1) {
    if (num < power(10, i)) {
      return i;
    }
  }

  printf("UNREACHABLE\n");
  exit(-1);
}

static long int power(int base, int exp) {
  if (exp == 0)
    return 1;
  else if (exp % 2)
    return base * power(base, exp - 1);
  else {
    long int temp = power(base, exp / 2);
    return temp * temp;
  }
}
