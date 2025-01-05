#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "sort.h"

DoublyTaskList* sortList(DoublyTaskList* head) {
    int choice;

    printf("escolha um algoritmo de ordenacao:\n");
    printf("1. bubble sort\n");
    printf("2. selection sort\n");
    printf("3. insertion sort\n");
    printf("4. merge sort\n");
    printf("5. quick sort\n");
    printf("digite o número do algoritmo desejado: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("usando bubble sort...\n");
            bubbleSort(head);
            break;
        case 2:
            printf("usando selection sort...\n");
            selectionSort(head);
            break;
        case 3:
            printf("usando insertion sort...\n");
            insertionSort(&head);
            break;
        case 4:
            printf("usando merge sort...\n");
            head = mergeSort(head);
            break;
        case 5:
            printf("usando quick sort...\n");
            head = quickSort(head);
            break;
        default:
            printf("escolha invalida! nenhuma alteracao feita\n");
            break;
    }

    return head;
}

void userMenu(User* currentUser) {
    system("clear");
    int userOption;

    do {
        printf("\n=== menu do usuário ===\n");
        printf("0 - voltar ao menu principal\n");
        printf("1 - listar todas as tarefas\n");
        printf("2 - inserir nova tarefa\n");
        printf("3 - concluir uma tarefa (função ainda não implementada)\n");
        printf("4 - apagar registro de tarefa (função ainda não implementada)\n");
        printf("5 - procurar tarefa (função ainda não implementada)\n");
        printf("6 - ordenar lista de tarefas:\n");
        printf("7 - listar tarefas pendentes\n");
        printf("8 - listar tarefas concluídas\n");
        printf("9 - reverter ato (função ainda não implementada).\n");
        printf("escolha uma opção: ");
        scanf("%d", &userOption);
        clearBuffer();

        switch (userOption) {
            case 0:
                printf("voltando ao menu principal...\n");
                break;
            case 1:
                printf("\nlistando todas as tarefas:\n");
                displayTaskListRecursive(currentUser->taskList);
                break;
            case 2:
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
            case 3:
                printf("\nconcluindo uma tarefa...\n");
                completeTask(currentUser->pendingTasks, currentUser->completedTasks);
                break;
            case 4:
                printf("\napagar registro de tarefa (função ainda não implementada).\n");
                break;
            case 5:
                printf("\ndigite o id da tarefa:\n");
                int key;
                scanf("%d", &key);
                clearBuffer();
                TaskList* aux = getTaskById(currentUser->taskList, key);
                if (aux) {
                    printTask(aux->task);
                } else {
                    printf("tarefa não encontrada.\n");
                }
                break;
            case 6:
                currentUser->doublyTaskList = sortList(currentUser->doublyTaskList);
                printf("lista ordenada!\nlista após a ordenação: ");
                displayDoublyTaskList(currentUser->doublyTaskList);
                break;
            case 7:
                printf("\nlistando tarefas pendentes:\n");
                displayPendingTasks(currentUser->pendingTasks);
                break;
            case 8:
                printf("\nlistando tarefas concluídas:\n");
                displayCompletedTasks(currentUser->completedTasks);
                break;
            case 9:
                printf("\nreverter ato (função ainda não implementada).\n");
                break;
            default:
                printf("\nopção inválida. tente novamente.\n");
        }

    } while (userOption != 0);
}

void mainMenu(User* userList) {
    int option;
    User* currentUser = NULL;

    do {
        printf("\n=== menu principal ===\n");
        printf("0 - sair\n");
        printf("1 - logar como usuário\n");
        printf("2 - listar usuários e seus ids\n");
        printf("3 - registrar novo usuário\n");
        printf("4 - apagar usuário (função ainda não implementada)\n");
        printf("5 - buscar um usuário (busca binária)\n");
        printf("escolha uma opção: ");
        scanf("%d", &option);
        clearBuffer();

        switch (option) {
            case 0:
                printf("saindo do programa...\n");
                break;
            case 1:
                    int id;
                    printf("digite o id do usuário: ");
                    scanf("%d", &id);
                    clearBuffer();
                    currentUser = getUserById(userList, id);
                    if (currentUser) {
                        printf("usuário '%s' logado com sucesso.\n", currentUser->name);
                        userMenu(currentUser);
                    } else {
                        printf("id não encontrado. tente novamente.\n");
                    }
                break;
            case 2:
                printf("\nlistando usuários e ids:\n");
                displayUserList(userList);
                break;
            case 3:
                userList = addUser(userList);
                break;
            case 4:
                printf("\napagar usuário (função ainda não implementada).\n");
                break;
            case 5:
                char name[50];
                printf("digite o nome do usuário: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", name);
                User* aux = binarySearchUser(userList, name);
                printf("usuário encontrado: \n");
                displayUser(aux);
                break;
            default:
                printf("\nopção inválida. tente novamente.\n");
        }
    } while (option != 0);
}

int main() {
    srand(time(NULL));
    User* userList = NULL;
    mainMenu(userList);
    return 0;
}