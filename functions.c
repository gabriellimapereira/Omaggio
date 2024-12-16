#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

User* allocateUser(int newId) { //aloca a memória para o usuário
    User* newUser = (User*) malloc (sizeof(User));
    if (newUser == NULL) {
        printf("erro ao alocar memória para usuário!\n");
        exit(1);
    } else {
        newUser->id = newId;
        return newUser;
    }
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

User* insertUser(User* userList, int newId) { //insere usuário
    User* newUser = allocateUser(newId);
    
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

void printUserList(User* userList) {
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