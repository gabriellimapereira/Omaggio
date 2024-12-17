#ifndef FUNCTIONS
#define FUNCTIONS

typedef struct Task {
    char name[50];
    char deadline[10];
    int priority;
} Task;

typedef struct TaskList { //lista encadeada
    struct Task* task;
    struct Task* next;
} TaskList;

typedef struct CompletedTasks { //lista encadeada-circular
    struct Task* task;
    struct Task* next;
} CompletedTasks;

typedef struct DoublyTaskList { //lista duplamente-encadeada
    struct Task* task;
    struct Task* next;
    struct Task* prev;
} DoublyTaskList;

typedef struct PendingTasks { //tarefas pendentes
    struct Task* first;
    struct Task* last;
} PendingTasks;

typedef struct UndoStack { //pilha para reverter ações
    struct User* top;
} UndoStack;

typedef struct User {
    char name[50];
    int id;
    struct User* next;
    struct User* prev;
    struct TaskList* taskList;
    struct CompletedTasks* completedTasks;
    struct DoublyTaskList* doublyTaskList;
    struct PendingTasks* pendingTasks;
    struct UndoStack* history;
} User;

User* allocateUser(int newId);
User* findUser(User* userList, int Id);
User* findEnd(User* userList);
User* insertUser(User* userList, int newId);
User* deleteUser(User* userList, int Id);
void printUserList(User* userList);

#endif