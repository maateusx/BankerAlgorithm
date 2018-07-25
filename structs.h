#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define LENGTH(a) (sizeof(a) / sizeof(*a))

#ifndef structs
#define structs

struct resourcesSystem
{
    int *availableResources;
} typedef *ResourcesSystem;

struct process
{
    int pid;
    int *resources;
} typedef *Process;

struct processThread
{
    pthread_t thread;
    struct process *process;
} typedef *ProcessThread;

#endif