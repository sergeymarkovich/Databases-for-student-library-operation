#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "string.h"
#include "time.h"
// Далее библиотеки, которые мы написали сами. Подробнее в самих библиотеках.
#include "Books.h"
#include "students.h"

/*
	
*/

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Russian");
	
	char A;		// переменная для считывания с консоли
	int Books_R=0;	// права для работы с книгами
	int Students_R=0;	// права для работы со студентами
	
	FILE *fp_users=fopen("users.csv", "r"); // Открываем файл чтобы посчитать количество строк (подробно в book.c)
	if (fp_users==NULL) printf("Ошибка: Файл с пользователями не может быть открыт.");
	else{	
		int LineCount=0;		
		while(! feof(fp_users)){	
			if (fgetc(fp_users)=='\n')
				LineCount++;
		}
		LineCount++; 
		fclose(fp_users);
		while (1){
			printf("БИБЛИОТЕКА МГТУ ИМ. БАУМАНА\n\nТребуется авторизация\n\n");
			printf("Введите логин: ");
			char Login[128]; 
			int k=0;
			SetConsoleCP(1251);
			A=getchar();
			while (A != '\n'){
				Login[k]=A;
				k++;
				A=getchar();
			}
			SetConsoleCP(866); 
			Login[k]='\0';
			
			printf("Введите пароль: ");
			char Password[128]; k=0;
			SetConsoleCP(1251); 
			A=getchar();
			while (A != '\n'){
				Password[k]=A;
				k++;
				A=getchar();
			}
			SetConsoleCP(866);
			Password[k]='\0';
			
			char Buffer[1024];
			fp_users=fopen("users.csv", "r"); // ...Открываем файл для сравнения пары логин/пароль
			
			int i=0;
			for (i=0; i<LineCount;i++){
				fgets(Buffer, 1024,fp_users);
				char CheckLogin[128]; // Переменная для проверки логина
				char CheckPassword[128]; 	// А эта для пароля
				strcpy(CheckLogin,strtok(Buffer,";"));
				strcpy(CheckPassword,strtok(NULL,";"));
				if (strcmp(Password, CheckPassword)==0 && strcmp(Login, CheckLogin)==0){  // Если логины и пароли совпадают с теми, что в файле
					Students_R=atoi(strtok(NULL,";"));	// Считывает права
					Books_R=atoi(strtok(NULL,";"));
					break;
				}
			}
			fclose(fp_users);
			
			if (Students_R==1 && Books_R==1){
				int Case;
				while(1){
					printf("\nВыберите действие:\n0 - Выход\n1 - Работа с книгами\n2 - Работа со студентами\n");
					scanf("%d", &Case);
					printf("\n");
					if (Case==0){
						return 0;
					}
					else if(Case==1){
						Books(Login);
					}
					else if(Case==2){
						Students(Login);
					}
				}
			}
			else if(Students_R==1){
				Students(Login);
				return 0;
			}
			else if(Books_R==1){
				Books(Login);
				return 0;
			}
			else{
				printf("Ошибка. Неверный логин или пароль.\n");
			}
		}
	}
}
