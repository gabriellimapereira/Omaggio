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
    DoublyTaskList* aux;
    DoublyTaskList* nextNode;

    do {
        swapped = 0;
        aux = head;

        while (aux != NULL && aux->next != NULL) {
            nextNode = aux->next;
            if (aux->task->priority > nextNode->task->priority) {
                // troca as tarefas
                Task* temp = aux->task;
                aux->task = nextNode->task;
                nextNode->task = temp;
                swapped = 1;
            }
            aux = aux->next;
        }
    } while (swapped);
}

// ordena a lista de tarefas alfabeticamente pelo nome usando Bubble Sort
// recebe a cabeça da lista de tarefas (DoublyTaskList*)
// não retorna valor
void bubbleSortChar(DoublyTaskList* head) {
    if (head == NULL) return;

    int swapped;
    DoublyTaskList* aux;
    DoublyTaskList* nextNode;

    do {
        swapped = 0;
        aux = head;

        while (aux != NULL && aux->next != NULL) {
            nextNode = aux->next;
            if (strcmp(aux->task->name, nextNode->task->name) > 0) {
                Task* temp = aux->task;
                aux->task = nextNode->task;
                nextNode->task = temp;
                swapped = 1;
            }
            aux = aux->next;
        }
    } while (swapped);
}

// ordena a lista de tarefas usando o algoritmo selection sort
// recebe a cabeça da lista de tarefas (DoublyTaskList*)
// não retorna valor
void selectionSort(DoublyTaskList* head) {
    if (head == NULL) return;

    DoublyTaskList* aux;
    DoublyTaskList* comparator;
    DoublyTaskList* minNode;
    Task* temp;

    for (aux = head; aux != NULL; aux = aux->next) {
        minNode = aux;
        comparator = aux->next;

        while (comparator != NULL) {
            if (comparator->task->priority < minNode->task->priority) {
                minNode = comparator;
            }
            comparator = comparator->next;
        }

        if (minNode != aux) {
            // troca as tarefas
            temp = aux->task;
            aux->task = minNode->task;
            minNode->task = temp;
        }
    }
}

// ordena a lista de tarefas usando o algoritmo insertion sort
// recebe o ponteiro para a cabeça da lista de tarefas (DoublyTaskList*)
// retorna o ponteiro para a nova cabeça da lista
DoublyTaskList* insertionSort(DoublyTaskList* head) {
    if (head == NULL || head->next == NULL) return head;

    DoublyTaskList* aux = head->next;
    while (aux != NULL) {
        DoublyTaskList* comparator = head;
        
        while (comparator != aux && comparator->task->priority <= aux->task->priority) {
            comparator = comparator->next;
        }

        if (comparator != aux) {
            if (aux->prev != NULL) {
                aux->prev->next = aux->next;
            }
            if (aux->next != NULL) {
                aux->next->prev = aux->prev;
            }
            aux->next = comparator;
            aux->prev = comparator->prev;
            if (comparator->prev != NULL) {
                comparator->prev->next = aux;
            }
            comparator->prev = aux;

            if (head == comparator) {
                head = aux;
            }
        }

        aux = aux->next;
    }

    return head;
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
    DoublyTaskList* aux = head->next;

    while (aux != NULL) {
        if (aux->task->priority < pivot->task->priority) {
            *lesser = addTaskToList_D(aux->task, *lesser);  
        } else {
            *greater = addTaskToList_D(aux->task, *greater);  
        }
        aux = aux->next;
    }

    return pivot;  
}

// concatena as listas menor, pivô e maior em uma única lista ordenada
// recebe as listas menor, pivô e maior (DoublyTaskList*)
// retorna a lista concatenada (DoublyTaskList*)
DoublyTaskList* concatenate(DoublyTaskList* lesser, DoublyTaskList* pivot, DoublyTaskList* greater) {
    if (lesser != NULL) {
        DoublyTaskList* aux = lesser;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = pivot;
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
