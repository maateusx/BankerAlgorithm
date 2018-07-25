#include "processos.h"

//Cria numero de recursos necessarios desse processo
Process createProcess(ResourcesSystem resource, int process)
{
    srand((unsigned)time(NULL));
    Process p = (Process)malloc(sizeof(Process));
    (*p).pid = process;
    (*p).resources = (int *)malloc(LENGTH((*resource).availableResources) * sizeof(int));
    for (int i = 0; i <= LENGTH((*resource).availableResources); i++)
        (*p).resources[i] = rand() % (*resource).availableResources[i];
    return p;
}