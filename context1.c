//подключение библиотек
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//главная функция программы
int main(int argc, char *argv[], char *envp[]) {
	int result;
	//Запуск программы cat с аргументом otchet_16.04.2024.txt
	result = execle("/bin/cat", "/bin/cat", "otchet_16.04.2024.txt", 0, envp);
	//printf() выполнятеся только в случае ошибки вызова execle()
	printf("Ошибка при выполнении системного вызова execle()\n");
	exit(-1);
	return 0;//Никогда не выполнятеся

}
