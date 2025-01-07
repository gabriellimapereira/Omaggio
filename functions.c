#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

// funções utilitárias
void clearBuffer() { //limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// funções de usuário
int checkUserId(User* userList, int id) { //verifica se o id já está sendo usado por algum usuário
    while (userList != NULL) {
        if (id == userList->id) return 0;
        userList = userList->next;
    }
    return 1;
}

int generateRandUserId(User* userList) { //gera um id randomizado
    int id;
    do {
        id = rand() % 10001;
    } while (!checkUserId(userList, id));
    return id;
}

User* setterUser(User* newUser, User* userList) { // captura as informações de usuário
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

User* allocateUser() { // aloca a memória para o usuário
    User* newUser = (User*) malloc(sizeof(User));
    if (newUser == NULL) {
        printf("erro ao alocar memória para usuário!\n");
        exit(1);
    } else {
        return newUser;
    }
}

User* initializeUserList() { // inicializa a lista
    return NULL;
}

User* getUserById(User* userList, int key) { // procura o usuário na lista
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

User* getLastUser(User* userList) { // acha o final da lista
    if (userList == NULL || userList->next == NULL) return userList;

    User* aux = userList;
    while (aux->next != NULL) aux = aux->next;
    return aux;
}

User* addUser(User* userList) { // insere usuário
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

void displayUserList(User* userList) { // exibe a lista
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

void displayUser(User* user) { // exibe uuário
    printf("usuário: %s\nid: %d\n\n", user->name, user->id);
}

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
Task* allocateTask() { // aloca a tarefa
    Task* newTask = (Task*) malloc(sizeof(Task));
    if (newTask == NULL) {
        printf("erro ao alocar memória!\n");
        exit(1);
    } else {
        return newTask;
    }
}

int checkTaskId(TaskList* taskList, int id) { // verifica se o id é valido
    while (taskList != NULL) {
        if (id == taskList->task->id) return 0;
        taskList = taskList->next;
    }
    return 1;
}

int generateRandTaskId(TaskList* taskList) { // gera um id de tarefa aleatório
    int id;
    do {
        id = rand() % 10001;
    } while (!checkTaskId(taskList, id));
    return id;
}

Task* setterTask(Task* newTask, TaskList* taskList) { // captura as informações de usuário
    printf("digite o nome da tarefa:\n");
    setbuf(stdin, NULL);
    scanf("%[^\n]", newTask->name);

    printf("escreva uma breve descrição da tarefa:\n");
    setbuf(stdin, NULL);
    scanf("%[^\n]", newTask->description);

    while (1) {
        printf("digite a prioridade da tarefa (1 a 5):\n");
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
TaskList* initializeTaskList() { // inicializa a lista de tarefas
    return NULL;
}

TaskList* allocateTaskNode() { // cria um nó de lista de tarefas
    TaskList* newNode = (TaskList*) malloc(sizeof(TaskList));
    if (newNode == NULL) {
        printf("erro ao alocar memória!\n");
        exit(1);
    } else {
        return newNode;
    }
}

TaskList* getTaskById(TaskList* taskList, int key) { // procura uma tarefa pelo id
    TaskList* aux = taskList;
    while (aux != NULL) {
        if (aux->task != NULL && aux->task->id == key) {
            return aux; 
        }
        aux = aux->next;
    }

    printf("tarefa não encontrada!\n");
    return NULL; // Retorna NULL se não encontrar
}

TaskList* getLastTaskNode(TaskList* taskList) { // retorna o último nó
    if (taskList == NULL) return NULL;

    TaskList* aux = taskList;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    return aux; 
}

TaskList* addTaskToList(Task* newTask, TaskList* taskList) { // adiciona tarefa à lista
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

void displayTaskListRecursive(TaskList* taskList) { // exibe a lista recursivamente
    if (taskList == NULL) {
        printf("lista vazia!\n");
        return;
    }

    if (taskList->task == NULL) {
        printf("lista vazia!\n");
        return;
    }
    
    printTask(taskList->task);

    displayTaskListRecursive(taskList->next);
}

void freeTaskList(TaskList* taskList) {
    while (taskList != NULL) {
        TaskList* next = taskList->next;
        free(taskList->task); 
        free(taskList);
        taskList = next; 
    }
    printf("free da lista normal ok\n");
}

//funções da lista de tarefas duplamente encadeada
DoublyTaskList* initializeDoublyTaskList() { // inicializa a lista dupla de tarefas
    return NULL;
}

DoublyTaskList* allocateTaskNode_D() { // cria um nó de lista de tarefas
    DoublyTaskList* newNode = (DoublyTaskList*) malloc(sizeof(DoublyTaskList));
    if (newNode == NULL) {
        printf("erro ao alocar memória!\n");
        exit(1);
    } else {
        return newNode;
    }
}

DoublyTaskList* getLastTaskNode_D(DoublyTaskList* taskList) { // encontra o final da lista dupla
    if (taskList == NULL || taskList->next == NULL) return taskList;

    DoublyTaskList* aux = taskList;
    while (aux->next != NULL) aux = aux->next;
    return aux;
}

DoublyTaskList* addTaskToList_D(Task* newTask, DoublyTaskList* taskList) { // insere a tarefa na lista dupla
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

void displayDoublyTaskList(DoublyTaskList* taskList) { // exibe a lista de tarefas dupla
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

void freeDoublyTaskList(DoublyTaskList* doublyTaskList) {
    while (doublyTaskList != NULL) {
        DoublyTaskList* next = doublyTaskList->next;
        free(doublyTaskList);
        doublyTaskList = next; 
    }

    printf("free da dupla ok\n");
}

//funções da lista de concluídas
CompletedTasks* initializeCompletedTasks() { // função clichẽ de inicialização
    return NULL;
}

CompletedTasks* allocateCircularNode() { // aloca o nó da circular
    CompletedTasks* newNode = (CompletedTasks*)malloc(sizeof(CompletedTasks));
    if (newNode == NULL) {
        printf("erro ao alocar memória para a nova tarefa.\n");
        exit(1);
    }
    newNode->task = NULL;
    newNode->next = NULL;
    newNode->quant = 0;
    return newNode;
}

CompletedTasks* addTaskToCircularList(Task* newTask, CompletedTasks* completedTasks) { // função para adicionar uma tarefa à lista circular de tarefas concluídas
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

void displayCompletedTasks(CompletedTasks* completedTasks) { // exibe as tarefas cumpridas
    if (completedTasks == NULL) {
        printf("\nNenhuma tarefa concluída.\n");
        return;
    }

    CompletedTasks* aux = completedTasks;
    printf("\n=== tarefas concluídas ===\n");
    
    do {
        printTask(aux->task);
        aux = aux->next;
    } while (aux != completedTasks); 
}

void freeCompletedTasks(CompletedTasks* completedTasks) { // free da lista de tarefas completas
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

//funções da lista de pendentes
PendingTasks* initializePendingTasks() { // preciso comentar?
    return NULL;
}

PendingTasks* allocatePendingTasks() { // aloca a fila de tarefas
    PendingTasks* newPendingTasks = (PendingTasks*)malloc(sizeof(PendingTasks));
    if (newPendingTasks == NULL) {
        printf("Erro ao alocar memória para a lista de tarefas pendentes.\n");
        exit(1);
    }
    newPendingTasks->first = NULL;
    newPendingTasks->last = NULL;
    return newPendingTasks;
}

void insertTaskIntoPendingList(PendingTasks* pendingTasks, Task* newTask) { // inserção na lista de tarefass
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

void displayPendingTasks(PendingTasks* pendingTasks) { // listagem da fila de pendẽncias
    if (pendingTasks == NULL || pendingTasks->first == NULL) {
        printf("\nnão há tarefas pendentes para listar.\n");
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

void completeTask(PendingTasks* pendingTasks, CompletedTasks* completedTasks) { // "completa" uma tarefa
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

void freePendingTasks(PendingTasks* pendingTasks) { // free da fila de pendentes
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

//funções da pilha de reversão
UndoStack* initializeUndoStack() { // inicializa a pilha de reversão
    return NULL;
}

//busca binária
int size(User* list) { // retorna o tamanho da lista
    int count = 0;
    User* aux = list;
    while (aux != NULL) {
        count++;
        aux = aux->next;
    }
    return count;
}

User* getUserAtIndex(User* list, int index) {
    User* aux = list;
    int count = 0;
    while (aux != NULL && count < index) {
        aux = aux->next;
        count++; 
    }
    return aux; 
}

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