//------------------------------------------------------------------------------
// Pablo Zepeda
// 2021 Winter 
// List.h
// Header file for List ADT
//------------------------------------------------------------------------------

#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE

// Exported type ---------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors -----------------------------------------------------

// Creates and returns a new empty list.
List newList(void);

//Frees all heap memory associated with *pL, and
//sets *pL to NULL.
void freeList(List* pL);

// Access functions -------------------------------------------------------------

// Returns the number of elements in L.
int length(List L);

// Returns index of cursor element if defined, -1 otherwise.
int index(List L);

// Returns front element of L. Pre: length() > 0
int front(List L);

// Returns back element of L. Pre: length() > 0
int back(List L);

// Returns cursor element of L. Pre: length() > 0, index() >= 0
int get(List L);

// Returns true (1) iff Lists A and B are in the same state,
// and returns false (0) otherwise.
int equals(List A, List B);

// Manipulation procedures ------------------------------------------------------

// Resets L to its original empty state.
void clear(List L);

// Overwrites the cursor element's data with x.
// Pre: length() > 0, index() >= 0
void set(List L, int x);

// If L is non-empty, it sets the cursor under the front element,
// otherwise it does nothing.
void moveFront(List L);

// If L is non-empty, it sets the cursor under the back element,
// otherwise it does nothing.
void moveBack(List L);

// If the cursor is defined and not at front, move the cursor one
// step toward the front of L; If the cursor is defined and at
// the front, the cursor becomes undefined; if the cursor is
// undefined do nothing
void movePrev(List L);

// If the cursor is defined and not at the back, move the cursor one step
// toward the back of L. If the cursor is defined and at the back, the cursor
// becomes undefined. If the cursor is undefined  do nothing.
void moveNext(List L);

// Insert a new element into L. If L is non-empty, insertion takes place before
// the front element.
void prepend(List L, int data);

// Insert a new element into L. If L is non-empty, insertion takes place after
// the back element.
void append(List L, int data);

// Insert a new element before the cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, int data);

// Insert a new element after the cursor.
// Pre: length() > 0, index() > = 0
void insertAfter(List L, int data);

// Delete the front element.
// Pre: length() > 0
void deleteFront(List L);

// Delete the back element.
// Pre: length() > 0
void deleteBack(List L);

// Delete the cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L);

// Other Operations --------------------------------------------------------------

// Prints to the file pointed to by out,
// a string representation of L consisting
// of a space separated sequence of integers
// with the front on the left.
void printList(FILE* out, List L);

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L);

// Returns a new List which is the  concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.

//List concatList(List A, List B);

#endif



