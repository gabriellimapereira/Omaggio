#ifndef FUNCTIONS
#define FUNCTIONS

typedef struct Task {
    int id;
    char name[50];
    char description[300];
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
void displayUser(User*);

// funções de tarefas
Task* allocateTask();
int checkTaskId(TaskList* taskList, int id);
int generateRandTaskId(TaskList* taskList);
Task* setterTask(Task* newTask, TaskList* taskList);
void printTask(Task* task);

// funções de lista encadeada
TaskList* initializeTaskList();
TaskList* allocateTaskNode();
TaskList* getTaskById(TaskList* taskList, int key);
TaskList* getLastTaskNode(TaskList* taskList);
TaskList* addTaskToList(Task* newTask, TaskList* taskList);
TaskList* removeTaskFromList(TaskList* taskList, int key);
void displayTaskListRecursive(TaskList* taskList);

//funções da lista de tarefas duplamente encadeada
DoublyTaskList* initializeDoublyTaskList();
DoublyTaskList* allocateTaskNode_D();
DoublyTaskList* getLastTaskNode_D(DoublyTaskList* taskList);
DoublyTaskList* addTaskToList_D(Task* newTask, DoublyTaskList* taskList);
void displayDoublyTaskList(DoublyTaskList* taskList);

//funções da lista circular de tarefas concluídas
CompletedTasks* initializeCompletedTasks();
CompletedTasks* allocateCircularNode();
CompletedTasks* addTaskToCircularList(Task* newTask, CompletedTasks* completedTasks);
void displayCompletedTasks(CompletedTasks* completedTasks);

//funções da lista de pendentes
PendingTasks* initializePendingTasks();
PendingTasks* allocatePendingTasks();
void insertTaskIntoPendingList(PendingTasks* pendingTasks, Task* newTask);
void displayPendingTasks(PendingTasks* pendingTasks);
void completeTask(PendingTasks* pendingTasks, CompletedTasks* completedTasks);

//funções da pilha de reversão
UndoStack* initializeUndoStack();

//busca binária de usuário
int size(User* list);
User* getUserAtIndex(User* list, int index);
User* binarySearchUser(User* list, const char* targetName);

#endif