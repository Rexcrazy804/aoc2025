#include "day6.h"
#include <assert.h>
#include <stdio.h>

#define COLUMNS 4
// #define COLUMNS2 16
// #define COLUMNS 1000
#define COLUMNS2 3684

int day_driver([[maybe_unused]] FILE *test, FILE *input) {
  [[maybe_unused]] const long long p1_ans = 4277556;
  [[maybe_unused]] const long long p2_ans = 3263827;

  // assert(p1_ans == day6_p1(test));
  // printf("P1: %lld\n", day6_p1(input));

  // rewind(test);
  // rewind(input);
  //
  // assert(p2_ans == day6_p2(test));
  printf("P2: %lld\n", day6_p2(input));

  return 0;
}

long long day6_p1(FILE *file) {
  long long answer = 0;

  long long prod[COLUMNS] = {};
  long long sum[COLUMNS] = {};

  char ch;
  int col = 0;
  int num = 0;
  while ((ch = (char)fgetc(file)) != EOF) {
    if (prod[col] == 0) { prod[col] = 1; }

    if (ch == ' ' || ch == '\n') {
      if (num != 0) {
        // printf("%d ", num);
        sum[col] += num;
        prod[col] *= num;
        num = 0;
      }

      // if (ch == '\n') {
      //   printf("\n");
      // }

      col = (ch == '\n')? 0 : col +  1;

      while ((ch = (char) getc(file)) == ' ') {}
      ungetc((int) ch, file);
      continue;
    } else if (ch != '+' && ch != '*') {
      num = num*10 + (int)(ch - '0');
      continue;
    }

    switch (ch) {
      case '+': answer += sum[col]; break;
      case '*': answer += prod[col]; break;
    }
    // printf("SA: %lld C: %d\n", answer, col);
  }

  // printf("A: %lld\n", answer);
  return answer;
}

long long day6_p2(FILE *file) {
  long long answer = 0;
  long long nums[COLUMNS2] = {};

  int col = 0;
  long long buffer = 0;
  char bufferOp = '\0';
  char ch;

  while ((ch = (char)fgetc(file)) != EOF) {
    if (ch == ' ' || ch == '\n') {
      if (nums[col] != 0 && bufferOp != '\0') {
        printf("N: %lld PB: %lld ", nums[col], buffer);
        switch (bufferOp) {
          case '+' : 
            printf("O: %C ", bufferOp);
            buffer += nums[col]; 
            break;
          case '*' : 
            printf("O: %C ", bufferOp);
            buffer = buffer * nums[col]; 
            break;
        }
        printf("B: %lld\n", buffer);
      }
      col = (ch == '\n')? 0 : col +  1;
      if (ch == '\n') {
        printf("\n");
      }
      continue;
    }

    if (ch != '+' && ch != '*') {
      nums[col] = nums[col]*10  + (long long) ch - '0';
      printf("C: %d D: %lld\n", col, nums[col]);
      col += 1;
      continue;
    }

    answer += buffer;
    bufferOp = ch;
    buffer = (ch == '*' && nums[col] == 0)? 1 : nums[col];
    printf("A: %lld, B: %lld\n", answer, buffer);
    col += 1;
  }

  answer = answer + buffer;
  printf("%lld\n", answer);
  return answer;
}
