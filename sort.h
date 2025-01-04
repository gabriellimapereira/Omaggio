#ifndef SORT_H
#define SORT_H

#include "functions.h"

void bubbleSort(DoublyTaskList* head);
void selectionSort(DoublyTaskList* head);
void insertionSort(DoublyTaskList** head);
DoublyTaskList* mergeSort(DoublyTaskList* head);
DoublyTaskList* quickSort(DoublyTaskList* head);
DoublyTaskList* splitList(DoublyTaskList* head);
DoublyTaskList* mergeLists(DoublyTaskList* list1, DoublyTaskList* list2);
DoublyTaskList* partition(DoublyTaskList* head, DoublyTaskList** lesser, DoublyTaskList** greater);
DoublyTaskList* concatenate(DoublyTaskList* lesser, DoublyTaskList* pivot, DoublyTaskList* greater);

#endif // SORT_H
