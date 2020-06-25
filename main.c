/* * * * * * *
 * Assignment 1: Convex Hulls main program entry point
 *
 * created for COMP20007 Design of Algorithms 2019
 * by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 */

//                         DO NOT CHANGE THIS FILE
//
// Do not change any of the constants or function prototypes in this file.
//
// An unomodified version of this file will be used when marking your
// assignment so changing this file may lead to compilation errors, and as a
// result a marks penalty.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "point.h"
#include "deque.h"
#include "convex-hull.h"

// ----------------- Constant Definitions -----------------

// Command line options
#define OPT_ORIENTATION 1
#define OPT_DEQUE 2
#define OPT_INSIDE_HULL 3
#define OPT_HELP 4

// The number of points to expect when using the --orientation option
#define NUM_POINTS_ORIENTATION 3

// The possible commands when using the --deque option
#define DEQUE_CMD_PUSH "push"
#define DEQUE_CMD_POP "pop"
#define DEQUE_CMD_INSERT "insert"
#define DEQUE_CMD_REMOVE "remove"
#define DEQUE_CMD_SIZE "size"

// Max length of a command when using the --deque option
#define MAX_CMD_LEN 16

// ----------------- Function Prototypes -----------------

// Reads the command line options and returns OPT_ORIENTATION, OPT_DEQUE,
// OPT_INSIDE_HULL or OPT_HELP.
//
// If the command line arguments are invalid then this will print out an error,
// usage information and then exit.
int get_option(int argc, char **argv);

// Read in the next command from stdin, for the --deque option.
// This will read in up to size characters until whitespace or EOF
// is encountered.
// Returns false if EOF is reached, true otherwise.
// The command is stored in cmd, and terminated by a null byte ('\0').
// The caller should check whether cmd is the empty string (see is_empty()).
bool read_command(char *cmd, int size);

// Returns whether or not the provided string is the empty string.
bool is_empty(char *str);

// Reads in and returns a Point by trying to read two doubles from stdin.
// If an error occurs the program will exit.
// The cmd argument is the name of the test_deque() command read.
// cmd can be NULL and an appropriate error message will be printed.
Point read_point(char *cmd_name);

// Prints the usage information for the command line tool
void print_usage(char *prog_name);

// Reads in three points given on their own lines and prints out whether
// the third point is to the left, right or collinear with then line segment
// formed by the former two.
void test_orientation();

// Tests the Deque implementation by reading in from stdin some number
// of commands, one per line.
//
// The following commands are available:
//   push x y
//   insert x y
//   pop
//   remove
//   size
//
// Push and insert will add a point to the deque, while pop and remove will
// take a point and print it out in the format "x y".
// Size prints the number of points in the deque.
void test_deque();

// Reads in a list of points from stdin in the format:
// n (the number of points to be read in)
// x1 y1
// x2 y2
// ...
// xn yn
//
// This polygon is given to inside_hull(), and the points which make up the
// convex hull are returned.
//
//  These points are then printed one per line.
void test_inside_hull();

// ----------------- Main Function -----------------

int main(int argc, char **argv) {
  int opt = get_option(argc, argv);

  if (opt == OPT_HELP) {
    print_usage(argv[0]);
  } else if (opt == OPT_ORIENTATION) {
    test_orientation();
  } else if (opt == OPT_DEQUE) {
    test_deque();
  } else if (opt == OPT_INSIDE_HULL) {
    test_inside_hull();
  }

  return 0;
}

// ----------------- Function Implementations -----------------

// Reads in three points given on their own lines and prints out whether
// the third point is to the left, right or collinear with then line segment
// formed by the former two.
void test_orientation() {
  int i;
  int values_read;
  char direction;
  Point points[NUM_POINTS_ORIENTATION];

  // Read in the points from stdin
  for (i = 0; i < NUM_POINTS_ORIENTATION; i++) {
    values_read = scanf("%lf %lf", &(points[i].x), &(points[i].y));

    if (values_read != 2) {
      fprintf(stderr, "Error: invalid input format\n");
      exit(EXIT_FAILURE);
    }
  }

  // Print out the points
  for (i = 0; i < NUM_POINTS_ORIENTATION; i++) {
    printf("p%d: ", i);
    print_point(points[i]);
  }

  direction = orientation(points[0], points[1], points[2]);

  // Print an appropriate message, or exit if something unexpected is returned
  if (direction == COLLINEAR) {
    printf("p0, p1 and p2 are collinear\n");
  } else if (direction == LEFT) {
    printf("p2 is to the left of the line p0p1\n");
  } else if (direction == RIGHT) {
    printf("p2 is to the right of the line p0p1\n");
  } else {
    fprintf(stderr,
      "Error: unexpected return value from orientation(): '%c'\n",
      direction);
    exit(EXIT_FAILURE);
  }
}

// Tests the Deque implementation by reading in from stdin some number
// of commands, one per line.
//
// The following commands are available:
//   push x y
//   insert x y
//   pop
//   remove
//   size
//
// Push and insert will add a point to the deque, while pop and remove will
// take a point and print it out in the format "x y".
// Size prints the number of points in the deque.
void test_deque() {
  Deque *deque;
  Point point;
  int size;
  char cmd[MAX_CMD_LEN];

  // Initialise the deque
  deque = new_deque();
  if (deque == NULL) {
    fprintf(stderr, "Error: new_deque() returned NULL\n");
    exit(EXIT_FAILURE);
  }

  while (read_command(cmd, MAX_CMD_LEN)) {
    // This will arise if multiple whitespace characters are input in a row
    if (is_empty(cmd)) {
      continue;
    }

    // Perform the appropriate actions for each command
    if (strcmp(cmd, DEQUE_CMD_PUSH) == 0) {
      point = read_point(cmd);
      deque_push(deque, point);
    } else if (strcmp(cmd, DEQUE_CMD_POP) == 0) {
      point = deque_pop(deque);
      print_point(point);
    } else if (strcmp(cmd, DEQUE_CMD_INSERT) == 0) {
      point = read_point(cmd);
      deque_insert(deque, point);
    } else if (strcmp(cmd, DEQUE_CMD_REMOVE) == 0) {
      point = deque_remove(deque);
      print_point(point);
    } else if (strcmp(cmd, DEQUE_CMD_SIZE) == 0) {
      size = deque_size(deque);
      printf("%d\n", size);
    } else {
      fprintf(stderr, "Error: unexpected command \"%s\"\n", cmd);
      exit(EXIT_FAILURE);
    }
  }

  // Free the memory for our deque
  free_deque(deque);
  deque = NULL;
}

// Reads in a list of points from stdin in the format:
// n (the number of points to be read in)
// x1 y1
// x2 y2
// ...
// xn yn
//
// This polygon is given to inside_hull(), and the points which make up the
// convex hull are returned.
//
//  These points are then printed one per line.
void test_inside_hull() {
  int num_points, hull_points, i;
  Point *points;
  Point *hull;

  // Make sure we read num_points correctly
  if (!scanf("%d\n", &num_points)) {
    fprintf(stderr, "Error: missing number of points on the first line\n");
    exit(EXIT_FAILURE);
  }

  // We must have >= 3 points to perform the inside_hull() function
  if (num_points < 3) {
    fprintf(stderr, "Error: must provide at least 3 points\n");
    exit(EXIT_FAILURE);
  }

  // Allocate space for the points to be read in, and the output of inside_hull
  points = malloc(sizeof(*points) * num_points);
  assert(points);
  hull = malloc(sizeof(*hull) * num_points);
  assert(num_points);

  // Read in the num_points
  for (i = 0; i < num_points; i++) {
    // Feed NULL because there's no command name
    points[i] = read_point(NULL);
  }

  // Perform inside_hull()
  hull_points = inside_hull(points, num_points, hull);

  // Ensure inside_hull() completed successfully
  if (hull_points == INSIDE_HULL_ERROR) {
    fprintf(stderr, "Error: inside_hull() returned INSIDE_HULL_ERROR\n");
    exit(EXIT_FAILURE);
  } else if (hull_points == COLLINEAR_POINTS) {
    printf("The polygon provided contains consecutive collinear points\n");
  } else {
    // Print out the hull points
    for (i = 0; i < hull_points; i++) {
      print_point(hull[i]);
    }
  }

  // Free these Point arrays
  free(points);
  points = NULL;
  free(hull);
  hull = NULL;
}

// Returns whether or not the provided string is the empty string.
bool is_empty(char *str) {
  return (str[0] == '\0');
}

// Read in the next command from stdin, for the --deque option.
// This will read in up to size characters until whitespace or EOF
// is encountered.
// Returns false if EOF is reached, true otherwise.
// The command is stored in cmd, and terminated by a null byte ('\0').
// The caller should check whether cmd is the empty string (see is_empty()).
bool read_command(char *cmd, int size) {
  char c;
  int i;

  assert(size > 0);

  i = 0;
  while ((c = getchar()) != EOF) {
    // We can't store any characters past the (size - 1)th char,
    // and won't store any whitespace.
    if (isspace(c) || (i == size - 1)) {
      break;
    }
    cmd[i] = c;
    i++;
  }

  // Add the null byte
  cmd[i] = '\0';

  // Return whether or not a string was read
  return (c != EOF);
}

// Reads in and returns a Point by trying to read two doubles from stdin.
// If an error occurs the program will exit.
// The cmd argument is the name of the test_deque() command read.
// cmd can be NULL and an appropriate error message will be printed.
Point read_point(char *cmd) {
  Point point;

  // Try to read the x and y coordinates
  int coords_read = scanf("%lf %lf", &point.x, &point.y);

  // If we couldn't read the coordinates we'll give an error
  if (coords_read != 2) {
    if (cmd != NULL) {
      fprintf(stderr, "Error: expected x and y coordinates to follow \"%s\"\n",
        cmd);
    } else {
      fprintf(stderr, "Error: expected to read x and y coordinates\n");
    }
    exit(EXIT_FAILURE);
  }

  return point;
}

// Reads the command line options and returns OPT_ORIENTATION, OPT_DEQUE,
// OPT_INSIDE_HULL or OPT_HELP.
//
// If the command line arguments are invalid then this will print out an error,
// usage information and then exit.
int get_option(int argc, char **argv) {
  char *opt;

  // If they run this without any options let's just give them the usage,
  // rather than giving an error
  if (argc == 1) {
    print_usage(argv[0]);
    exit(EXIT_SUCCESS);
  } else if (argc > 2) {
    fprintf(stderr, "Error: expecting exactly one command line argument\n");
    print_usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  opt = argv[1];
  if (strcmp(opt, "-o") == 0 || strcmp(opt, "--orientation") == 0) {
    return OPT_ORIENTATION;
  } else if (strcmp(opt, "-d") == 0 || strcmp(opt, "--deque") == 0) {
    return OPT_DEQUE;
  } else if (strcmp(opt, "-i") == 0 || strcmp(opt, "--inside-hull") == 0) {
    return OPT_INSIDE_HULL;
  } else if (strcmp(opt, "-h") == 0 || strcmp(opt, "--help") == 0) {
    return OPT_HELP;
  }

  fprintf(stderr, "Error: unexpected command line argument \"%s\"\n", opt);
  print_usage(argv[0]);
  exit(EXIT_FAILURE);
}

// Prints the usage information for the command line tool
void print_usage(char *prog_name) {
  fprintf(stderr, "usage: %s [options] < <input_file>\n", prog_name);
  fprintf(stderr, "\n");
  fprintf(stderr, "options:\n");
  fprintf(stderr, "\t-o | --orientation \tTest the orientation() function\n");
  fprintf(stderr, "\t-d | --deque       \tTest deque functionality\n");
  fprintf(stderr, "\t-i | --inside-hull \tTest the inside_hull() function\n");
  fprintf(stderr, "\t-h | --help        \tPrint this help message\n");
}
