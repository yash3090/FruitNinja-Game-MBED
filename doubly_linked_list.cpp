//================================================================
// Implementation for DLL module.
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"


/**
  *creates new ll node
*/

LLNode* create_llnode(void* data) {

    LLNode*  newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
  
    return newNode;
}

/**
  * creates new ll
*/
DLinkedList* create_dlinkedlist(void) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

/**
  * returns size of ll
*/
int getSize(DLinkedList* dLinkedList){
  return dLinkedList->size;
}

/**
  * returns head of ll
*/
LLNode* getHead(DLinkedList* dLinkedList){
  if(dLinkedList->size == 0) {
    return NULL;
  }
  return dLinkedList->head; 
}

/**
  * returns tail of ll
*/
LLNode* getTail(DLinkedList* dLinkedList){
if(dLinkedList->size == 0) {
    return NULL;
  }
  return dLinkedList->tail; 
}

/**
  * returns next node
*/
LLNode* getNext(LLNode* node){
  return node->next;
}

/**
  * returns prev node
*/
LLNode* getPrev(LLNode* node){
  return node->prev;
}

/**
  * returns data of node
*/
void* getData(LLNode* node){
  return node->data;
}

/**
  * inserts data after the node passed in 
*/
void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
  if (prev_node == NULL) {
    printf("the given previous node cannot be NULL");
    return;
  }

  LLNode* newNode = create_llnode(data); // creates new node with data passed in
  
  
  if(prev_node->next == NULL) {  // if prev_node was tail (edge case)
    prev_node->next = newNode;
    newNode->prev = prev_node;
    dLinkedList->tail = newNode;
  } else {
    (prev_node->next)->prev = newNode;
    newNode->next = prev_node->next;
    newNode->prev = prev_node;
    prev_node->next = newNode;
  }

  dLinkedList->size = dLinkedList->size + 1;
  return;
}

/**
  * inserts data before the node passed in 
*/
void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){
  if (next_node == NULL) {
    printf("the given next node cannot be NULL");
    return;
  }


  LLNode* newNode = create_llnode(data);
  
  
  if(next_node->prev == NULL) { // if next_node was head
    next_node->prev = newNode;
    newNode->next = next_node;
    dLinkedList->head = newNode;
  } else {
    (next_node->prev)->next = newNode;
    newNode->prev = next_node->prev;
    newNode->next = next_node;
    next_node->prev = newNode;
  }

  dLinkedList->size = dLinkedList->size + 1;

  return;
}

/**
  * inserts data to the head of ll
*/
void insertHead(DLinkedList* dLinkedList, void* data){
  if(dLinkedList->head == NULL){
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  }else{
    insertBefore(dLinkedList, dLinkedList->head, data);
  }
}

/**
  * inserts data to the tail of ll
*/
void insertTail(DLinkedList* dLinkedList, void* data){
  if(dLinkedList->tail == NULL){
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  }else{
    insertAfter(dLinkedList, dLinkedList->tail, data);
  }

}
/**
  * deletes a node from the ll
*/
void deleteNode(DLinkedList* dLinkedList, LLNode* Node){
  if(dLinkedList->size == 1) { // edge case if size == 1
    dLinkedList->head = NULL;
    dLinkedList->tail = NULL;
  } else if(dLinkedList->head == Node){ // edge case if node is head
    dLinkedList->head = Node->next;
    (Node->next)->prev = NULL;
  } else if(dLinkedList->tail == Node) { // edge case if node is tail
    dLinkedList->tail = Node->prev;
    (Node->prev)->next = NULL;
  } else {
    (Node->prev)->next = Node->next;
    (Node->next)->prev = Node->prev;
  }


  free(Node->data); // frees up data memort
  free(Node); // frees up memory
  dLinkedList->size--;
  return;
}


/**
  * destroys the list emptying memory
*/
void destroyList(DLinkedList* dLinkedList){

LLNode* temp = dLinkedList->head;
LLNode* temp_two;
while(temp!= NULL) { // iterating through ll to destroy data and nodes in ll
  temp_two = temp->next;
  free(temp->data);
  free(temp);
  temp = temp_two;
}
  
free(dLinkedList);
return;
}

/**
  * reverses the order of the ll
*/
void reverse(DLinkedList* dLinkedList)
{

// if size < 1 then no reverse
  if(dLinkedList->size == 0) {
    printf("size 0 linked list cannot be reversed\n");
    return;
  }
  if(dLinkedList->size > 1) {
    LLNode* temp = NULL;
    LLNode* current = dLinkedList->head;
    while (current != NULL) { // switches next and prev pointers
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;            
      current = current->prev;
    }
    // swaps head and tail
    LLNode* TempHead = dLinkedList->head;
    dLinkedList->head = dLinkedList->tail;
    dLinkedList->tail = TempHead;
  }
  return;

}     