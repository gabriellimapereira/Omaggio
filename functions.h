#ifndef FUNCTIONS
#define FUNCTIONS

typedef struct Task {
    int id;
    char name[50];
    char deadline[10];
    char description[500];
    int priority;
    int status;
} Task;

typedef struct TaskList {
    Task* task;
    struct TaskList* next;
} TaskList;

typedef struct CompletedTasks {
    Task* task;
    struct CompletedTasks* next;
    int quant;
} CompletedTasks;

typedef struct DoublyTaskList {
    Task* task;
    struct DoublyTaskList* next;
    struct DoublyTaskList* prev;
} DoublyTaskList;

typedef struct PendingTasks {
    TaskList* first;
    TaskList* last;
} PendingTasks;

typedef struct UndoStack {
    struct User* top;
} UndoStack;

typedef struct User {
    char name[50];
    int id;
    struct User* next;
    struct User* prev;
    TaskList* taskList;
    CompletedTasks* completedTasks;
    DoublyTaskList* doublyTaskList;
    PendingTasks* pendingTasks;
    UndoStack* history;
} User;

// funções utilitárias
void clearBuffer();

//funções de usuário
int checkUserId(User* userList, int id);
int generateRandUserId(User* userList);
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
int checkTaskId(TaskList* taskList, int id);
int generateRandTaskId(TaskList* taskList);
Task* setterTask(TaskList* taskList);

// funções de lista encadeada
TaskList* initializeTaskList();
TaskList* allocateTaskNode();
TaskList* getTaskById(TaskList* taskList, int key);
TaskList* getLastTaskNode(TaskList* taskList);
TaskList* addTaskToList(Task* newTask, TaskList* taskList);
void displayTaskList(TaskList* taskList);
TaskList* removeTaskFromList(TaskList* taskList, int key);
void displayTaskListRecursive(TaskList* taskList);

//funções da lista de tarefas duplamente encadeada
DoublyTaskList* initializeDoublyTaskList();
DoublyTaskList* allocateTaskNode_D();
DoublyTaskList* getLastTaskNode_D(DoublyTaskList* taskList);
DoublyTaskList* addTaskToList_D(Task* newTask, DoublyTaskList* taskList);

//funções da lista circular de tarefas concluídas

//funções da lista de pendentes
PendingTasks* initializePendingTasks();

//funções da pilha de reversão
UndoStack* initializeUndoStack();

#endif