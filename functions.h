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
User* allocateUser();
User* bootUserList();
User* findUser(User* userList, int Id);
User* findEnd(User* userList);
User* insertUser(User* userList);
User* deleteUser(User* userList, int Id);
void printUserList(User* userList);

//funções de tarefas
Task* allocateTask();

//funções de lista de listas encadeadas
TaskList* bootTaskList();
TaskList* allocateListNode();
TaskList* findTask(TaskList* TaskList, int taskId);
TaskList* findEndList(TaskList* userList);
TaskList* insertTask(TaskList* userList, int newId);
void printTasks(TaskList* taskList);

#endif