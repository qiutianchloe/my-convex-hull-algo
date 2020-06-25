/* * * * * * *
 * Deque module (i.e., double ended queue) for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2019
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Tian Qiu 988121>
 */

//                   WRITE YOUR IMPLEMENTATION HERE
//
// You should fill in the function definitions for
//  - new_deque()
//  - free_deque()
//  - deque_push()
//  - deque_insert()
//  - deque_pop()
//  - deque_remove()
//  - deque_size()
//
// Don't be shy to add any extra functions or types you may need.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "deque.h"
#include "point.h"

// TODO: Fill in this struct definition, or change the typedef in deque.h


// I fill the struct in the "deque.h" file
// And add another type Node in the deque.h





// Create a new empty Deque and return a pointer to it
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
Deque *new_deque() {

  // allocate the memory for the struct deque
  Deque *newdeque; 
  newdeque = (Deque *)malloc(sizeof(*newdeque)); 
  assert(newdeque!=NULL); 

  // initialize the size of deque 0
  newdeque->size = 0; 

  // initialize the head and pointer as NULL 
  newdeque->head = NULL; 
  newdeque->tail = NULL; 

  // return the deque that already been initialized
  return newdeque;
}





// Free the memory associated with a Deque
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
void free_deque(Deque *deque) {

  Node *current; 
  Node *prev; 
  current = deque->head;

  // free all the node in the deque
  while(current!=NULL){
    prev = current; 
    current = current->next; 
    free(prev); 
  }

  //free deque itself
  free(deque); 
}

// Add a Point to the top of a Deque
//
// TODO: Fill in the runtime of this function
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
void deque_push(Deque *deque, Point data) {

  // allocate the memory for the struct deque
  Node *newnode; 
  newnode = (Node *)malloc(sizeof(*newnode)); 
  assert(newnode!=NULL); 

  //store the Point information in the node
  newnode->pointdata = data; 

  // if this is the first element insert into the deque
  if(deque->head==NULL){

    //make head and tail point both point to it
    deque->head = newnode; 
    deque->tail = newnode;

    //there is no node connected to it
    newnode->next = NULL; 
    newnode->prev = NULL;

    //increase the size of the deque(plus 1) 
    deque->size = deque->size+1; 
  }else{
    //this is not the first node insert into the deque

    //make this node next pointer point to the deque's head node
    newnode->next = deque->head; 

    //and make it prev as NULL
    newnode->prev = NULL; 

    //make old deque head node's prev point to this node
    deque->head->prev = newnode; 

    //make the node become the head of the deque
    deque->head = newnode; 

    // increase the size of the deque (plus 1)
    deque->size = deque->size+1;
  }
}

// Add a Point to the bottom of a Deque
//
// TODO: Fill in the runtime of this function
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
void deque_insert(Deque *deque, Point data) {

  // allocate the memory for the struct deque
  Node *newnode; 
  newnode = (Node *)malloc(sizeof(*newnode)); 
  assert(newnode!=NULL); 

  //store the Point information in the node
  newnode->pointdata = data; 

  // if this is the first element insert into the deque
  if(deque->tail==NULL){

    //make head and tail point both point to it
    deque->tail = newnode; 
    deque->head = newnode; 
    
    //there is no node connected to it
    newnode->next = NULL; 
    newnode->prev = NULL; 

    //increase the size of the deque(plus 1)
    deque->size = deque->size+1; 
  }else{
    //this is not the first node insert into the deque 

    //make this node prev pointer point to the deque's head node
    newnode->prev = deque->tail; 

    //make this node next pointer equal to NULL
    newnode->next = NULL; 

    //make the deque tail node point to this node
    deque->tail->next = newnode; 

    //make this node become the deque tail node
    deque->tail = newnode; 

    //increase the size of the deque(plus 1)
    deque->size = deque->size+1;
  }
}

// Remove and return the top Point from a Deque
//
// TODO: Fill in the runtime of this function
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
Point deque_pop(Deque *deque) {

  // get the Point information of head node of deque 
  Point headpoint = deque->head->pointdata; 

  //create a node pointer point to the node that will be popped
  Node *prevhead = deque->head; 

  //create a node pointer point to the new head node
  Node *currenthead = deque->head->next; 

  
  if(currenthead==NULL){
    //if there is no node in deque after pop this node

    //make tail and head of deque equal to NULL
    deque->tail = NULL;
    deque->head = NULL;  
  }else{
    //there is other node in deque 

    //make the deque head point to the new head node
    currenthead->prev = NULL;
    deque->head = currenthead; 
  }

  //decrease the size of the deque(minus 1)
  deque->size = deque->size-1;

  //free the node
  free(prevhead); 

  //return the value of the Point 
  return headpoint; 
}

// Remove and return the bottom Point from a Deque
//
// TODO: Fill in the runtime of this function
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
Point deque_remove(Deque *deque) {

  // get the Point information of tail node of deque
  Point tailpoint = deque->tail->pointdata;  

  //create a node pointer point to the node that will be removed
  Node *prevtail = deque->tail; 

  //create a node pointer point to the new head node
  Node *currenttail = deque->tail->prev; 
  if(currenttail==NULL){
    //if there is no node in deque after pop this node

    //make tail and head of deque equal to NULL
    deque->tail = NULL;
    deque->head = NULL;  
  }else{
    //there is other node in deque 

    //make the deque tail point to the new head node
    currenttail->next = NULL;
    deque->tail = currenttail; 
  }

  //decrease the size of the deque(minus)
  deque->size = deque->size-1;

  //free the node
  free(prevtail);

  //return the value of the Point 
  return tailpoint; 
}

// Return the number of Points in a Deque
//
// TODO: Fill in the runtime of this function
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE

int deque_size(Deque *deque) {
  //return the size of deque
  return deque->size; 
}

// TODO: Add any other functions you might need for your Deque module
