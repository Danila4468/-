#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
// Создаём массив из двух элементов для хранения файловых дескрипторов для чтения и записи
	int fd[2];
	pid_t result;
	size_t size;
	char string[] = "Hello, world!";
	char resstring[14];
	if(pipe(fd)<0){
		printf("Can\'t create pipe\n");
// Возврат признака аварийного завершения программы (-1)
		exit(-1);
	}
	result = fork();
	if(result<0) {
		printf("Ошибка выполнения fork()\n");
                exit(-1);
	}
	else if (result>0) {
		if (close(fd[0])<0) {
			printf("Ошибка при закрытии pipe на чтение\n");
			exit(-1);
		}
		size = write(fd[1], string, 14);
		// Проверка колличества байт, записанных в строку с помощью write()
		if(size != 14){
			printf("Ошибка при закрытии pipe на чтение\n");
			exit(-1);
		}
		printf("Процесс родитель записал информацию в pipe и заканчивает работу \n");
		if(close(fd[1])<0){
			printf("Не получилось закрыть исходящий поток\n");
			exit(-1);
		}
	}
	else {
		// Закрытие pipe для записи
		if(close(fd[1])<0){
			printf("Не получилось закрыть исходящий поток\n");
			exit(-1);
		}
		size = read(fd[0], resstring, 14);
		// Проверка количества байт, прочитанных из pipe() с помощью read()
 		if(size != 14) {
			printf("Не получилось закрыть исходящий поток\n");
			exit(-1);
		}
		printf("%s\n", resstring);
		// Закрытие pipe для чтения
		if (close(fd[0]) < 0) {
			printf("Не получилось закрыть входящий поток\n");
		exit(-1);
		}
	}
	return 0;
}

		
