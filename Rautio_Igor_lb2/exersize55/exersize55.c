/*5.5. Можно ли задать разные процедуры планирования разным процессам с одинаковыми приоритетами. 
Как они будут конкурировать, подтвердите экспериментально. 
Существует ли понятие приоритетности по отношению к политике планирования?*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

void compute_task(char sym, FILE* ff) {
    volatile long long i;
    for (i = 0; i < 1000000000LL; i++)
    if(i%100000000==0){
        fprintf(ff, "Процесс %c выполняется\n", sym); // Простая нагрузка
        fflush(ff);
        }
    fprintf(ff, "\n");    
}

int main() {
    pid_t pid1, pid2,pid3,pid4;
    FILE *ff = fopen("out.txt", "a");
    struct sched_param param;
    struct timeval start, end;
    double time_spent;

    // Устанавливаем параметры для SCHED_FIFO с приоритетом 10
    param.sched_priority = 10;

    pid1 = fork();
    if (pid1 == 0) {
        // Устанавливаем SCHED_FIFO для первого процесса (требуется root)
        if (sched_setscheduler(0, SCHED_RR, &param) == -1) {
            perror("Ошибка установки SCHED_FIFO для процесса 1 (нужен root)");
            exit(1);
        }
        fprintf(ff,"Процесс 1 (PID: %d) начал выполнение с приоритетом %d\n", getpid(), param.sched_priority);
        
        gettimeofday(&start, NULL);
        compute_task('1',ff);
        gettimeofday(&end, NULL);
        
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        fprintf(ff,"Процесс 1 завершён. Время: %.3f секунд\n", time_spent);
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        // Устанавливаем SCHED_FIFO для второго процесса
        if (sched_setscheduler(0, SCHED_RR, &param) == -1) {
            perror("Ошибка установки SCHED_FIFO для процесса 2 (нужен root)");
            exit(1);
        }
        fprintf(ff,"Процесс 2 (PID: %d) начал выполнение с приоритетом %d\n", getpid(), param.sched_priority);
        
        gettimeofday(&start, NULL);
        compute_task('2',ff);
        gettimeofday(&end, NULL);
        
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        fprintf(ff,"Процесс 2 завершён. Время: %.3f секунд\n", time_spent);
        exit(0);
    }
    pid3 = fork();
    if (pid3 == 0) {
        // Устанавливаем SCHED_FIFO для второго процесса
        if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
            perror("Ошибка установки SCHED_FIFO для процесса 3 (нужен root)");
            exit(1);
        }
        fprintf(ff,"Процесс 3 (PID: %d) начал выполнение с приоритетом %d\n", getpid(), param.sched_priority);
        
        gettimeofday(&start, NULL);
        compute_task('3',ff);
        gettimeofday(&end, NULL);
        
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        fprintf(ff,"Процесс 3 завершён. Время: %.3f секунд\n", time_spent);
        exit(0);
    }
    pid4 = fork();
    if (pid4 == 0) {
        // Устанавливаем SCHED_FIFO для второго процесса
        if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
            perror("Ошибка установки SCHED_FIFO для процесса 3 (нужен root)");
            exit(1);
        }
        fprintf(ff,"Процесс 4 (PID: %d) начал выполнение с приоритетом %d\n", getpid(), param.sched_priority);
        
        gettimeofday(&start, NULL);
        compute_task('4',ff);
        gettimeofday(&end, NULL);
        
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        fprintf(ff,"Процесс 4 завершён. Время: %.3f секунд\n", time_spent);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    fprintf(ff,"Все процессы завершены.\n");
    fclose(ff);
    return 0;
}