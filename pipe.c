#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
// Создаём массив из двух элементов для хранения файловых дескрипторов для чтения и записи
	int fd1[2], fd2[2];
	pid_t result;
	size_t size;
	char string1[] = "Hello, child!", string2[] = "Hello, parent!";
	char resstring1[13], resstring2[14];
	if(pipe(fd1)<0){
		printf("Can\'t create pipe\n");
	// Возврат признака аварийного завершения программы (-1)
		exit(-1);
	}
	if (pipe(fd2)<0){
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
		if (close(fd1[0])<0) {
			printf("Ошибка при закрытии pipe на чтение\n");
			exit(-1);
		}
		if (close(fd2[1])<0) {
                        printf("Ошибка при закрытии pipe на чтение\n");
                        exit(-1);
		}

		size = write(fd1[1], string1, 13);
		// Проверка колличества байт, записанных в строку
		if(size != 13){
			printf("Can\'t write all string\n");
			exit(-1);
		}
		printf("Процесс родитель записал информацию в pipe\n");
		size = read(fd2[0], resstring2, 14);
		// Проверка колличества байт, записанных в строку
		if(size != 14) {
                        printf("Не получилось закрыть исходящий поток\n");
                        exit(-1);
                }
		printf("Информация от дочернего процесса:");
		for (int i=0; i<14; i++) printf("%c", resstring2[i]);
		printf("\n");
		if(close(fd1[1])<0){
			printf("Не получилось закрыть исходящий поток\n");
			exit(-1);
		}
		if(close(fd2[0])<0){
                        printf("Не получилось закрыть исходящий поток\n");
                        exit(-1);
                }
	}
	else {
		if(close(fd1[1])<0){
			printf("Не получилось закрыть входящий поток\n");
			exit(-1);
		}
		if(close(fd2[0])<0){
                        printf("Не получилось закрыть исходящий поток\n");
                        exit(-1);
                }
		size = read(fd1[0], resstring1, 13);
		// Закрытие pipe для записи
 		if(size != 13) {
			printf("Не прочитали строки\n");
			exit(-1);
		}
		printf("Инфорамция от родителя:");
		for (int i=0; i<13; i++) printf("%c", resstring1[i]);
		printf("\n");
		size = write(fd2[1], string2, 14);
		// Проверка колличество байт, прочитанных из pipe
		if(size != 14) {
                        printf("Не получилось вывести строки\n");
                        exit(-1);
                }
		printf("Процесс ребёнка записал информацию в pipe \n");
		// Проверка колличество байт, прочитанных из pipe
		if (close(fd1[0]) < 0) {
			printf("Не получилось закрыть входящий поток\n");
			exit(-1);
		}
		if (close(fd2[1]) < 0) {
                        printf("Не получилось закрыть исходящий поток\n");
                	exit(-1);
		}
	}
	return 0;
}

		
