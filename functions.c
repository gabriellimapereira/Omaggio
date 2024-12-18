#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

//funções de usuários
User* allocateUser() { //aloca a memória para o usuário
    User* newUser = (User*) malloc (sizeof(User));
    if (newUser == NULL) {
        printf("erro ao alocar memória para usuário!\n");
        exit(1);
    } else {
        return newUser;
    }
}

User* bootUserList() { //inicializa a lista
    return NULL;
}

User* findUser(User* userList, int Id) { //caça o usuário na lista
    if (userList == NULL) {
        printf("sem usuários no sistema!\n");
        return NULL;
    }

    User* aux = userList;
    while (aux != NULL) {
        if (aux->id == Id) {
            return aux;
        }
        aux = aux->next;
    }

    printf("usuário não encontrado!\n");
    return NULL;
}

User* findEnd(User* userList) { //acha o final da lista
    if (userList == NULL || userList->next == NULL) return userList;

    User* aux = userList;
    while (aux->next != NULL) aux = aux->next;
    return aux;
}

User* insertUser(User* userList) { //insere usuário
    User* newUser = allocateUser();
    
    if (userList == NULL) {
        newUser->next = NULL;
        newUser->prev = NULL;
        userList = newUser;
    } else if (userList->next == NULL) {
        userList->next = newUser;
        newUser->prev = userList;
        newUser->next = NULL;
    } else {
        User* aux = findEnd(userList);
        aux->next = newUser;
        newUser->prev = aux;
        newUser->next = NULL;
    }

    return userList;
}

User* deleteUser(User* userList, int Id) { //deleta o usuário
    if (userList == NULL) {
        printf("lista vazia!\n");
        return NULL;
    }

    User* temp = findUser(userList, Id);
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
        temp->next->prev = temp ->prev;
        temp->prev->next = temp->next;
        free(temp);
    }

    return userList;
}

void printUserList(User* userList) { //exibe a lista
    if (userList == NULL) {
        printf("sem usuários cadastrados!\n");
        return;
    }

    User* aux = userList;
    while (aux != NULL) {
        printf("usuario: fulano\nid: %d\n\n", aux->id);
        aux = aux->next;
    }
}

//funções de tarefas

Task* allocateTask() { //aloca a tarefa
    Task* newTask = (Task*) malloc (sizeof(Task));
    if (newTask == NULL) {
        printf("erro ao alocar memória!\n");
        exit(1);
    } else {
        return newTask;
    }
}

//funções das listas de tarefas

TaskList* bootTaskList() { //inicializa a lista de tarefas
    return NULL;
}

TaskList* allocateListNode() {
    TaskList* newNode = (TaskList*) malloc (sizeof(TaskList));
    if (newNode == NULL) {
        printf("erro ao alocar memória!\n");
        exit(1);
    } else {
        return newNode;
    }
}

TaskList* findTask(TaskList* taskList, int taskId) { //achar tarefa
    if (taskList == NULL) {
        printf("sem tarefas no sistema!\n");
        return NULL;
    }

    TaskList* aux = taskList;
    while (aux != NULL) {
        if (aux->task->id == taskId) {
            return aux;
        }
        aux = aux->next;
    }

    printf("tarefa não encontrada!\n");
    return NULL;
}

TaskList* findEndList(TaskList* taskList) { //encontra final da lista
    if (taskList == NULL || taskList->next == NULL) return taskList;

    TaskList* aux = taskList;
    while (aux->next != NULL) aux = aux->next;
    return aux;
}

TaskList* insertTask(TaskList* taskList) { //inserir tarefa
    Task* newTask = allocateTask();
    TaskList* newNode = allocateNode();
    newNode->task = newTask;
    
    if (taskList == NULL) {
        newNode->next = NULL;
        taskList = newTask;
    } else if (taskList->next == NULL) {
        taskList->next = newTask;
        newNode->next = NULL;
    } else {
        TaskList* aux = findEndList(taskList);
        aux->next = newTask;
        newNode->next = NULL;
    }

    return taskList;
}

#include <stdio.h>

void printTasks(TaskList* taskList) {
    if (taskList == NULL) {
        printf("não há tarefas na lista\n");
        return;
    }

    TaskList* aux = taskList;
    printf("IDs das tarefas:\n");
    while (aux != NULL) {
        if (aux->task != NULL) { 
            printf("ID: %d\n", aux->task->id);
        }
        aux = aux->next;
    }
}
