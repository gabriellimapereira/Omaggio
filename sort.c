#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "functions.h"

// ordena a lista de tarefas usando o algoritmo bubble sort
// recebe a cabeça da lista de tarefas (DoublyTaskList*)
// não retorna valor
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
                // troca as tarefas
                Task* temp = current->task;
                current->task = nextNode->task;
                nextNode->task = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

// ordena a lista de tarefas usando o algoritmo selection sort
// recebe a cabeça da lista de tarefas (DoublyTaskList*)
// não retorna valor
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
            // troca as tarefas
            temp = current->task;
            current->task = minNode->task;
            minNode->task = temp;
        }
    }
}

// ordena a lista de tarefas usando o algoritmo insertion sort
// recebe o ponteiro para a cabeça da lista de tarefas (DoublyTaskList**)
// não retorna valor
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

// divide a lista de tarefas em duas metades
// recebe a cabeça da lista de tarefas (DoublyTaskList*)
// retorna a segunda metade da lista (DoublyTaskList*)
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

// mescla duas listas de tarefas ordenadas
// recebe duas listas de tarefas (DoublyTaskList*)
// retorna a lista mesclada e ordenada (DoublyTaskList*)
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

// ordena a lista de tarefas usando o algoritmo merge sort
// recebe a cabeça da lista de tarefas (DoublyTaskList*)
// retorna a lista ordenada (DoublyTaskList*)
DoublyTaskList* mergeSort(DoublyTaskList* head) {
    if (head == NULL || head->next == NULL) return head;

    DoublyTaskList* secondHalf = splitList(head);

    head = mergeSort(head);
    secondHalf = mergeSort(secondHalf);

    return mergeLists(head, secondHalf);
}

// particiona a lista de tarefas em duas partes baseadas no pivô
// recebe a cabeça da lista de tarefas (DoublyTaskList*) e ponteiros para as listas menores e maiores (DoublyTaskList**)
// retorna o pivô da partição (DoublyTaskList*)
DoublyTaskList* partition(DoublyTaskList* head, DoublyTaskList** lesser, DoublyTaskList** greater) {
    if (head == NULL) return NULL;

    DoublyTaskList* pivot = head;
    DoublyTaskList* current = head->next;

    while (current != NULL) {
        if (current->task->priority < pivot->task->priority) {
            *lesser = addTaskToList_D(current->task, *lesser);  
        } else {
            *greater = addTaskToList_D(current->task, *greater);  
        }
        current = current->next;
    }

    return pivot;  
}

// concatena as listas menor, pivô e maior em uma única lista ordenada
// recebe as listas menor, pivô e maior (DoublyTaskList*)
// retorna a lista concatenada (DoublyTaskList*)
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

// ordena a lista de tarefas usando o algoritmo quick sort
// recebe a cabeça da lista de tarefas (DoublyTaskList*)
// retorna a lista ordenada (DoublyTaskList*)
DoublyTaskList* quickSort(DoublyTaskList* head) {
    if (head == NULL || head->next == NULL) return head;

    DoublyTaskList* lesser = NULL;
    DoublyTaskList* greater = NULL;
    DoublyTaskList* pivot = partition(head, &lesser, &greater);

    lesser = quickSort(lesser);
    greater = quickSort(greater);

    return concatenate(lesser, pivot, greater);
}
