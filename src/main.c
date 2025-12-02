#include "day2.h"
#include <stdio.h>

#define DAY "2"

int main(void) {
  const char *test_file = "./inputs/day" DAY "t.txt";
  const char *input_file = "./inputs/day" DAY ".txt";
  const long int test_answer = 1227775554;
  long int (*func)(FILE *) = day2_p1;

  FILE *test = fopen(test_file, "r");
  if (!test) {
    printf("Failed to open test file\n");
    return -1;
  };
  long answer = func(test);
  printf("test: %ld\n", answer);
  fclose(test);

  if (answer != test_answer) {
    printf("test failed :<\n");
    return -1;
  }

  FILE *actual = fopen(input_file, "r");
  if (!actual) {
    printf("Failed to open input file\n");
    return -1;
  };
  answer = func(actual);
  printf("actual: %ld\n", answer);
  fclose(actual);

  return 0;
}
