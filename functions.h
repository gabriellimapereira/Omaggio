#ifndef FUNCTIONS
#define FUNCTIONS

// estruturas 
// estrutura de tarefa com seus atributos
typedef struct Task {
    int id;
    char name[50];
    char description[300];
    int priority;
    int status;
} Task;

// estrutura da lista de tarefa principal
typedef struct TaskList {
    Task* task;
    struct TaskList* next;
} TaskList;

// estrutura da lista de tarefas concluídas (circular)
typedef struct CompletedTasks {
    Task* task;
    struct CompletedTasks* next;
    int quant;
} CompletedTasks;

// estrutura da lista de tarefas duplamente encadeada
typedef struct DoublyTaskList {
    Task* task;
    struct DoublyTaskList* next;
    struct DoublyTaskList* prev;
} DoublyTaskList;

// estrutura da fila de tarefas pendentes
typedef struct PendingTasks {
    TaskList* first;
    TaskList* last;
} PendingTasks;

// estrutura da pilha de reversão
typedef struct UndoStack {
    struct User* top;
} UndoStack;

// estrutura do usuário
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

//funções utilitárias
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
User* deleteUser(User* userList, int key);
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
void displayTaskListRecursive(TaskList* taskList);
void freeTaskList(TaskList* taskList);

//funções da lista de tarefas duplamente encadeada
DoublyTaskList* initializeDoublyTaskList();
DoublyTaskList* allocateTaskNode_D();
DoublyTaskList* getLastTaskNode_D(DoublyTaskList* taskList);
DoublyTaskList* addTaskToList_D(Task* newTask, DoublyTaskList* taskList);
void displayDoublyTaskList(DoublyTaskList* taskList);
void freeDoublyTaskList(DoublyTaskList* doublyTaskList);

//funções da lista circular de tarefas concluídas
CompletedTasks* initializeCompletedTasks();
CompletedTasks* allocateCircularNode();
CompletedTasks* addTaskToCircularList(Task* newTask, CompletedTasks* completedTasks);
void displayCompletedTasks(CompletedTasks* completedTasks);
void freeCompletedTasks(CompletedTasks* completedTasks);

//funções da fila de pendentes
PendingTasks* initializePendingTasks();
PendingTasks* allocatePendingTasks();
void insertTaskIntoPendingList(PendingTasks* pendingTasks, Task* newTask);
void displayPendingTasks(PendingTasks* pendingTasks);
void completeTask(PendingTasks* pendingTasks, CompletedTasks* completedTasks);
void freePendingTasks(PendingTasks* pendingTasks);

//busca binária de usuário
int size(User* list);
User* getUserAtIndex(User* list, int index);
User* binarySearchUser(User* list, const char* targetName);

#endif