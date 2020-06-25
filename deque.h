/* * * * * * *
 * Deque module (i.e., double ended queue) for Assignment 1
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

#ifndef DEQUE_H
#define DEQUE_H

#include "point.h"

//Use the double Linked list to implement the deque 
//Create node struct for deque to store Point 
//And deque struct at the same time 

typedef struct node Node;
typedef struct deque Deque;
struct node {
    Point pointdata;   // the information of Point 
    Node *next;        // next node it linked
    Node *prev;        // last node it linked
};

struct deque {
    Node *head;       // the head of deque
    Node *tail;       // the tail of deque
    int size;         // number of element store in the deque
};

// Create a new empty Deque and return a pointer to it
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
Deque *new_deque();

// Free the memory associated with a Deque
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
void free_deque(Deque *deque);

// Add a Point to the top of a Deque
//
// TODO: Fill in the runtime of this function
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
void deque_push(Deque *deque, Point data);

// Add a Point to the bottom of a Deque
//
// TODO: Fill in the runtime of this function
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
void deque_insert(Deque *deque, Point data);

// Remove and return the top Point from a Deque
//
// TODO: Fill in the runtime of this function
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
Point deque_pop(Deque *deque);

// Remove and return the bottom Point from a Deque
//
// TODO: Fill in the runtime of this function
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
Point deque_remove(Deque *deque);

// Return the number of Points in a Deque
//
// TODO: Fill in the runtime of this function
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
int deque_size(Deque *deque);

// TODO: Add any other functions you might need for your Deque module

#endif
