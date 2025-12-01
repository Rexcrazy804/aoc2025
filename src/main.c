#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int day1_p1(void);
int rotate(int, int, char);

int main(int argc, char **argv) {
  int answer = day1_p1();

  printf("%d\n", answer);

  return 0;
}

int day1_p1(void) {
  FILE *file;
  char direction;
  char current;
  int weight;
  int dial;
  int passwd;

  file = fopen("./inputs/day1.txt", "r");

  if (!file) {
    printf("failed to open file\n");
    return 0;
  };

  dial = 50;
  passwd = 0;
  direction = '0';
  while ((current = fgetc(file)) != EOF) {
    if (current == 'L' || current == 'R') {
      if (direction != '0') {
        dial = rotate(dial, weight, direction);
        if (dial == 0) {
          passwd += 1;
        }
      };

      direction = current;
      weight = 0;
    } else if (strchr("0123456789", current) != NULL) {
      weight = weight * 10 + atoi(&current);
    }
  }

  fclose(file);

  return passwd;
}

int rotate(int base, int weight, char direction) {
  // printf("[PRE] dial:%d, weight: %d, direction: %C\n", base, weight,
  // direction);
  weight = weight % 100;

  if (direction == 'L') {
    base = base - weight;
  } else {
    base = base + weight;
  }

  base = base + 100;
  base = base % 100;

  // printf("[PST] dial:%d, weight: %d, direction: %C\n", base, weight,
  // direction);
  return base;
}
