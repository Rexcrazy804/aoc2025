#include "day1.h"
#include <stdlib.h>
#include <string.h>

int day1_p1(FILE *file) {
  char direction, current;
  int weight, dial, passwd, rotations;

  if (!file) {
    printf("failed to open file\n");
    return 0;
  };

  dial = 50;
  passwd = 0;
  direction = '0';
  rotations = 0;
  while ((current = fgetc(file)) != EOF) {
    if (current == 'L' || current == 'R') {
      direction = current;
      weight = 0;
    } else if (strchr("0123456789", current) != NULL) {
      weight = weight * 10 + atoi(&current);
    } else if (current == '\n') {
      rotate(&dial, &rotations, weight, direction);
      passwd += (dial == 0) ? 1 : 0;
    }
  }

  // part one is just the passwd, part 2 we needa add the rotations as well
  return passwd + rotations;
}

static void rotate(int *base, int *rotations, int weight, char direction) {
  *rotations += weight / 100;
  weight = weight % 100;

  if (direction == 'L') {
    if (*base > 0 && *base - weight < 0) {
      *rotations += 1;
    }
    *base = *base - weight;
  } else {
    if (*base < 100 && *base + weight > 100) {
      *rotations += 1;
    }
    *base = *base + weight;
  }

  *base = *base + 100;
  *base = *base % 100;
}
