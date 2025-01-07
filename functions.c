#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

// funções utilitárias

// limpa o buffer de entrada (stdin)
// não recebe parâmetros e não retorna valor
void clearBuffer() {
    while (getchar() != '\n'); 
}

// funções de usuário

// verifica se o id já está sendo usado por algum usuário
// recebe um ponteiro para a lista de usuários (User*) e um id (int)
// retorna 0 se o id já estiver em uso, 1 caso contrário
int checkUserId(User* userList, int id) { 
    while (userList != NULL) {
        if (id == userList->id) return 0;
        userList = userList->next;
    }
    return 1;
}

// gera um id de usuário aleatório
// recebe um ponteiro para a lista de usuários (User*)
// retorna um id único (int)
int generateRandUserId(User* userList) { 
    int id;
    do {
        id = rand() % 10001;
    } while (!checkUserId(userList, id));
    return id;
}

// captura as informações de um novo usuário
// recebe o ponteiro para o novo usuário (User*) e para a lista de usuários (User*)
// retorna o ponteiro para o novo usuário com os valores configurados (User*)
User* setterUser(User* newUser, User* userList) { 
    printf("digite o nome do novo usuário: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", newUser->name);

    newUser->id = generateRandUserId(userList);
    printf("seu id é: %d\n", newUser->id);

    newUser->taskList = initializeTaskList();
    newUser->completedTasks = NULL;
    newUser->doublyTaskList = NULL;
    newUser->pendingTasks = initializePendingTasks();

    return newUser;
}

// aloca memória para um novo usuário
// não recebe parâmetros
// retorna o ponteiro para o novo usuário alocado (User*)
User* allocateUser() { 
    User* newUser = (User*) malloc(sizeof(User));
    if (newUser == NULL) {
        printf("erro ao alocar memória para usuário!\n");
        exit(1);
    } else {
        return newUser;
    }
}

// inicializa a lista de usuários
// não recebe parâmetros
// retorna um ponteiro nulo (User*)
User* initializeUserList() { 
    return NULL;
}

// procura um usuário na lista pelo id
// recebe a lista de usuários (User*) e a chave de busca (int)
// retorna o ponteiro para o usuário encontrado ou null se não encontrar (User*)
User* getUserById(User* userList, int key) { 
    if (userList == NULL) {
        printf("sem usuários no sistema!\n");
        return NULL;
    }

    User* aux = userList;
    while (aux != NULL) {
        if (aux->id == key) {
            return aux;
        }
        aux = aux->next;
    }

    printf("usuário não encontrado!\n");
    return NULL;
}

// obtém o último usuário da lista
// recebe a lista de usuários (User*)
// retorna o ponteiro para o último usuário da lista (User*)
User* getLastUser(User* userList) { 
    if (userList == NULL || userList->next == NULL) return userList;

    User* aux = userList;
    while (aux->next != NULL) aux = aux->next;
    return aux;
}

// insere um novo usuário na lista
// recebe a lista de usuários (User*)
// retorna a lista de usuários atualizada (User*)
User* addUser(User* userList) { 
    User* newUser = allocateUser();
    newUser = setterUser(newUser, userList);

    if (userList == NULL) {
        newUser->next = NULL;
        newUser->prev = NULL;
        userList = newUser;
    } else if (userList->next == NULL) {
        userList->next = newUser;
        newUser->prev = userList;
        newUser->next = NULL;
    } else {
        User* aux = getLastUser(userList);
        aux->next = newUser;
        newUser->prev = aux;
        newUser->next = NULL;
    }

    return userList;
}

// exibe a lista de usuários
// recebe um ponteiro para a lista de usuários (User*)
// não retorna valor
void displayUserList(User* userList) { 
    if (userList == NULL) {
        printf("sem usuários cadastrados!\n");
        return;
    }

    User* aux = userList;
    while (aux != NULL) {
        displayUser(aux);
        aux = aux->next;
    }
}

// exibe um usuário
// recebe um ponteiro para o usuário (User*)
// não retorna valor
void displayUser(User* user) {
    printf("usuário: %s\nid: %d\n\n", user->name, user->id);
}

// remove um usuário da lista pelo id
// recebe a lista de usuários (User*) e o id (int)
// retorna a lista de usuários atualizada (User*)
User* deleteUser(User* userList, int key) {
    if (userList == NULL) {
        printf("lista vazia!\n");
        return NULL;
    }

    User* currentUser = userList;
    User* previousUser = NULL;

    while (currentUser != NULL) {
        if (currentUser->id == key) {
            if (previousUser == NULL) {
                userList = currentUser->next; 
            } else {
                previousUser->next = currentUser->next; 
            }

            freeTaskList(currentUser->taskList);
            freePendingTasks(currentUser->pendingTasks);
            freeDoublyTaskList(currentUser->doublyTaskList);
            freeCompletedTasks(currentUser->completedTasks);
            free(currentUser); 

            return userList; 
        }

        previousUser  = currentUser ;
        currentUser  = currentUser ->next;
    }
    printf("id não encontrado!\n");
    return userList;
}

// funções de tarefas

// aloca uma nova tarefa
// não recebe parâmetros
// retorna um ponteiro para a nova tarefa (Task*)
Task* allocateTask() { // aloca a tarefa
    Task* newTask = (Task*) malloc(sizeof(Task));
    if (newTask == NULL) {
        printf("erro ao alocar memória para tarefa!\n");
        exit(1);
    } else {
        return newTask;
    }
}

// verifica se o id da tarefa é válido
// recebe a lista de tarefas (TaskList*) e o id (int)
// retorna 0 se o id já existir, 1 caso contrário
int checkTaskId(TaskList* taskList, int id) { 
    while (taskList != NULL) {
        if (id == taskList->task->id) return 0;
        taskList = taskList->next;
    }
    return 1;
}

// gera um id aleatório para a tarefa
// recebe a lista de tarefas (TaskList*)
// retorna um id único (int)
int generateRandTaskId(TaskList* taskList) { 
    int id;
    do {
        id = rand() % 10001;
    } while (!checkTaskId(taskList, id));
    return id;
}

// define as propriedades de uma nova tarefa
// recebe o ponteiro para a tarefa (Task*) e a lista de tarefas (TaskList*)
// retorna o ponteiro para a tarefa configurada (Task*)
Task* setterTask(Task* newTask, TaskList* taskList) {
    printf("digite o nome da tarefa:\n");
    setbuf(stdin, NULL);
    scanf("%[^\n]", newTask->name);

    printf("escreva uma breve descrição da tarefa:\n");
    setbuf(stdin, NULL);
    scanf("%[^\n]", newTask->description);

    while (1) {
        printf("digite a prioridade da tarefa (1 a 5, onde 1 é a menor prioridade e 5 a maior):\n");
        scanf("%d", &newTask->priority);
        if (newTask->priority >= 1 && newTask->priority <= 5) break;
        printf("prioridade inválida! digite um valor entre 1 e 5\n");
    }
  
    while (1) {
        printf("digite o status da tarefa (0 para pendente, 1 para concluída):\n");
        scanf("%d", &newTask->status);
        if (newTask->status == 0 || newTask->status == 1) break;
        printf("status inválido! digite 0 ou 1\n");
    }

    newTask->id = generateRandTaskId(taskList);

    return newTask;
}

// exibe os detalhes de uma tarefa
// recebe o ponteiro para a tarefa (Task*)
// não retorna valor
void printTask(Task* task) {
    if (task == NULL) {
        printf("tarefa inválida.\n");
        return;
    }

    printf("\n=== detalhes da tarefa ===\n");
    printf("ID: %d\n", task->id);
    printf("nome: %s\n", task->name);
    printf("descrição: %s\n", task->description);
    printf("prioridade: %d\n", task->priority);
    printf("status: %s\n\n", task->status == 0 ? "pendente" : "concluída");
}

// funções das listas de tarefas

// inicializa uma lista de tarefas
// não recebe parâmetros
// retorna um ponteiro nulo (TaskList*)
TaskList* initializeTaskList() { 
    return NULL;
}

// aloca um nó de lista de tarefas
// não recebe parâmetros
// retorna o ponteiro para o nó alocado (TaskList*)
TaskList* allocateTaskNode() { 
    TaskList* newNode = (TaskList*) malloc(sizeof(TaskList));
    if (newNode == NULL) {
        printf("erro ao alocar memória para a lista de tarefas!\n");
        exit(1);
    } else {
        return newNode;
    }
}

// busca uma tarefa pelo id na lista
// recebe a lista de tarefas (TaskList*) e o id (int)
// retorna o nó encontrado ou null (TaskList*)
TaskList* getTaskById(TaskList* taskList, int key) { 
    TaskList* aux = taskList;
    while (aux != NULL) {
        if (aux->task != NULL && aux->task->id == key) {
            return aux; 
        }
        aux = aux->next;
    }

    printf("tarefa não encontrada!\n");
    return NULL; 
}

// obtém o último nó de uma lista de tarefas
// recebe a lista de tarefas (TaskList*)
// retorna o ponteiro para o último nó (TaskList*)
TaskList* getLastTaskNode(TaskList* taskList) { 
    if (taskList == NULL) return NULL;

    TaskList* aux = taskList;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    return aux; 
}

// adiciona uma nova tarefa à lista
// recebe a tarefa (Task*) e a lista de tarefas (TaskList*)
// retorna a lista de tarefas atualizada (TaskList*)
TaskList* addTaskToList(Task* newTask, TaskList* taskList) { 
    TaskList* newNode = allocateTaskNode();
    newNode->task = newTask;

    if (taskList == NULL) {
        return newNode;
    } else {
        TaskList* lastNode = getLastTaskNode(taskList);
        lastNode->next = newNode;
        return taskList;
    }
}

// exibe a lista de tarefas recursivamente
// recebe a lista de tarefas (TaskList*)
// não retorna valor
void displayTaskListRecursive(TaskList* taskList) { 
    if (taskList == NULL) return;

    if (taskList->task == NULL) {
        printf("lista vazia!\n");
        return;
    }
    
    printTask(taskList->task);

    displayTaskListRecursive(taskList->next);
}

// libera memória da lista de tarefas
// recebe a lista de tarefas (TaskList*)
// não retorna valor
void freeTaskList(TaskList* taskList) {
    while (taskList != NULL) {
        TaskList* next = taskList->next;
        free(taskList->task); 
        free(taskList);
        taskList = next; 
    }
}

//funções da lista de tarefas duplamente encadeada

// inicializa uma lista duplamente encadeada de tarefas
// não recebe parâmetros
// retorna um ponteiro nulo (DoublyTaskList*)
DoublyTaskList* initializeDoublyTaskList() { 
    return NULL;
}

// aloca um nó para a lista duplamente encadeada de tarefas
// não recebe parâmetros
// retorna o ponteiro para o nó alocado (DoublyTaskList*)
DoublyTaskList* allocateTaskNode_D() { 
    DoublyTaskList* newNode = (DoublyTaskList*) malloc(sizeof(DoublyTaskList));
    if (newNode == NULL) {
        printf("erro ao alocar memória para o nó da lista de tarefa duplamente encadeada!\n");
        exit(1);
    } else {
        return newNode;
    }
}

// busca o último nó de uma lista duplamente encadeada
// recebe a lista de tarefas (DoublyTaskList*)
// retorna o ponteiro para o último nó (DoublyTaskList*)
DoublyTaskList* getLastTaskNode_D(DoublyTaskList* taskList) { 
    if (taskList == NULL || taskList->next == NULL) return taskList;

    DoublyTaskList* aux = taskList;
    while (aux->next != NULL) aux = aux->next;
    return aux;
}

// adiciona uma nova tarefa à lista duplamente encadeada
// recebe a tarefa (Task*) e a lista (DoublyTaskList*)
// retorna a lista de tarefas atualizada (DoublyTaskList*)
DoublyTaskList* addTaskToList_D(Task* newTask, DoublyTaskList* taskList) { 
    DoublyTaskList* newNode = allocateTaskNode_D();
    newNode->task = newTask;

    if (taskList == NULL) {
        newNode->prev = NULL;
        newNode->next = NULL;
        taskList = newNode;
    } else if (taskList->next == NULL) {
        taskList->next = newNode;
        newNode->prev = taskList;
        newNode->next = NULL;
    } else {
        DoublyTaskList* aux = getLastTaskNode_D(taskList);
        aux->next = newNode;
        newNode->prev = aux;
        newNode->next = NULL;
    }

    return taskList;
}

// exibe a lista de tarefas duplamente encadeada
// recebe a lista de tarefas (DoublyTaskList*)
// não retorna valor
void displayDoublyTaskList(DoublyTaskList* taskList) { 
    if (taskList == NULL) {
        printf("não há tarefas na lista\n");
        return;
    }

    DoublyTaskList* aux = taskList;
    printf("ids das tarefas:\n");
    while (aux != NULL) {
        if (aux->task != NULL) {
            printf("id: %d, nome: %s, prioridade: %d, status: %d\n", aux->task->id, aux->task->name, aux->task->priority, aux->task->status);
        }
        aux = aux->next;
    }
}

// libera memória da lista de tarefas duplamente encadeada
// recebe a lista de tarefas (DoublyTaskList*)
// não retorna valor
void freeDoublyTaskList(DoublyTaskList* doublyTaskList) {
    while (doublyTaskList != NULL) {
        DoublyTaskList* next = doublyTaskList->next;
        free(doublyTaskList);
        doublyTaskList = next; 
    }

    printf("free da dupla ok\n");
}

//funções da lista de concluídas

// inicializa a lista de tarefas concluídas
// não recebe parâmetros
// retorna um ponteiro nulo (CompletedTasks*)
CompletedTasks* initializeCompletedTasks() { 
    return NULL;
}

// aloca o nó da lista circular de tarefas concluídas
// não recebe parâmetros
// retorna o ponteiro para o nó alocado (CompletedTasks*)
CompletedTasks* allocateCircularNode() {
    CompletedTasks* newNode = (CompletedTasks*)malloc(sizeof(CompletedTasks));
    if (newNode == NULL) {
        printf("erro ao alocar memória para o nó da lista de tarefas completadas!\n");
        exit(1);
    }
    newNode->task = NULL;
    newNode->next = NULL;
    newNode->quant = 0;
    return newNode;
}

// adiciona uma nova tarefa à lista circular de tarefas concluídas
// recebe a tarefa (Task*) e a lista de tarefas concluídas (CompletedTasks*)
// retorna a lista de tarefas concluídas atualizada (CompletedTasks*)
CompletedTasks* addTaskToCircularList(Task* newTask, CompletedTasks* completedTasks) { 
    CompletedTasks* newNode = allocateCircularNode();
    newNode->task = newTask;

    if (completedTasks == NULL) {
        newNode->next = newNode; 
        newNode->quant = 1; 
        return newNode; 
    }

    CompletedTasks* temp = completedTasks;
    while (temp->next != completedTasks) {
        temp = temp->next; 
    }

    if (temp->quant == 10) {
        CompletedTasks* first = completedTasks;
        completedTasks = first->next; 
        temp->next = completedTasks; 
        free(first); 
        temp->quant--; 
    }

    temp->next = newNode;
    newNode->next = completedTasks; 
    temp->quant++;

    return completedTasks;
}

// exibe a lista de tarefas concluídas
// recebe a lista de tarefas concluídas (CompletedTasks*)
// não retorna valor
void displayCompletedTasks(CompletedTasks* completedTasks) { 
    if (completedTasks == NULL) {
        printf("\nnenhuma tarefa concluída!\n");
        return;
    }

    CompletedTasks* aux = completedTasks;
    printf("\n=== tarefas concluídas ===\n");
    
    do {
        printTask(aux->task);
        aux = aux->next;
    } while (aux != completedTasks); 
}

// libera memória da lista de tarefas concluídas
// recebe a lista de tarefas concluídas (CompletedTasks*)
// não retorna valor
void freeCompletedTasks(CompletedTasks* completedTasks) { 
    if (completedTasks == NULL) {
        return; 
    }

    CompletedTasks* aux = completedTasks;
    CompletedTasks* head = completedTasks;

    do {
        CompletedTasks* next = aux->next; 
        free(aux);
        aux = next; 
    } while (aux != head);

    free(head); 
}

// inicializa a lista de tarefas pendentes
// não recebe parâmetros
// retorna um ponteiro nulo (PendingTasks*)
PendingTasks* initializePendingTasks() { 
    return NULL;
}

// aloca a fila de tarefas pendentes
// não recebe parâmetros
// retorna o ponteiro para a fila alocada (PendingTasks*)
PendingTasks* allocatePendingTasks() { 
    PendingTasks* newPendingTasks = (PendingTasks*)malloc(sizeof(PendingTasks));
    if (newPendingTasks == NULL) {
        printf("erro ao alocar memória para a lista de tarefas pendentes!\n");
        exit(1);
    }
    newPendingTasks->first = NULL;
    newPendingTasks->last = NULL;
    return newPendingTasks;
}

// insere uma nova tarefa na fila de tarefas pendentes
// recebe a fila de tarefas pendentes (PendingTasks*) e a tarefa (Task*)
// não retorna valor
void insertTaskIntoPendingList(PendingTasks* pendingTasks, Task* newTask) { 
    TaskList* newNode = allocateTaskNode();
    newNode->task = newTask;

    if (pendingTasks->first == NULL) {
        pendingTasks->first = newNode;
        pendingTasks->last = newNode;
        newNode->next = NULL;
    } else {
        pendingTasks->last->next = newNode;
        pendingTasks->last = newNode;
        newNode->next = NULL;
    }
}

// exibe a lista de tarefas pendentes
// recebe a lista de tarefas pendentes (PendingTasks*)
// não retorna valor
void displayPendingTasks(PendingTasks* pendingTasks) { // listagem da fila de pendẽncias
    if (pendingTasks == NULL || pendingTasks->first == NULL) {
        printf("\nnão há tarefas pendentes para listar!\n");
        return;
    }

    TaskList* current = pendingTasks->first;
    printf("\ntarefas pendentes:\n");

    while (current != NULL) {
        printf("id: %d\n", current->task->id);
        printf("nome: %s\n", current->task->name);
        printf("prioridade: %d\n", current->task->priority);
        printf("status: %s\n", current->task->status == 0 ? "pendente" : "concluída");
        printf("\n");

        current = current->next;
    }
}

// completa uma tarefa da fila de pendentes e move para a lista de concluídas
// recebe a fila de tarefas pendentes (PendingTasks*) e de concluídas (CompletedTasks*)
// não retorna valor
void completeTask(PendingTasks* pendingTasks, CompletedTasks* completedTasks) { 
    if (pendingTasks == NULL || pendingTasks->first == NULL) {
        printf("\nnenhuma tarefa pendente para concluir!\n");
        return;
    }

    TaskList* taskToComplete = pendingTasks->first;
    pendingTasks->first = pendingTasks->first->next;
    if (pendingTasks->first == NULL) {
        pendingTasks->last = NULL;
    }

    taskToComplete->task->status = 1; // status 1 significa concluída

    completedTasks = addTaskToCircularList(taskToComplete->task, completedTasks);

    free(taskToComplete);
}

// libera memória da fila de tarefas pendentes
// recebe a fila de tarefas pendentes (PendingTasks*)
// não retorna valor
void freePendingTasks(PendingTasks* pendingTasks) { 
    if (pendingTasks == NULL) {
        return;
    }

    TaskList* aux = pendingTasks->first;

    while (aux != NULL) {
        TaskList* next = aux->next;
        free(aux); 
        aux = next; 
    }
}

// retorna o tamanho da lista de usuários
// recebe a lista de usuários (User*)
// retorna o tamanho (int)
int size(User* list) { 
    int count = 0;
    User* aux = list;
    while (aux != NULL) {
        count++;
        aux = aux->next;
    }
    return count;
}

// retorna o usuário no índice especificado da lista
// recebe a lista de usuários (User*) e o índice (int)
// retorna o ponteiro para o usuário (User*)
User* getUserAtIndex(User* list, int index) {
    User* aux = list;
    int count = 0;
    while (aux != NULL && count < index) {
        aux = aux->next;
        count++; 
    }
    return aux; 
}

// realiza a busca binária por nome na lista de usuários
// recebe a lista de usuários (User*) e o nome alvo (const char*)
// retorna o ponteiro para o usuário encontrado (User*) ou NULL
User* binarySearchUser (User* list, const char* targetName) { // a grande busca binária
    int left = 1;
    int right = size(list);

    while (left <= right) {
        int mid = left + (right - left) / 2;
        User* midNode = getUserAtIndex(list, mid);

        if (midNode == NULL) {
            return NULL; 
        }

        int comparison = strcmp(midNode->name, targetName);

        if (comparison == 0) {
            return midNode; 
        } else if (comparison < 0) {
            left = mid + 1; 
        } else {
            right = mid - 1; 
        }
    }

    return NULL; 
}