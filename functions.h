#ifndef FUNCTIONS
#define FUNCTIONS

typedef struct User {
    int id;
    struct User* next;
    struct User* prev;
} User;

User* allocateUser(int newId);
User* findUser(User* userList, int Id);
User* findEnd(User* userList);
User* insertUser(User* userList, int newId);
User* deleteUser(User* userList, int Id);
void printUserList(User* userList);

#endif