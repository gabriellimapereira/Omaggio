#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void testUserMenu() {
    User* userList = initializeUserList();
    User* currentUser = NULL;

    printf("\n=== teste do menu principal ===\n");

    printf("\n[teste 1] cadastrando um novo usuário...\n");
    userList = addUser(userList);
    printf("usuário cadastrado com sucesso!\n");

    printf("\n[teste 2] listando usuários...\n");
    displayUserList(userList);

    printf("\n[teste 3] selecionando o usuário cadastrado...\n");
    currentUser = getUserById(userList, userList->id);
    if (currentUser) {
        printf("usuário '%s' selecionado com sucesso!\n", currentUser->name);
    } else {
        printf("falha ao selecionar usuário.\n");
    }

    printf("\n[teste 4] removendo o usuário...\n");
    userList = removeUserById(userList, userList->id);
    printf("usuário removido com sucesso!\n");

    printf("\n[teste 5] verificando lista de usuários...\n");
    displayUserList(userList);
}

void testTaskMenu() {
    printf("\n=== teste do menu de tarefas ===\n");

    User* testUser = malloc(sizeof(User));
    strcpy(testUser->name, "usuário teste");
    testUser->id = 1234;
    testUser->taskList = initializeTaskList();

    printf("\n[teste 1] adicionando uma nova tarefa...\n");
    Task* newTask1 = allocateTask();
    newTask1->id = 5678;
    strcpy(newTask1->name, "tarefa 1");
    strcpy(newTask1->description, "descrição da tarefa 1");
    strcpy(newTask1->deadline, "30/12/2024");
    newTask1->priority = 3;
    newTask1->status = 0;
    testUser->taskList = addTaskToList(newTask1, testUser->taskList);
    printf("tarefa 1 adicionada com sucesso!\n");

    printf("\n[teste 2] adicionando outra tarefa...\n");
    Task* newTask2 = allocateTask();
    newTask2->id = 5679;
    strcpy(newTask2->name, "tarefa 2");
    strcpy(newTask2->description, "descrição da tarefa 2");
    strcpy(newTask2->deadline, "05/01/2025");
    newTask2->priority = 1;
    newTask2->status = 0;
    testUser->taskList = addTaskToList(newTask2, testUser->taskList);
    printf("tarefa 2 adicionada com sucesso!\n");

    printf("\n[teste 3] listando tarefas do usuário...\n");
    displayTaskListRecursive(testUser->taskList);

    printf("\n[teste 4] removendo a tarefa 1...\n");
    testUser->taskList = removeTaskFromList(testUser->taskList, newTask1->id);
    printf("tarefa 1 removida com sucesso!\n");

    printf("\n[teste 5] verificando lista de tarefas após remoção...\n");
    displayTaskListRecursive(testUser->taskList);

    printf("\n[teste 6] alterando o status da tarefa 2 para concluída...\n");
    newTask2->status = 1;
    printf("tarefa 2 status alterado para concluída.\n");

    printf("\n[teste 7] listando tarefas após alteração de status...\n");
    displayTaskListRecursive(testUser->taskList);

    printf("\n[teste 8] removendo a tarefa 2...\n");
    testUser->taskList = removeTaskFromList(testUser->taskList, newTask2->id);
    printf("tarefa 2 removida com sucesso!\n");

    printf("\n[teste 9] verificando lista de tarefas após remoção final...\n");
    displayTaskListRecursive(testUser->taskList);

    free(testUser);
}

int main() {
    printf("\n=== iniciando script de teste ===\n");

    testUserMenu();

    testTaskMenu();

    printf("\n=== fim do script de teste ===\n");
    return 0;
}
