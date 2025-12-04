#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "day4.h"
#define SIZE 135

int paper_rolls(char[SIZE][SIZE], bool);
void checkincrease(char[SIZE][SIZE], int[SIZE][SIZE], int, int, int);

int day_driver([[maybe_unused]]FILE *test, FILE *input) {
  [[maybe_unused]] const int p1_ans = 13;
  [[maybe_unused]] const int p2_ans = 43;

  printf("P1: %d\n", day4(input, false));
  printf("P2: %d\n", day4(input, true));

  // rewind(test);
  // rewind(input);
  //
  // assert(p2_ans == day4_p2(test));
  // printf("P2: %lld\n", day4_p2(input));

  return 0;
}

int day4(FILE *file, bool p2) {
  char map[SIZE][SIZE];

  char ch;
  int row = 0;
  int col = 0;
  while ((ch = (char)fgetc(file)) != EOF) {
    if (col > SIZE) {
      printf("OVERFLOW!"); // yes that overflow
      exit(1);
    }

    if (ch == '\n') {
      row += 1;
      col = 0;
      continue;
    }

    map[row][col] = ch;
    col += 1;
  }

  return paper_rolls(map, p2);
}

int paper_rolls(char map[SIZE][SIZE], bool p2) {
  int result[SIZE][SIZE] = {};
  int count = 0;

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if ((j > 0 || j < SIZE - 1) && (i == 0 || i == SIZE - 1)) {
        checkincrease(map, result, i, j, 3);
      }
      if ((i > 0 || i < SIZE - 1) && (j == 0 || j == SIZE - 1)) {
        checkincrease(map, result, i, j, 3);
      }
      if ((i == 0 && j == 0) || (i == SIZE - 1 && j == SIZE - 1) ||
          (i == 0 && j == SIZE - 1) || (j == 0 && i == SIZE - 1)) {
        checkincrease(map, result, i, j, 5);
      }
      if (map[i][j] == '.') {
        // sometimes you realize you are    a lazy slob
        //           I           I   too am
        #include "day4_omnicheck"
      }
    }
  }

  do {
    int subcount = 0;

    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        if (result[i][j] > 4) {
          subcount += 1;
          if (p2) {
            result[i][j] = 0;
            map[i][j] = '.';
            #include "day4_omnicheck"
          }
        }
      }
    }

    if (subcount == 0) {
      break;
    }

    count += subcount;
  } while (p2);

  return count;
}

// accepts a row and column, and increases the respective field
// if possible after checking if it contains '@'
void checkincrease(char map[SIZE][SIZE], int heat[SIZE][SIZE], int row, int col,
                   int weight) {
  if (row < 0 || col < 0 || row >= SIZE || col >= SIZE) {
    return;
  }

  if (map[row][col] == '@') {
    heat[row][col] += weight;
  }
}
