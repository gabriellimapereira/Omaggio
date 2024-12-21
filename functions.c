#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

// funções de usuário
int checkUserId(User* userList, int id) { //verifica se o id já está sendo usado por algum usuário
    while (userList != NULL) {
        if (id == userList->id) return 0;
        userList = userList->next;
    }
    return 1;
}

int generateRandUserId(User* userList) { //gera um id randomizado
    while (1) {
        int id = rand() % 10001;
        if (checkUserId(userList, id)) return id;
    }
}

void clearBuffer() { //limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

User* setterUser(User* newUser, User* userList) { //captura os dados de usuário
    printf("digite o nome do novo usuário: ");
    fgets(newUser->name, sizeof(newUser->name), stdin);

    newUser->name[strcspn(newUser->name, "\n")] = '\0';   
    clearBuffer();

    newUser->id = generateRandUserId(userList);
    printf("seu id é: %d", newUser->id);
    clearBuffer();

    newUser->taskList = initializeTaskList();
    newUser->completedTasks = createCompletedTasks();
    newUser->doublyTaskList = createDoublyTaskList();
    newUser->pendingTasks = createPendingTasks();
    newUser->history = createUndoStack();

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
    User* newUser = aloccateUser();
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

int checkTaskId(TaskList* taskList, int id) { //verifica se o id já está sendo usado por alguma tarefa
    while (taskList != NULL) {
        if (id == taskList->task->id) return 0;
        taskList = taskList->next;
    }
    return 1;
}

int generateRandUserId(TaskList* taskList) { //gera um id de tarefa randomizado
    while (1) {
        int id = rand() % 10001;
        if (checkUserId(taskList, id)) return id;
    }
}

Task* setterTask(Task* newTask, TaskList* taskList) { //setter de tarefa
    printf("digite o nome da tarefa:\n");
    fgets(newTask->name, sizeof(newTask->name), stdin);
    newTask->name[strcspn(newTask->name, "\n")] = '\0';
    clearBuffer();

    printf("digite o prazo (dd/mm/aaaa):\n");
    fgets(newTask->deadline, sizeof(newTask->deadline), stdin);
    newTask->deadline[strcspn(newTask->deadline, "\n")] = '\0';
    clearBuffer();

    while (1) {
        printf("digite a prioridade da tarefa (1 a 5):\n");
        scanf("%d", &newTask->priority);
        if (newTask->priority >= 1 && newTask->priority <= 5) break;
        printf("prioridade inválida! digite um valor entre 1 e 5\n");
    }
    clearBuffer();

    while (1) {
        printf("digite o status da tarefa (0 para pendente, 1 para concluída):\n");
        scanf("%d", &newTask->status);
        if (newTask->status == 0 || newTask->status == 1) break;
        printf("status inválido! digite 0 ou 1\n");
    }
    clearBuffer();

    newTask->id = generateRandUserId(taskList);

    return newTask;
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
    Task* newTask = allocateTask();
    TaskList* newNode = allocateTaskNode();
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