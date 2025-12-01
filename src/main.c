#include "day1.h"
#include <stdio.h>

#define DAY "1"

int main(void) {
  const char *test_file = "./inputs/day" DAY "t.txt";
  const char *input_file = "./inputs/day" DAY ".txt";
  const int test_answer = 6;
  int (*func)(FILE *) = day1_p1;

  FILE *test = fopen(test_file, "r");
  int answer = func(test);
  printf("test: %d\n", answer);
  fclose(test);

  if (answer != test_answer) {
    printf("test failed :<\n");
    return -1;
  }

  FILE *actual = fopen(input_file, "r");
  answer = func(actual);
  printf("actual: %d\n", answer);
  fclose(actual);

  return 0;
}
