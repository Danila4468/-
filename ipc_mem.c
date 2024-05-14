#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
	int *array; // Указатель на массив, расположенный в разделённой памяти
	int shmid; // Идентификатор области раздляемой памяти
	int new = 1; // признак необходимости создания нового массива
	char pathname[] = "forftok.ipc"; // Файл необходимыйф для генерации ключа 
	key_t key; // Переменная для хранения ключа
	// Попытка генерации ключа ipc
	if ((key = ftok(pathname, 0)) < 0) {
		printf("Не удалось сгенерировать ipc-ключ\n");
		exit(-1);
	}
	// Попытка создания области разделённой памяти
	if ((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
		// проверяем, что ошибка при создании области разделяемой памяти не связана с тем, что область существует
		if(errno != EEXIST) {
			printf("Не удаётся создать область разделений памяти\n");
			exit(-1);
		}
		// Получение идентификатора области раздяемой памяти, если область уже существует
		else {
			if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
				printf("Не удаётся найти область разделений памяти\n");
				exit(-1);
			}
			new = 0; // Установка признака уже существующей области разделяемой памяти
		}
	}
	// Включение разделяемой памяти в адресное пространство текущего процесса
	if ((array = (int *) shmat(shmid, NULL, 0)) == (int *)(-1)) {
		printf("Не удалось добавить разделяемую память в адресное пространство процесса\n");
		exit(-1);
	}
	// Операции над вновь созданным массивом
	if(new) {
		array[0] = 1;
		array[1] = 0;
		array[2] = 1;
	}
	// Операции над уже существующим массивом
	else {
		array[0] += 1;
                array[2] += 1;

	}
	printf("Программа 1 была запущена %d раз(а), программа 2 - %d раз(а), всего - %d\n", array[0], array[1], array[2]);
	// Исключение области разделяемой памяти из адресного пространства текущего процесса
	if(shmdt(array)<0) {
		printf("Не удалось исключить разделяемую память из адресного пространства процесса\n");
		exit(-1);
	}
	return 0;
}




	
