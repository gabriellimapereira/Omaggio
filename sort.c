#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "functions.h"

//bubble
void bubbleSort(DoublyTaskList* head) {
    if (head == NULL) return;

    int swapped;
    DoublyTaskList* current;
    DoublyTaskList* nextNode;

    do {
        swapped = 0;
        current = head;

        while (current != NULL && current->next != NULL) {
            nextNode = current->next;
            if (current->task->priority > nextNode->task->priority) {
                // Swap tasks
                Task* temp = current->task;
                current->task = nextNode->task;
                nextNode->task = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

// selection
void selectionSort(DoublyTaskList* head) {
    if (head == NULL) return;

    DoublyTaskList* current;
    DoublyTaskList* comparator;
    DoublyTaskList* minNode;
    Task* temp;

    for (current = head; current != NULL; current = current->next) {
        minNode = current;
        comparator = current->next;

        while (comparator != NULL) {
            if (comparator->task->priority < minNode->task->priority) {
                minNode = comparator;
            }
            comparator = comparator->next;
        }

        if (minNode != current) {
            // Swap tasks
            temp = current->task;
            current->task = minNode->task;
            minNode->task = temp;
        }
    }
}

// insertion
void insertionSort(DoublyTaskList** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    DoublyTaskList* current = (*head)->next;
    while (current != NULL) {
        DoublyTaskList* comparator = *head;
        while (comparator != current && comparator->task->priority <= current->task->priority) {
            comparator = comparator->next;
        }

        if (comparator != current) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            current->next = comparator;
            current->prev = comparator->prev;
            if (comparator->prev != NULL) {
                comparator->prev->next = current;
            }
            comparator->prev = current;

            if (*head == comparator) {
                *head = current;
            }
        }

        current = current->next;
    }
}

// merge
DoublyTaskList* splitList(DoublyTaskList* head) {
    if (head == NULL || head->next == NULL) return head;

    DoublyTaskList* middle = head;
    DoublyTaskList* fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            middle = middle->next;
            fast = fast->next;
        }
    }

    DoublyTaskList* secondHalf = middle->next;
    middle->next = NULL;
    return secondHalf;
}

DoublyTaskList* mergeLists(DoublyTaskList* list1, DoublyTaskList* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    if (list1->task->priority <= list2->task->priority) {
        list1->next = mergeLists(list1->next, list2);
        if (list1->next != NULL) {
            list1->next->prev = list1;
        }
        list1->prev = NULL;
        return list1;
    } else {
        list2->next = mergeLists(list1, list2->next);
        if (list2->next != NULL) {
            list2->next->prev = list2;
        }
        list2->prev = NULL;
        return list2;
    }
}

DoublyTaskList* mergeSort(DoublyTaskList* head) {
    if (head == NULL || head->next == NULL) return head;

    DoublyTaskList* secondHalf = splitList(head);

    head = mergeSort(head);
    secondHalf = mergeSort(secondHalf);

    return mergeLists(head, secondHalf);
}

// quick
DoublyTaskList* partition(DoublyTaskList* head, DoublyTaskList** lesser, DoublyTaskList** greater) {
    DoublyTaskList* pivot = head;
    DoublyTaskList* current = head->next;

    *lesser = NULL;
    *greater = NULL;

    while (current != NULL) {
        if (current->task->priority <= pivot->task->priority) {
            current->next = *lesser;
            *lesser = current;
        } else {
            current->next = *greater;
            *greater = current;
        }
        current = current->next;
    }

    return pivot;
}

DoublyTaskList* concatenate(DoublyTaskList* lesser, DoublyTaskList* pivot, DoublyTaskList* greater) {
    if (lesser != NULL) {
        DoublyTaskList* current = lesser;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = pivot;
    } else {
        lesser = pivot;
    }
    pivot->next = greater;
    return lesser;
}

DoublyTaskList* quickSort(DoublyTaskList* head) {
    if (head == NULL || head->next == NULL) return head;

    DoublyTaskList* lesser = NULL;
    DoublyTaskList* greater = NULL;
    DoublyTaskList* pivot = partition(head, &lesser, &greater);

    lesser = quickSort(lesser);
    greater = quickSort(greater);

    return concatenate(lesser, pivot, greater);
}
