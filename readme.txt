Instruções

Para compilar o programa:
    gcc -pthread -o main main.c processos.c sistema.c

Para Executar é esperado uma entrada do tipo:
    ./main -n 2 -a 5 7 9
    ./main -n 3 -a 2 3 5

Onde no segundo caso, 3 é o número de threads que iram ser criadas e os números em sequencias, os recursos disponiveis.