#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

// funções de usuário
int generateRandId() { //gera um id randomizado
    srand(time(NULL));
    int id = rand();
    return id;
}

void clearBuffer() { //limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

User* setterUser(User* newUser) { //captura os dados de usuário
    printf("digite o nome do novo usuário: ");
    fgets(newUser->name, sizeof(newUser->name), stdin);

    newUser->name[strcspn(newUser->name, "\n")] = '\0';   
    clearBuffer();

    newUser->id = generateRandId();
    printf("seu id é: %d", newUser->id);

    newUser->taskList = initializeTaskList();
    newUser->completedTasks = createCompletedTasks();
    newUser->doublyTaskList = createDoublyTaskList();
    newUser->pendingTasks = createPendingTasks();
    newUser->history = createUndoStack();

    return newUser;
}

User* createUser() { // aloca a memória para o usuário
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
    User* newUser = createUser();
    newUser = setterUser(newUser);

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

Task* createTask() { // aloca a tarefa
    Task* newTask = (Task*) malloc(sizeof(Task));
    if (newTask == NULL) {
        printf("erro ao alocar memória!\n");
        exit(1);
    } else {
        return newTask;
    }
}

// funções das listas de tarefas
TaskList* initializeTaskList() { // inicializa a lista de tarefas
    return NULL;
}

TaskList* createTaskNode() { // cria um nó de lista de tarefas
    TaskList* newNode = (TaskList*) malloc(sizeof(TaskList));
    if (newNode == NULL) {
        printf("erro ao alocar memória!\n");
        exit(1);
    } else {
        return newNode;
    }
}

TaskList* getTaskById(TaskList* taskList, int key) { // acha a tarefa
    if (taskList == NULL) {
        printf("sem tarefas no sistema!\n");
        return NULL;
    }

    TaskList* aux = taskList;
    while (aux != NULL) {
        if (aux->task->id == key) {
            return aux;
        }
        aux = aux->next;
    }

    printf("tarefa não encontrada!\n");
    return NULL;
}

TaskList* getLastTaskNode(TaskList* taskList) { // encontra o final da lista
    if (taskList == NULL || taskList->next == NULL) return taskList;

    TaskList* aux = taskList;
    while (aux->next != NULL) aux = aux->next;
    return aux;
}

TaskList* addTaskToList(TaskList* taskList) { // insere a tarefa na lista
    Task* newTask = createTask();
    TaskList* newNode = createTaskNode();
    newNode->task = newTask;

    if (taskList == NULL) {
        newNode->next = NULL;
        taskList = newNode;
    } else if (taskList->next == NULL) {
        taskList->next = newNode;
        newNode->next = NULL;
    } else {
        TaskList* aux = getLastTaskNode(taskList);
        aux->next = newNode;
        newNode->next = NULL;
    }

    return taskList;
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

//funções da lista de tarefas duplamente encadeada
DoublyTaskList* initializeDoublyTaskList() { // inicializa a lista dupla de tarefas
    return NULL;
}

//funções da lista de pendentes
PendingTasks* initializePendingTasks() { // inicializa a lista de pendentes
    return NULL;
}

//funções da pilha de reversão
UndoStack* initializeUndoStack() { // inicializa a pilha de reversão
    return NULL;
}