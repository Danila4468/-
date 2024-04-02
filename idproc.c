//Подключение билиотек
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//Главная функция программы
int main() {
//Объявение переменных
        pid_t getpid;
        pid_t getppid;
//Системный вызов getpid()
        pid = getpid();
//Системный вызов getppid()
        ppid = getppid();
        printf("Ид. пользователя: %d\n", pid);
        printf("Ид. группы пользователя: %d\n", ppid);
//Возврат значение "0" из главной функции
        return 0;
}

