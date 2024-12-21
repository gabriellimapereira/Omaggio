#ifndef FUNCTIONS
#define FUNCTIONS

typedef struct Task {
    int id;
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

//funções de usuário
int checkUserId(User* userList, int id);
int generateRandUserId(User* userList);
void clearBuffer();
User* setterUser(User* newUser, User* userList);
User* allocateUser();
User* initializeUserList();
User* getUserById(User* userList, int id);
User* getLastUser(User* userList);
User* addUser(User* userList);
User* removeUserById(User* userList, int id);
void displayUserList(User* userList);

// funções de tarefas
Task* allocateTask();

// funções de lista encadeada
TaskList* initializeTaskList();
TaskList* allocateTaskNode();
TaskList* getTaskById(TaskList* taskList, int key);
TaskList* getLastTaskNode(TaskList* taskList);
TaskList* addTaskToList(TaskList* taskList);
void displayTaskList(TaskList* taskList);

//funções da lista de tarefas duplamente encadeada
DoublyTaskList* initializeDoublyTaskList();

//funções da lista de pendentes
PendingTasks* initializePendingTasks();

//funções da pilha de reversão
UndoStack* initializeUndoStack();

#endif