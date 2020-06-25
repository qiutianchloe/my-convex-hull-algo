/* * * * * * *
 * Implementation of the Inside Hull algorithm for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2019
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Tian Qiu 988121>
 */

//                   WRITE YOUR IMPLEMENTATION HERE
//
// You should fill in the function definitions for orientation() and
// inside_hull() in this file.
//
// Don't be shy to add any extra functions or types you may need.

#include <stdio.h>
#include <stdlib.h>

#include "deque.h"
#include "convex-hull.h"

// Returns the orientation of Point p2 in relation to the line segment p0p1.
// If p2 is to the left of p0p1 then it returns LEFT ('l'), if p2 is to the
// right it returns RIGHT ('r').
// If p0, p1 and p2 are collinear then COLLINEAR ('c') is returned.
char orientation(Point p0, Point p1, Point p2) {
    double check_value; 
    check_value = (p1.y-p0.y)*(p2.x-p1.x)-(p1.x-p0.x)*(p2.y-p1.y); 
    if(check_value == 0){
        return 'c'; 
    }else if(check_value > 0){
        return 'r'; 
    }else{
        return 'l'; 
    }
}

// Takes a polygon (i.e. an array of points) given in counter-clockwise order
// with n points.
//
// Stores the points of the convex hull into the hull array (the last point
// should NOT be the same as the first point), and returns the number of
// points which are in the convex hull.
//
// If three successive points in the polygon are collinear then the algorithm
// should terminate and COLLINEAR_POINTS should be returned.
//
// If an error occurs this function should return INSIDE_HULL_ERROR.
int inside_hull(Point *polygon, int n, Point *hull) {
  //check the validation of the iput 
  if(n<3){
    return INSIDE_HULL_ERROR; 
  }
  if(orientation(polygon[0], polygon[1], polygon[2])==COLLINEAR){
    return COLLINEAR_POINTS; 
  }

  //create a new deque as a temphull
  Deque *temphull = new_deque(); 

  int i = 3; //counter

  // check the postion of first three points to initialize the temphull
  if(orientation(polygon[0], polygon[1], polygon[2])==LEFT){
    //condition that the third point is on the left of verctor of first two 
    deque_push(temphull, polygon[2]); 
    deque_push(temphull, polygon[1]);   
    deque_push(temphull, polygon[0]); 
    deque_push(temphull, polygon[2]);    
  }else{
    //condition that the third point is on the right of verctor of first two 
    deque_push(temphull, polygon[2]); 
    deque_push(temphull, polygon[0]);   
    deque_push(temphull, polygon[1]); 
    deque_push(temphull, polygon[2]);   
  }

  //the temphull has already been initialized
  // go through all the other points to check whether they are on the convex hull
  while(i<n){
    // get the point that need to check in this loop
    Point currentPoint = polygon[i]; 
    //find the first two point on the top of the array
    Point ctm1 = temphull->tail->prev->pointdata; 
    Point ct = temphull->tail->pointdata;  
    //find the last two point on the bottom of the array
    Point cb = temphull->head->pointdata;
    Point cbp1 = temphull->head->next->pointdata; 

    // if this point as already beed involved in the temp convex hull
    if(orientation(ctm1, ct, currentPoint)==LEFT && orientation(cb, cbp1, currentPoint)==LEFT){
      // do nothing with this point , continue the for loop
      i=i+1; 
      continue; 
    }

    // for the points that is not involved in the temp convex hull
    // that is not on the left hand side of the segment of two point ahead
    
    //check with the start of temp convex hull
    while(orientation(ctm1, ct, currentPoint)!=LEFT){
      if(orientation(ctm1, ct, currentPoint)==COLLINEAR_POINTS){
        return COLLINEAR_POINTS; 
      }
      else{
        //remove the last node of temp convex hull
        deque_remove(temphull); 

        //updata the information, to check whether on the lefthandside now
        ctm1 = temphull->tail->prev->pointdata; 
        ct = temphull->tail->pointdata; 
      }
    }
    // insert in temp convex hull so that it is becomes the points on the convex hull
    deque_insert(temphull, currentPoint); 

    //check with the end of tempconvex hull
    while(orientation(cb, cbp1, currentPoint)!=LEFT){
      if(orientation(cb, cbp1, currentPoint)==COLLINEAR){
        return COLLINEAR_POINTS; 
      }else{
        //pop the first node of temp convex hull
        deque_pop(temphull); 

        //update the information, to check whether on the lefthandside now
        cb = temphull->head->pointdata; 
        cbp1 = temphull->head->next->pointdata; 
      }
    }

    // insert in temp convex hull so that it is becomes the points on the convex hull
    deque_push(temphull, currentPoint); 

    //check another point
    i=i+1; 
  }


  //delete the repeated node
  deque_remove(temphull);

  int j=0; //counter
  int numOfElement = deque_size(temphull); //number of points on convex hull

  //store the points in the Hull array
  for(j=0; j<numOfElement; j++){

    // store the point in counter-clockwise order
    Point current = deque_pop(temphull); 
    hull[j] = current; 
  } 

  //free the deque
  free(temphull); 
  //return number of points on the convex hull
  return numOfElement; 
}

