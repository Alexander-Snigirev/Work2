/*2.2. Создайте программы родителя и потомка с размещением в разных файлах (father.c и son.c).  
Для фиксации состояния таблицы процессов в файле целесообразно 
использовать в коде программы системный вызов system("command_line"), т.е.*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
    pid_t pid;
    system("ps -l > ps_before.txt");
    pid = fork();
    if(pid<0){
        perror("fork failed");
        exit(1);
    }

    if(pid==0){
        printf("Дочерний процесс: PID = %d, PPID = %d\n", getpid(), getppid());
        execl("./task22_son", "task22_son", NULL);
        perror("execl failed");
        exit(1);
    }
    else{
        printf("Родительский процесс: PID = %d, PPID = %d\n", getpid(), getppid());
        system("ps -l > ps_after.txt");
        wait(NULL);
        
        printf("Родительский процесс завершен\n");
    }
    return 0;
}