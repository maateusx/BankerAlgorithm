#include "sistema.h"

//Criacao das threads
void startThreads(ResourcesSystem s, Process p)
{
    pthread_t process_thread;
    ProcessThread process = (ProcessThread)malloc(sizeof(ProcessThread));
    (*process).thread = process_thread;
    (*process).process = p;
    pthread_create(&process_thread, NULL, executeProcess, process);
}

//Executa Processos
void *executeProcess(void *p)
{
    int running = 1;
    int seg_sleep = 0;
    while (running)
    {
        Process pTemp = (*(ProcessThread)p).process;
        //Solicita permissão para alocar recurso
        if (requisicao_recursos((*pTemp).pid, (*pTemp).resources) == 0) //caso haja recurso
        {
            printf("Processo %d: Alocou Recursos.\n", (*pTemp).pid);
            seg_sleep = (rand() % 2) + 1;
            sleep(seg_sleep); //Dorme um tempo random
            printf("Processo %d: Entrou em Sleep. %d Segundos\n", (*pTemp).pid, seg_sleep);
            libera_recursos((*pTemp).pid, (*pTemp).resources);
            seg_sleep = (rand() % 2) + 1;
            sleep(seg_sleep);
            printf("Processo %d: Entrou em Sleep. %d Segundos\n", (*pTemp).pid, seg_sleep);
            printf("Processo %d: Desalocou Recursos.\n", (*pTemp).pid);
            //Devo finalizar a thread?
        }
        else //caso não haja mais recursos disponiveis
        {
            running = 0; //Caso deseja finalizar a thread
            printf("Alocacao de recursos para PROCESSO %d falhou, encerrando thread.\n", (*pTemp).pid);
        }
    }
}