#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "day4.h"
#define SIZE 135

int paper_rolls(char[SIZE][SIZE]);
void checkincrease(char[SIZE][SIZE], int[SIZE][SIZE], int, int, int);

int day_driver(FILE *test, FILE *input) {
  const int p1_ans = 13;
  [[maybe_unused]] const long long p2_ans = 3121910778619;
 
  // int ans = day4_p1(test);
  // printf("A: %d\n", ans);
  // assert(p1_ans == ans);

  printf("P1: %d\n", day4_p1(input));

  // rewind(test);
  // rewind(input);
  //
  // assert(p2_ans == day4_p2(test));
  // printf("P2: %lld\n", day4_p2(input));

  return 0;
}

int day4_p1(FILE *file) {
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

  return paper_rolls(map);
  // return 0;
}

int paper_rolls(char map[SIZE][SIZE]) {
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
        checkincrease(map, result, i-1, j-1, 1);
        checkincrease(map, result, i+1, j+1, 1);

        checkincrease(map, result, i-1, j, 1);
        checkincrease(map, result, i+1, j, 1);
        checkincrease(map, result, i, j-1, 1);
        checkincrease(map, result, i, j+1, 1);

        checkincrease(map, result, i-1, j+1, 1);
        checkincrease(map, result, i+1, j-1, 1);
      }
    }
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (result[i][j] > 4) {
        count += 1;
      }
    }
  }

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
