#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int a = 0; // Инициализация глобальной статической переменной, доступной из каждого треда
// Функция выполняющаяся в рамках второго треда
void *mythread(void *dummy){
	pthread_t mythid; // Идентификатор треда - для каждого имеет своё значение
	mythid = pthread_self();
	a = a+1;
	printf("Thread %ld, Результат вычисления a = %d\n", mythid, a); // Печать идентификатора текущего треда и результат текущего значения глобальной переменной
	return NULL;
}

int main() {
	pthread_t thid, mythid;
	int result;
	result = pthread_create(&thid, (pthread_attr_t *)NULL, mythread, NULL); // Создание нового треда
	if(result != 0) {
		printf("Ошибка при создании нового thread\'a, возвращения значение = %d\n", result);
		exit(-1);
	}
	printf("Thread создан, thid = %ld\n", thid);
	mythid = pthread_self(); // Сохраняем в перемнной mythid идентификатор главного треда 
	a = a+1;
	printf("Thread %ld, Результат вычисления a = %d\n", mythid, a);
	pthread_join(thid, (void **)NULL); // Ожидание завершения порождённого треда
	return 0;
} 
