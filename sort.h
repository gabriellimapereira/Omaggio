#ifndef SORT_H
#define SORT_H

#include "functions.h"

// bubble
void bubbleSort(DoublyTaskList* head);

// selection
void selectionSort(DoublyTaskList* head);

// insertion
void insertionSort(DoublyTaskList** head);

// merge
DoublyTaskList* splitList(DoublyTaskList* head);
DoublyTaskList* mergeLists(DoublyTaskList* list1, DoublyTaskList* list2);
DoublyTaskList* mergeSort(DoublyTaskList* head);

// quick
DoublyTaskList* partition(DoublyTaskList* head, DoublyTaskList** lesser, DoublyTaskList** greater);
DoublyTaskList* concatenate(DoublyTaskList* lesser, DoublyTaskList* pivot, DoublyTaskList* greater);
DoublyTaskList* quickSort(DoublyTaskList* head);

#endif // SORT_H
