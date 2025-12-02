#include <stdio.h>

#define DAY "2"
#include "day2.h"

int main(void) {
  const char *test_file = "./inputs/day" DAY "t.txt";
  const char *input_file = "./inputs/day" DAY ".txt";

  printf(" D: " DAY "\n");

  int (*driver)(FILE *, FILE *) = day_driver;

  FILE *test = fopen(test_file, "r");
  FILE *actual = fopen(input_file, "r");

  if (!test) {
    printf("Failed to open test file\n");
    return -1;
  };

  if (!actual) {
    printf("Failed to open input file\n");
    return -1;
  };

  int ret = driver(test, actual);

  fclose(test);
  fclose(actual);

  return ret;
}
