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
    scanf("%d", &newUser->name);

    newUser->id = generateRandUserId(userList);
    printf("seu id é: %d\n", newUser->id);

    newUser->taskList = initializeTaskList();
    newUser->completedTasks = NULL;
    newUser->doublyTaskList = NULL;
    newUser->pendingTasks = initializePendingTasks();
    newUser->history = NULL;

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

User* removeUserById(User* userList, int key) { // deleta o usuário
    if (userList == NULL) {
        printf("lista vazia!\n");
        return NULL;
    }

    User* temp = getUserById(userList, key);
    if (temp == NULL) return userList;

    if (temp == userList) {
        if (userList->next == NULL) {
            free(temp);
            return NULL;
        }
        userList = userList->next;
        userList->prev = NULL;
        free(temp);
    } else if (temp->next == NULL) {
        temp->prev->next = NULL;
        free(temp);
    } else {
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        free(temp);
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
        printf("usuário: fulano\nid: %d\n\n", aux->id);
        aux = aux->next;
    }
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
    scanf("%d", &newTask->name);

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
    printf("nome: %d\n", task->name);
    printf("prioridade: %d\n", task->priority);
    printf("status: %d\n", task->status);
}

// funções das listas de tarefas
TaskList* initializeTaskList() { 
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

void displayTaskList(TaskList* taskList) { // exibe a lista de tarefas
    if (taskList == NULL) {
        printf("não há tarefas na lista\n");
        return;
    }

    TaskList* aux = taskList;
    printf("ids das tarefas:\n");
    while (aux != NULL) {
        if (aux->task != NULL) {
            printf("id: %d\n", aux->task->id);
        }
        aux = aux->next;
    }
}

TaskList* removeTaskFromList(TaskList* taskList, int key) { // remove uma tarefa da lista
    if (taskList == NULL) {
        printf("a lista está vazia!\n");
        return NULL;
    }

    TaskList* prev = NULL;
    TaskList* current = taskList;

    while (current != NULL && current->task->id != key) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Tarefa com id %d não encontrada.\n", key);
        return taskList;
    }

    if (prev == NULL) {
        TaskList* temp = current->next;
        free(current->task);
        free(current);
        return temp;
    }

    prev->next = current->next;
    free(current->task);
    free(current);
    return taskList;
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

    printf("id: %d\n", taskList->task->id);
    printf("nome: %d\n", taskList->task->name);
    printf("prioridade: %d\n", taskList->task->priority);
    printf("status: %s\n\n", taskList->task->status == 0 ? "pendente" : "concluída");

    displayTaskListRecursive(taskList->next);
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

void listCompletedTasks(CompletedTasks* completedTasks) { // exibe as tarefas cumpridas
    if (completedTasks == NULL) {
        printf("\nNenhuma tarefa concluída.\n");
        return;
    }

    CompletedTasks* current = completedTasks;
    printf("\n=== Tarefas Concluídas ===\n");
    
    do {
        printTask(current->task);
        current = current->next;
    } while (current != completedTasks); 
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
    if (pendingTasks == NULL) {
        printf("Erro: A lista de tarefas pendentes não foi inicializada.\n");
        return;
    }

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

void listPendingTasks(PendingTasks* pendingTasks) { // listagem da fila de pendẽncias
    if (pendingTasks == NULL || pendingTasks->first == NULL) {
        printf("\nNão há tarefas pendentes para listar.\n");
        return;
    }

    TaskList* current = pendingTasks->first;
    printf("\nTarefas pendentes:\n");

    while (current != NULL) {
        printf("ID: %d\n", current->task->id);
        printf("Nome: %d\n", current->task->name);
        printf("Prioridade: %d\n", current->task->priority);
        printf("Status: %s\n", current->task->status == 0 ? "Pendente" : "Concluída");
        printf("\n");

        current = current->next;
    }
}

void completeTask(PendingTasks* pendingTasks, CompletedTasks* completedTasks) { // "completa" uma tarefa
    if (pendingTasks == NULL || pendingTasks->first == NULL) {
        printf("\nNenhuma tarefa pendente para concluir.\n");
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

//funções da pilha de reversão
UndoStack* initializeUndoStack() { // inicializa a pilha de reversão
    return NULL;
}