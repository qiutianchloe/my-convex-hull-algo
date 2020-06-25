/* * * * * * *
 * Point data structure with x and y coordinate for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2019
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Tian Qiu 988121>
 */

// You must not change any of the code already provided in this file, such as
// type definitions, constants or functions.
//
// You may, however, add additional functions and/or types which you may need
// while implementing your algorithms and data structures.

#ifndef POINT_H
#define POINT_H

typedef struct point Point;
struct point {
  double x;
  double y;
};

// Returns a new Point (note, this is not a pointer to a Point)
// Since it's not allocated using dynamic memory allocation it does not
// need to be freed
Point new_point(double x, double y);

// Prints (on its own line) the Point in the format "x y"
void print_point(Point p);

// TODO: Add any other functions you may need

#endif
