//------------------------------------------------------------------------------
// Pablo Zepeda
// List.c
// Implementation file for List ADT
//------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs ---------------------------------------------------------------------

//private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* previous;
    struct NodeObj* next;
} NodeObj;

//private Node type
//Pointer to NodeObj struct
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors -----------------------------------------------------

// newNode()
// Returns reference to a new NodeObj struct.
// Initializes data, previous, next fields.
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->previous = NULL;
    N->next = NULL;
    return(N);
}

// freeNode()
// frees heap memory pointed to by the *pN
// it sets *pN to NULL.
//pointer to a pointer
void freeNode(Node* pN){
    if(pN != NULL && *pN !=NULL){
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Returns reference to a new empty List object.
List newList(){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}

// freeList()
// Frees all heap memory pointed to by the List *pL
// it sets *pL to NULL
// pointer to pointer
// Delete the Nodes pointed to by the listObj
void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        
        while(length(*pL) > 0){
            deleteFront(*pL);
        }
        
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -------------------------------------------------------------
// Returns the number of elements in L or List.
int length(List L){
    if(L == NULL){
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if(L == NULL){
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }
    if(L->cursor == NULL){
        return -1;          // cursor element not defined
    }
    return L->index;
}

// Returns front element of L.
// Pre: length() > 0
// Else the the list is empty or there's no list
int front(List L){
    if(L == NULL){
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    if(length(L) > 0){
        return L->front->data; //Precondition satified
    }
    if(length(L) <= 0){
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }
    return 0; //get's rid of the warning, "control may reach end of non-void function"
    
}

// Returns back element of L.
// Pre: length() > 0
int back(List L){
    if(L == NULL){
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
    }
    if(length(L) > 0){
           return L->back->data; //Precondition satified
       }
    if(length(L) <= 0){
           printf("List Error: calling back() on an empty List\n");
           exit(1);
       }
    return 0; //get's rid of the warning, "control may reach end of non-void function"
}

// Returns cursor element of L.
// Pre: length() > 0, index() >= 0
int get(List L){
    if(L == NULL){
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0 || index(L) < 0){
        printf("List Error: calling get() on an empty List or undefined List\n");
        exit(1);
    }
    if(length(L) > 0 && index(L) >= 0) {
        return L->cursor->data;
    }
    return 0; //get's rid of the warning, "control may reach end of non-void function"
}

// Returns true (1) iff List A and B are in the same state
// and returns false (0) otherwise.
int equals(List A, List B){
    if(A == NULL || B == NULL){
           printf("List Error: calling equals() on NULL List reference\n");
           exit(1);
       }
    Node listA = NULL; // temporary pointers used to transverse each list
    Node listB = NULL; // without changing the lists
    
    listA = A->front;
    listB = B->front;
    
    if (length(A) == length(B)){
        for(int i = 0; i < length(A); i++){
            if(listA->data != listB->data){
                listA = listB = NULL;
                return 0; //lists are not equvalient
            }
            listA = listA->next;
            listB = listB->next;
        }
        return 1; //lists are equvalient
    }
     return 0; //get's rid of the warning, "control may reach end of non-void function"
}

// Manipulation procedures ------------------------------------------------------

// Resets L to its original empty state.
void clear(List L){
    if(L == NULL){
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
    Node location = L->front;
    while(location != NULL){
        deleteFront(L);
        location = L->front; // After every deletion there's a new front
    }                       // Location gets released from the stack when the func ends
    L->length = 0;
    L->index = -1;
    L->front = NULL;
    L->cursor = NULL;
    L->back = NULL;
}

// Overwrites the cursor element's data with x.
// Pre: length() > 0, index() >= 0
void set(List L, int x){
    if(L == NULL){
           printf("List Error: calling set() on NULL List reference\n");
           exit(1);
       }
    if(length(L) > 0 && index(L) >= 0){
        L->cursor->data = x;
    }
}

// If L is non-empty, it sets the cursor under the front element,
// otherwise it does nothing.
void moveFront(List L){
    if(L == NULL){
              printf("List Error: calling moveFront() on NULL List reference\n");
              exit(1);
          }
    if(length(L) > 0){
        L->cursor = L->front;
        L->index = 0;
    }
}

// If L is non-empty, it sets the cursor under the back element,
// otherwise it does nothing.
void moveBack(List L){
    if(L == NULL){
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
    if(length(L) > 0){
        L->cursor = L->back;
        L->index = length(L) - 1;
    }
}

// If the cursor is defined and not at the front, move the cursor one
// step toward the front of L; If the cursor is defined and at
// the front, the cursor becomes undefined; If the cursor is
// undefined do nothing
void movePrev(List L){
    if(L == NULL){
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }
    if (index(L) != -1 && index(L) > 0){
        L->cursor = L->cursor->previous; //move the cursor to the prev NodeObj
        L->index--;
    }
    else if(L->cursor != NULL && index(L) == 0){ //cursor is at the front
        L->cursor = NULL;
        L->index = -1;
    }
}

// If the cursor is defined and not at the back, move the cursor one step
// toward the back of L. If the cursor is defined and at the back, the cursor
// becomes undefined. If the cursor is undefined do nothing.
void moveNext(List L){
    if(L == NULL){
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    if(L->cursor != NULL && L->cursor != L->back){
        L->cursor = L->cursor->next;      //move the cursor toward the back
        L->index++;
    }
    else if(L->cursor != NULL && L->cursor == L->back){
        L->cursor = NULL;                //cursor was at the back & is now undefined
        L->index = -1;
    }
}

// Insert a new element into L. If L is non-empty, insertion takes place before
// the front element.
void prepend(List L, int data){
    if(L == NULL){
           printf("List Error: calling prepend() on NULL List reference\n");
           exit(1);
       }
    Node temp = NULL;
    temp = newNode(data);
    temp->next = L->front;

    if(length(L) > 0){    // List has elements
        L->front->previous = temp;
    }
    L->front = temp;     // new front element of the list, whether list was previously empty or not
    L->length++;

    if(L->cursor != NULL){
        L->index++;     // cursor is defined
    }
    
    if(length(L) == 1){  // the inserted node is the only node in the list
        L->back = temp;
    }
}

// Insert a new element into L. If L is non-empty, insertion takes place after
// the back element.
void append(List L, int data){
    if(L == NULL){
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
    Node temp = NULL;
    temp = newNode(data);
    temp->previous = L->back;
    
    if(length(L) == 0){ // list is empty
        L->front = temp;
        L->back = temp;
        L->length++;
    }else if(length(L) > 0){   // List has elements
        L->back->next = temp;
        L->back = temp; // new back element of the list
        L->length++;
    }
   
}

// Insert a new element before the cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, int data){
    if(L == NULL){
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    if(index(L) == 0){
        prepend(L, data); // cursor is at the front element
    }
    else if(length(L) > 0 && index(L) >= 0){
        Node temp = newNode(data);
        temp->previous = L->cursor->previous;
        L->cursor->previous->next = temp;
        L->cursor->previous = temp;
        temp->next = L->cursor;
        L->index++;
        L->length++;
        
    }
}

// Insert a new element after the cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, int data){
    if(L == NULL){
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    if(index(L) == length(L)-1){ //cursor is at the back of the list
        append(L, data);
    }
    else if(length(L) > 0 && index(L) >= 0){
        Node temp = newNode(data);
        temp->previous = L->cursor;
        temp->next = L->cursor->next;
        L->cursor->next->previous = temp;
        L->cursor->next = temp;
        L->length++;
    }
}

// Delete the front element.
// Pre: length() > 0
void deleteFront(List L){
    if(L == NULL){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
       }
    if(length(L) == 0){
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(1);
    }
    Node temp = L->front;
    
    if(length(L) > 1){      // Redefine the new front element
        L->front = L->front->next;
        L->front->previous = NULL;
       } else{              // Deleting the only element in the list
           L->front = NULL;
           L->back = NULL;
       }
    
    freeNode(&temp);        // Delete the front element by indirection, pointer to pointer
    L->length--;
    if(index(L) == 0){      // cursor at the beginning
        L->cursor = NULL;
        L->index = -1;
    }
    if(L->cursor != NULL){
        L->index--;        // cursor is defined
    }
  
}

// Delete the back element.
// Pre: length() > 0
void deleteBack(List L){
    if(L == NULL){
         printf("List Error: calling deleteBack() on NULL List reference\n");
         exit(1);
    }
    if(length(L) == 0){
        printf("List Error: calling deleteBack() on an empty List\n");
        exit(1);
    }
    if(length(L) == 1){
        freeNode(&(L->back)); // Delete the only element
        L->front = NULL;
        L->back = NULL;
        L->length = 0;
        
        if(index(L) == 0){
            L->cursor = NULL;
            L->index = -1;
        }
    }
    else if(length(L) > 1){
        
        if(L->cursor == L->back){   // cursor is at back element
                   L->cursor = NULL;
                   L->index = -1;
               }
        
        Node temp = L->back;
        L->back = L->back->previous;  // redefine a new back
        L->back->next = NULL;
        freeNode(&temp);             // back element just got canceled
        L->length--;
        
    }
}

// Delete the cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L){
    if(L == NULL){
         printf("List Error: calling delete() on NULL List reference\n");
         exit(1);
    }
    if(L->cursor == NULL){
         printf("List Error: calling delete() on NULL List cursor\n");
         exit(1);
    }
    if (index(L) == 0){
        deleteFront(L);  // cursor is at the first element
    }
    else if(index(L) > 0){
        Node temp = L->cursor;
        temp->previous->next = temp->next;
        if(index(L) == length(L) - 1){  // cursor is at the back
            L->back = temp->previous;
        }else{
            temp->next->previous = temp->previous;
        }
        L->cursor = NULL;
        L->index = -1;
        L->length--;
        freeNode(&temp);
    }
}

// Other Functions --------------------------------------------------------------

// Prints to the file pointed to by out,
// a string representation of L consisting
// of a space separated sequence of integers
// with the front on the left.
void printList(FILE* out, List L){
    if(L == NULL){
            printf("List Error: calling printList() on NULL List reference\n");
            exit(1);
       }
    moveFront(L);    // Start at the front & iterate through the list
    while(L->cursor != NULL){
        fprintf(out, "%d ", get(L)); // write to the file
        moveNext(L);
    }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new List is undefined,
// regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L){
    if(L == NULL){
               printf("List Error: calling copyList() on NULL List reference\n");
               exit(1);
          }
    List tempList = newList();
    Node temp = L->front;
    
    while(temp != NULL){ //start at the front & copy data into the new list
        append(tempList, temp->data);
        temp = temp->next;
    }
    return tempList;  // list is copied 
}
