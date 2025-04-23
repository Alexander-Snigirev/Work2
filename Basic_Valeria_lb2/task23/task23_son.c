/*2.3. Выполните создание процессов с использованием различных функций семейства exec() 
с разными параметрами функций семейства, приведите результаты эксперимента, 
меняя значения переменных окружения и передавая массив входных параметров.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    char *env_var = getenv("MY_VAR");

    
    printf("Потомок: PID = %d, PPID = %d\n", getpid(), getppid());
    printf("Параметры: ");
    for (int i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    
    printf("Значение MY_VAR: %s\n", env_var);

    return 0;
}