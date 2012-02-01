#ifndef __MYCPP__H__
#define __MYCPP__H__

#include <Arduino.h>

/*	This library allows Arduino IDE
 *  to use the cpp new and delete
 *  operators.
 *  eg:
 *
 *  #include <NewDelete.h>
 *  myBar foo = new myBar;
 *  delete foo;
 *
 *	Also works for arrays:
 *  int* myArray = new int[5];
 *  delete[] myArray;
 *
 *  As this code is fairly standard
 *  I accept no credit, but I know
 *  many people want the
 *  functionality.
 *
 *  Happy programming!
 *
 *  Simon Howroyd, 2012
 *  Loughborough University Centre
 *  for Autonomous Systems, UK
 */

void * operator new(size_t size) { 
  return malloc(size); 
} 

void operator delete(void * ptr) { 
  free(ptr); 
}

void * operator new[](size_t size) { 
    return malloc(size); 
} 

void operator delete[](void * ptr) { 
    free(ptr); 
}
#endif
