/* 
    TRABALHO DE SISTEMAS OPERACIONAIS 
    ALGORITMO DO BANQUEIRO

    MATEUS PEREIRA DA SILVA -- 11411BCC020
*/

#include "structs.h"
#include "main.h"
#include "sistema.h"
#include "processos.h"
#include "init.h"

int main(int argc, char *argv[])
{
    int i, j, NUMBER_PROCESS;

    //Pega o numero total de processos a serem simulados
    NUMBER_PROCESS = atoi(argv[2]);

    //Alocar um vetor com numero total dos recursos de cada tipo
    int *RESOURCES = (int *)malloc((argc - 4) * sizeof(int));
    for (i = 0; i < (argc - 4); i++)
        RESOURCES[i] = atoi(argv[i + 4]); //Pega cada recurso e transforma em INT

    //Cria Vetor de Recursos DIsponiveis
    resources = (ResourcesSystem)malloc(sizeof(ResourcesSystem));
    (*resources).availableResources = RESOURCES;

    //Criando Processos
    Process *PROCESS = (Process *)malloc(NUMBER_PROCESS * sizeof(Process));
    for (i = 0; i < NUMBER_PROCESS; i++)
        PROCESS[i] = createProcess(resources, i);

    pthread_mutex_init(&lock, NULL);

    //Iniciando os Processos
    for (i = 0; i < NUMBER_PROCESS; i++)
        startThreads(resources, PROCESS[i]);

    //Enquanto houver threads em execucao, o programa nao finalizara
    while (1 == 1)
    {
    }

    return 0;
}

int requisicao_recursos(int pid, int *recursos)
{
    int i = 0;
    pthread_mutex_lock(&lock);
    lockedPid = pid;

    for (i = 0; i <= LENGTH((*resources).availableResources); i++)
        //Verificar se os recursos estão disponiveis
        if (recursos[i] > (*resources).availableResources[i])
        {
            pthread_mutex_unlock(&lock);
            return -1;
        }

    //Aloca os recursos disponiveis
    for (i = 0; i <= LENGTH((*resources).availableResources); i++)
        (*resources).availableResources[i] -= recursos[i];

    pthread_mutex_unlock(&lock);
    return 0;
}

int libera_recursos(int pid, int *recursos)
{
    int i;
    pthread_mutex_lock(&lock);
    lockedPid = pid;

    //Libera os recursos do processo
    for (i = 0; i <= LENGTH((*resources).availableResources); i++)
        (*resources).availableResources[i] += recursos[i];

    pthread_mutex_unlock(&lock);
    return 0;
}