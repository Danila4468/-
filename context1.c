//подключение библиотек
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//главная функция программы
int main(int argc, char *argv[], char *envp[]) {
	//Объявление переменных
	int result1;
	pid_t procid, parentid; // Идентификаторы процессов
	pid_t result; //Результат системного вызова fork()
	int a = 0; //Переменная для проверки работы процесса-родителя и процесса-ребёнка
	result = fork();
	if (result < 0) {
		printf("Ошибка при выполнении fork()\n");
		exit(-1);
	}
	else if (result == 0) {
		a = a+1;
		procid = getpid(); //Получение идентификатора текущего процесса
		parentid = getppid(); //Получение идентификатора родительского процесса
		printf("Ид. процесса: %d, ид. родителя: %d, значение переменной a: %d\n", procid, parentid, a);
		result1 = execle("/bin/cat", "/bin/cat", "otchet_16.04.2024.txt", 0, envp);
        	printf("Ошибка при выполнении системного вызова execle()\n");
        	exit(-1);
	}
	else {
		a = a + 555;
		procid = getpid(); //Получение идентификатора текущего процесса
                parentid = getppid(); //Получение идентификатора родительского процесса
                printf("Ид. процесса: %d, ид. родителя: %d, значение переменной a: %d\n", procid, parentid, a);
	}
	//Запуск программы cat с аргументом otchet_16.04.2024.txt
	return 0;//Никогда не выполнятеся

}
