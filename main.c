#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "sort.h"

DoublyTaskList* sortList(DoublyTaskList* head) {
    int choice;

    printf("\n--- escolha um algoritmo de ordenação ---\n");
    printf("1. bubble sort\n");
    printf("2. selection sort\n");
    printf("3. insertion sort\n");
    printf("4. merge sort\n");
    printf("5. quick sort\n");
    printf("-----------------------------------------\n");
    printf("digite o número do algoritmo desejado: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            bubbleSort(head);
            break;
        case 2:
            selectionSort(head);
            break;
        case 3:
            insertionSort(&head);
            break;
        case 4:
            head = mergeSort(head);
            break;
        case 5:
            head = quickSort(head);
            break;
        default:
            printf("escolha inválida! nenhuma alteração foi feita. escolha algo válido! :/\n");
            break;
    }

    return head;
}

void userMenu(User* currentUser) {
    system("clear");
    int userOption;

    do {
        printf("\n============ menu do usuário ============\n");
        printf("1 - listar todas as tarefas (lista normal)\n");
        printf("2 - inserir nova tarefa\n");
        printf("3 - ordenar lista de tarefas (lista dupla)\n");
        printf("4 - listar fila tarefas pendentes\n");
        printf("5 - listar tarefas concluídas\n");
        printf("6 - concluir tarefa pendente da fila\n");
        printf("0 - voltar ao menu principal\n");
        printf("=========================================\n");
        printf("escolha uma opção: ");
        scanf("%d", &userOption);
        clearBuffer();

        switch (userOption) {
            case 0:
                break;
            case 1:
                displayTaskListRecursive(currentUser->taskList);
                break;
            case 2: {
                Task* newTask = allocateTask();
                newTask = setterTask(newTask, currentUser->taskList);
                if (newTask->status == 1) {
                    currentUser->completedTasks = addTaskToCircularList(newTask, currentUser->completedTasks);
                } else {
                    if (currentUser->pendingTasks == NULL) {
                        currentUser->pendingTasks = allocatePendingTasks();
                    }
                    insertTaskIntoPendingList(currentUser->pendingTasks, newTask);
                }
                currentUser->taskList = addTaskToList(newTask, currentUser->taskList);
                currentUser->doublyTaskList = addTaskToList_D(newTask, currentUser->doublyTaskList);
                printf("tarefa registrada com sucesso!\n");
                break;
            }
            case 3:
                printf("lista antes da ordenação: \n");
                displayDoublyTaskList(currentUser->doublyTaskList);
                currentUser->doublyTaskList = sortList(currentUser->doublyTaskList);
                printf("lista ordenada! lista após a ordenação:\n");
                displayDoublyTaskList(currentUser->doublyTaskList);
                break;
            case 4:
                displayPendingTasks(currentUser->pendingTasks);
                break;
            case 5:
                displayCompletedTasks(currentUser->completedTasks);
                break;
            case 6:
                completeTask(currentUser->pendingTasks, currentUser->completedTasks);
                break;
            default:
                printf("opção inválida. tente novamente.\n");
        }
    } while (userOption != 0);
}

void mainMenu(User* userList) {
    int option;

    do {
        printf("\n============ menu principal ============\n");
        printf("1 - logar como usuário\n");
        printf("2 - listar usuários e seus ids\n");
        printf("3 - registrar novo usuário\n");
        printf("4 - apagar usuário\n");
        printf("5 - buscar usuário pelo nome (busca binária)\n");
        printf("0 - sair\n");
        printf("========================================\n");
        printf("escolha uma opção: ");
        scanf("%d", &option);
        clearBuffer();

        switch (option) {
            case 0:
                printf("saindo do programa...\n");
                break;
            case 1: {
                int id;
                printf("digite o id do usuário: ");
                scanf("%d", &id);
                clearBuffer();
                User* currentUser = getUserById(userList, id);
                if (currentUser) {
                    printf("usuário '%s' logado com sucesso.\n", currentUser->name);
                    userMenu(currentUser);
                } else {
                    printf("id não encontrado. tente novamente.\n");
                }
                break;
            }
            case 2:
                displayUserList(userList);
                break;
            case 3:
                userList = addUser(userList);
                break;
            case 4: 
                int key;
                printf("digite o id do usuário: ");
                scanf("%d", &key);
                userList = deleteUser(userList, key);
                break;
            case 5:
                char name[50];
                printf("digite o nome do usuário: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", name);
                User* aux = binarySearchUser(userList, name);
                if (aux == NULL) {
                    printf("usuaŕio não encontrado!\n");
                } else {
                    printf("usuário encontrado: \n");
                    displayUser(aux);
                }
                break;
            default:
                printf("opção inválida. tente de novo!\n");
        }
    } while (option != 0);
}

int main() {
    srand(time(NULL));
    User* userList = NULL;
    mainMenu(userList);
    return 0;
}
