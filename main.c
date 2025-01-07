#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "sort.h"

// exibe o menu para escolha do algoritmo de ordenação e aplica o algoritmo escolhido
// recebe a cabeça da lista de tarefas (DoublyTaskList*)
// retorna a cabeça da lista de tarefas ordenada (DoublyTaskList*)
DoublyTaskList* sortList(DoublyTaskList* head) { 
    int choice;

    printf("\n--- escolha um algoritmo de ordenação ---\n");
    printf("1. bubble sort\n");
    printf("2. selection sort\n");
    printf("3. insertion sort\n");
    printf("4. merge sort\n");
    printf("5. quick sort\n");
    printf("-----------------------------------------\n");
    printf("digite o número do método desejado: ");
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
            printf("escolha inválida! nenhuma alteração foi feita. escolha algum válido! :/\n");
            break;
    }

    return head;
}

// exibe o menu de manipulação das tarefas do usuário
// recebe o usuário atual (User*) como parâmetro
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
        printf("7 - buscar tarefa pelo nome (busca binária)\n");
        printf("0 - voltar ao menu principal\n");
        printf("=========================================\n");
        printf("escolha uma opção: ");
        scanf("%d", &userOption);
        clearBuffer();

        switch (userOption) {
            case 0:
                break;
            case 1: //exibir lista de forma recursiva
                if (currentUser->taskList == NULL) {
                    printf("lista vazia!\n");
                } else {
                    displayTaskListRecursive(currentUser->taskList);
                }
                break;
            case 2: // inserir nova tarefa
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
            case 3: // ordenar a lista duplamente encadeada
                printf("lista antes da ordenação: \n");
                displayDoublyTaskList(currentUser->doublyTaskList);
                currentUser->doublyTaskList = sortList(currentUser->doublyTaskList);
                printf("lista ordenada! lista após a ordenação:\n");
                displayDoublyTaskList(currentUser->doublyTaskList);
                break;
            case 4: // exibir fila de tarefas pendentes
                displayPendingTasks(currentUser->pendingTasks);
                break;
            case 5: // exibir lista de tarefas completas
                displayCompletedTasks(currentUser->completedTasks);
                break;
            case 6: // completar tarefa
                completeTask(currentUser->pendingTasks, currentUser->completedTasks);
                break;
            case 7:
            char name[50];
                printf("digite o nome do tarefa: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", name);
                DoublyTaskList* aux = binarySearchTask(currentUser->doublyTaskList, name);
                if (aux == NULL) {
                    printf("tarefa desaparecido! (não encontrada)\n");
                } else {
                    printf("tarefa encontrada: \n");
                    printTask(aux->task);
                }
                break;
            default:
                printf("opção inválida. tente novamente! (alguma válido, de preferẽncia)\n");
        }
    } while (userOption != 0);
}

// exibe o menu principal do programa, onde o usuário pode logar, registrar e manipular usuários
// recebe a lista de usuários (User*) como parâmetro
void mainMenu(User* userList) { 
    int option;

    do {
        printf("\n============ menu principal ============\n");
        printf("1 - logar como usuário\n");
        printf("2 - listar usuários e seus ids\n");
        printf("3 - registrar novo usuário\n");
        printf("4 - apagar usuário\n");
        printf("0 - sair\n");
        printf("========================================\n");
        printf("escolha uma opção: ");
        scanf("%d", &option);
        clearBuffer();

        switch (option) {
            case 0: // saída do programa
                printf("saindo do programa...\n");
                break;
            case 1:  // logar como usuário
                int id;
                printf("digite o id do usuário: ");
                scanf("%d", &id);
                clearBuffer();
                User* currentUser = getUserById(userList, id);
                if (currentUser) {
                    printf("usuário '%s' logado com sucesso\n", currentUser->name);
                    userMenu(currentUser);
                } else {
                    printf("usuário finado (id não encontrado). tente novamente!\n");
                }
                break;
            case 2: // exibe a lista de usuários
                displayUserList(userList);
                break;
            case 3:
                // adiciona novo usuário
                userList = addUser(userList);
                break;
            case 4: // deleta um usuário
                int key;
                printf("digite o id do usuário: ");
                scanf("%d", &key);
                userList = deleteUser(userList, key);
                break;
            default:
                printf("opção inválida. tente de novo!\n");
        }
    } while (option != 0);
}

// main
int main() {
    srand(time(NULL)); // geração da semente para randomização
    User* userList = initializeUserList(); // inicialização da lsita de usuário
    mainMenu(userList); // chama o menu principal (agora é só ser feliz)
    return 0;
}
