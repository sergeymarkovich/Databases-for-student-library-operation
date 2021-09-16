
#include "Books.h"
#include "students.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

void Students(char Login[]){ // Смотри файл с книгами все очень похоже
	char Buff[1024];
	int Case=0;	
	int BackUpTrigger=0;
	FILE *fp_Students=fopen("students.csv", "r");
	if (fp_Students==NULL) printf("Ошибка: Файл студентов не может быть открыт.");
	else{
		
int LineCount=0;		// Как запустился этот модуль кода, он открывает файл
while(! feof(fp_Students)){	// и считает количество строк в нем (количество переносов строки +1)
	if (fgetc(fp_Students)=='\n')
		LineCount++;
}
LineCount++;
fclose(fp_Students); // Закрываем файл
struct Student *Students; 
Students=(struct Student*)malloc(sizeof(struct Student)); 
int i=0;
fp_Students=fopen("students.csv", "r"); 
for (i=0; i<LineCount;i++){ 
	int k=0;
	fgets(Buff, 1024,fp_Students);
	strcpy(Students[i].Valid,strtok(Buff,";"));  
	strcpy(Students[i].Surname,strtok(NULL,";"));
	strcpy(Students[i].Name,strtok(NULL,";"));
	strcpy(Students[i].patronymic,strtok(NULL,";"));
	strcpy(Students[i].Fackultet,strtok(NULL,";"));
	strcpy(Students[i].Spec,strtok(NULL,";"));
	Students=(struct Student*)realloc(Students ,(i+2)*sizeof(struct Student)); 
}
fclose(fp_Students);

printf("Работа со списком студентов\nУправление:\n0 - Выход\n1 - Добавить студента\n2 - Удалить студента\n3 - Редактировать информацию по студенту\n4 - Посмотреть информацию\n5 - Сохранить бекап\n6 - Загрузить бекап\n7 - Поиск по фамилии\n8 - Просмотр книг студента\n");

while(1){
	
	scanf("%d", &Case);
	printf("\n");  
	if (Case==0){	// ВЫХОД ИЗ ПРОГРАММЫ С СОХРАНЕНИЕМ ИЗМЕНЕНИЙ
		printf("Сохраняем базу данных...\n");
		FILE *fp_Students=fopen("students.csv", "w"); // Открываем файл уже для записи
		if (fp_Students==NULL) printf("Ошибка: Файл с книгами не может быть открыт.");
		else{
			for(i=0; i<LineCount;i++)
				if (strcmp("NULL", Students[i].Valid)!=0) fprintf(fp_Students,"%s;%s;%s;%s;%s;%s",Students[i].Valid,Students[i].Surname,Students[i].Name,Students[i].patronymic,Students[i].Fackultet,Students[i].Spec);
				
			fclose(fp_Students);
			printf("Сохранено успешно, завершаем работу.\n");
			char c=getchar();
			FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("Ошибка: Файл лога не может быть открыт.");
			else
			{
				time_t CurTime=time(NULL); // Создаем переменную для хранениня времени и присваиваем ей текущее время
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// т.к. сtime возвращает время с переносом строки в конце - нужно перенос удалить
				i=0;
				while (Time[i]!='\0')
				{
					if (Time[i]==':' || Time[i]==' ') Time[i]='_';
					i++;
				}
				fprintf(LogFile, "\n%s;%s;\"StudentsEndOfWork\"",Time,Login);
				fclose(LogFile);
			}
		return ;
		}
	}
	else if (Case==1){	// ДОБАВИТЬ НОВОГО СТУДЕНТА
		while (1){
			printf("Добавить нового студента:\nВведите номер студ.билета:");
			char Valid[7];
			char A;
			int k=0;
			A=getchar();
			SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
			A=getchar();
			while (A != '\n'){
				Valid[k]=A;
				k++;
				A=getchar();
			}
			SetConsoleCP(866); 	// Меняем кодировку консоли назад
			Valid[k]='\0';
			int Error=0;
			for(i=0; i<LineCount; i++) {// Проверка если ли уже такой код в базе
				if(strcmp(Valid, Students[i].Valid)==0){
					printf("Ошибка, студент с такой зачеткой уже есть в базе.\n"); Error=1; break;
					}
			}
			if (Error==1) break;
			else{
				k=0;
				printf("Введите имя:");
				char Name[128]; k=0;
				SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
				A=getchar();
				while (A != '\n'){
					Name[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// Меняем кодировку консоли назад
				Name[k]='\0';
				
				printf("Введите Фамилию:");
				char Surname[128]; k=0;
				SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
				A=getchar();
				while (A != '\n'){
					Surname[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// Меняем кодировку консоли назад
				Surname[k]='\0';
				
				printf("Введите Отчество:");
				char patronymic[128]; k=0;
				SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
				A=getchar();
				while (A != '\n'){
					patronymic[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// Меняем кодировку консоли назад
				patronymic[k]='\0';
				
				printf("Введите Факультет:");
				char Fackultet[128]; k=0;
				SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
				A=getchar();
				while (A != '\n'){
					Fackultet[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// Меняем кодировку консоли назад
				Fackultet[k]='\0';
				
				printf("Введите Специальность:");
				char Spec[128]; k=0;
				SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
				A=getchar();
				while (A != '\n'){
					Spec[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// Меняем кодировку консоли назад
				Spec[k]='\0';
				
				LineCount++; 	
				Students=(struct Student*)realloc(Students ,(LineCount)*sizeof(struct Student));
				strcpy(Buff,"\0"); 	//Добавляем перенос строки чтобы в файле все было аккуратно
				strcpy(Buff,Valid); 	//..
				strcpy(Valid,"\n");	//..
				strcat(Valid,Buff);	//..
				strcpy(Students[LineCount-1].Valid,Valid);  
				strcpy(Students[LineCount-1].Surname,Surname);
				strcpy(Students[LineCount-1].Name,Name);
				strcpy(Students[LineCount-1].patronymic,patronymic);
				strcpy(Students[LineCount-1].Fackultet,Fackultet);
				strcpy(Students[LineCount-1].Spec,Spec);
				int T=0;
				printf("Студент добавлен. Возврат в меню.\n");
				 break;
			}
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("Ошибка: Файл лога не может быть открыт.");
			else
			{
				time_t CurTime=time(NULL); // Создаем переменную для хранениня времени и присваиваем ей текущее время
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// т.к. сtime возвращает время с переносом строки в конце - нужно перенос удалить
				i=0;
				while (Time[i]!='\0')
				{
					if (Time[i]==':' || Time[i]==' ') Time[i]='_';
					i++;
				}
				fprintf(LogFile, "\n%s;%s;\"AddStudent\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==2){	// УДАЛИТЬ 
		printf("Введите Номер зачетки для удаления:");
		char Valid[7];
		char A;
		int k=0;
		A=getchar();
		SetConsoleCP(1251);  
		A=getchar();
		while (A != '\n'){
			Valid[k]=A;
			k++;
			A=getchar();
		}
		SetConsoleCP(866); 	
		Valid[k]='\0';
		printf("Поиск студента...\n");
		int i=0; int T=-1;
		int Error=0;
		for(i=0; i<LineCount; i++) {
			if(strcmp(Valid, Students[i].Valid)==0){
				printf("Студент найден...\n"); T=i; break;		
				}
		}
		if (T==-1) printf("Студент не найден, возврат в меню.\n");
		else{
			// Открыть файл с записями
			FILE *SBFile=fopen("student_books.csv", "r"); // Открываем файл чтобы посчитать количество строк (подробно в book.c)
			if (SBFile==NULL) printf("Ошибка: Файл не может быть открыт.");
			else{	
				int SBLineCount=0;		
				while(! feof(SBFile)){	
					if (fgetc(SBFile)=='\n')
						SBLineCount++;
				}
				SBLineCount++; 
				fclose(SBFile);
				// Найти строку с нужным номером зачетки
				char Buff[1024];
				SBFile=fopen("student_books.csv", "r"); // Открываем файл для поиска книг у данного студента
				int BooksTrigger=0;
				for (i=0; i<SBLineCount;i++){
					fgets(Buff, 1024,SBFile);
					char Valid[7];
					strtok(Buff,";"); // пропускаем номер книги
					strcpy(Valid,strtok(NULL,";"));	// записываем номер зачетки
						if (strcmp(Valid,Students[T].Valid)==0){  // Если в файле есть такой номер зачетки, то у студента есть книги.
						BooksTrigger=1;
						break;	// Завершаем цикл
					}
				}
				fclose(SBFile);
				// Если строка есть вывести ошибку, если нет - удалить студента
				if (BooksTrigger==0){
					strcpy(Students[T].Valid,"NULL");// Обозначаем запись как удаленную
					printf("Удалено успешно!\n\n");
				}
				else printf("У данного студента есть книги!\n");
			}
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("Ошибка: Файл лога не может быть открыт.");
			else
			{
				time_t CurTime=time(NULL); // Создаем переменную для хранениня времени и присваиваем ей текущее время
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// т.к. сtime возвращает время с переносом строки в конце - нужно перенос удалить
				i=0;
				while (Time[i]!='\0')
				{
					if (Time[i]==':' || Time[i]==' ') Time[i]='_';
					i++;
				}
				fprintf(LogFile, "\n%s;%s;\"DelStudent\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==3){	// РЕДАКТИРОВАТЬ ИНФОРМАЦИЮ 
		printf("Введите Номер зачетки для редактирования:");
		char Valid[7];
		char A;
		int k=0;
		A=getchar();
		SetConsoleCP(1251);  
		A=getchar();
		while (A != '\n'){
			Valid[k]=A;
			k++;
			A=getchar();
		}
		SetConsoleCP(866); 	
		Valid[k]='\0';
		printf("Поиск студента...\n");
		int i=0; int T=-1;
		int Error=0;
		for(i=0; i<LineCount; i++) {
			if(strcmp(Valid, Students[i].Valid)==0){
				printf("Студент найден.\n"); T=i; break;		
				}
		}
		if (T==-1) printf("Студент не найден, возврат в меню.\n");
		else{
			printf("Информация по студенту:\n%s %s %s %s %s %s\n",Students[T].Valid,Students[T].Surname,Students[T].Name,Students[T].patronymic,Students[T].Fackultet,Students[T].Spec);
			printf("Введите имя:");
				char Name[128]; k=0;
				SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
				A=getchar();
				while (A != '\n'){
					Name[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// Меняем кодировку консоли назад
				Name[k]='\0';
				
				printf("Введите Фамилию:");
				char Surname[128]; k=0;
				SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
				A=getchar();
				while (A != '\n'){
					Surname[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// Меняем кодировку консоли назад
				Surname[k]='\0';
				
				printf("Введите Отчество:");
				char patronymic[128]; k=0;
				SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
				A=getchar();
				while (A != '\n'){
					patronymic[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// Меняем кодировку консоли назад
				patronymic[k]='\0';
				
				printf("Введите Факультет:");
				char Fackultet[128]; k=0;
				SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
				A=getchar();
				while (A != '\n'){
					Fackultet[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// Меняем кодировку консоли назад
				Fackultet[k]='\0';
				
				printf("Введите Специальность:");
				char Spec[128]; k=0;
				SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
				A=getchar();
				while (A != '\n'){
					Spec[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// Меняем кодировку консоли назад
				Spec[k]='\0';
				
				strcpy(Students[T].Valid,Valid);  
				strcpy(Students[T].Surname,Surname);
				strcpy(Students[T].Name,Name);
				strcpy(Students[T].patronymic,patronymic);
				strcpy(Students[T].Fackultet,Fackultet);
				strcpy(Students[T].Spec,Spec);
				printf("Изменеия сохранены успешно, возврат в меню.\n");
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("Ошибка: Файл лога не может быть открыт.");
			else
			{
				time_t CurTime=time(NULL); // Создаем переменную для хранениня времени и присваиваем ей текущее время
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// т.к. сtime возвращает время с переносом строки в конце - нужно перенос удалить
				i=0;
				while (Time[i]!='\0')
				{
					if (Time[i]==':' || Time[i]==' ') Time[i]='_';
					i++;
				}
				fprintf(LogFile, "\n%s;%s;\"StudentEdit\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==4){
		printf("Введите Номер зачетки:");
		char Valid[7];
		char A;
		int k=0;
		A=getchar();
		SetConsoleCP(1251);  
		A=getchar();
		while (A != '\n'){
			Valid[k]=A;
			k++;
			A=getchar();
		}
		SetConsoleCP(866); 	
		Valid[k]='\0';
		printf("Поиск студента...\n");
		int i=0; int T=-1;
		int Error=0;
		for(i=0; i<LineCount; i++) {
			if(strcmp(Valid, Students[i].Valid)==0){
				printf("Студент найден.\n\n");T=i; break;		
				}
		}
		if (T==-1) printf("Студент не найден, возврат в меню.\n");
		else{
			printf("Информация по студенту:\nНомер зачетки: %s\nФамилия: %s\nИмя: %s\nОтчество: %s\nФакультет: %s\nСпециальност:%s\n",Students[T].Valid,Students[T].Surname,Students[T].Name,Students[T].patronymic,Students[T].Fackultet,Students[T].Spec);
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("Ошибка: Файл лога не может быть открыт.");
			else
			{
				time_t CurTime=time(NULL); // Создаем переменную для хранениня времени и присваиваем ей текущее время
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// т.к. сtime возвращает время с переносом строки в конце - нужно перенос удалить
				i=0;
				while (Time[i]!='\0')
				{
					if (Time[i]==':' || Time[i]==' ') Time[i]='_';
					i++;
				}
				fprintf(LogFile, "\n%s;%s;\"StudentInfo\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==5){	// СОХРАНЯЕМ БЕКАП
		time_t CurTime=time(NULL); 
		char Way[64]="students_";
		char Time[32];
		strcpy(Time,ctime(&CurTime));
		Time[strlen(Time)-1]='\0';
		i=0;
		while (Time[i]!='\0'){	
			if (Time[i]==':' || Time[i]==' ') Time[i]='_';
			i++;
		}
		strcat(Way,Time);
		strcat(Way,".csv");
		FILE *BackFile=fopen(Way, "w"); // Создаем файл для записи
		if (BackFile==NULL) printf("Ошибка: Файл сохранения не может быть создан.");
		for(i=0; i<LineCount; i++){
			fprintf(BackFile,"%s;%s;%s;%s;%s;%s",Students[i].Valid,Students[i].Surname,Students[i].Name,Students[i].patronymic,Students[i].Fackultet,Students[i].Spec);
		//	if(i!=LineCount-1) fprintf(BackFile,"\n"); // Чтобы избежать лишнего переноса строки в конце
		}
		fclose(BackFile);
		printf("Успешно Сохранено\n");
		printf("Имя файла: %s\n", Way);
		printf("Возврат в меню\n");
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("Ошибка: Файл лога не может быть открыт.");
			else
			{
				time_t CurTime=time(NULL); // Создаем переменную для хранениня времени и присваиваем ей текущее время
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// т.к. сtime возвращает время с переносом строки в конце - нужно перенос удалить
				i=0;
				while (Time[i]!='\0')
				{
					if (Time[i]==':' || Time[i]==' ') Time[i]='_';
					i++;
				}
				fprintf(LogFile, "\n%s;%s;\"StudentBackUp\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==6){	// ЗАГРУЖАЕМ ИЗ БЕКАПА
		printf("Введите название файла-бекапа: ");
		char Way[64];
		scanf("%s", &Way);
		FILE *BackFile=fopen(Way, "r");
		if (BackFile==NULL) printf("Ошибка: Файл сохранения не может быть открыт.\n");
		else{	
			LineCount=0;				//  Считаем строки в файле бекапа
			while(! feof(BackFile)){	// 	В целом то же самое, что и в начале программы, считываем строки изагоняем в основной файл.
				if (fgetc(BackFile)=='\n')
					LineCount++;
			}
			LineCount++; 
			fclose(BackFile); 
			FILE *BackFile=fopen(Way, "r");
			struct Student *Students; 
			Students=(struct Student*)malloc(sizeof(struct Student)); 
			int i=0;
			for (i=0; i<LineCount;i++){ 
				int k=0;
				fgets(Buff, 1024,BackFile);
				strcpy(Students[i].Valid,strtok(Buff,";"));  
				strcpy(Students[i].Surname,strtok(NULL,";"));
				strcpy(Students[i].Name,strtok(NULL,";"));
				strcpy(Students[i].patronymic,strtok(NULL,";"));
				strcpy(Students[i].Fackultet,strtok(NULL,";"));
				strcpy(Students[i].Spec,strtok(NULL,";"));
				Students=(struct Student*)realloc(Students ,(i+2)*sizeof(struct Student)); 
			}
			fclose(BackFile);
			
			FILE *fp_Books=fopen("books.csv", "w"); // Открываем файл уже для записи
			if (fp_Books==NULL) printf("Ошибка: Файл с книгами не может быть открыт.");
			else{
				for(i=0; i<LineCount;i++){
				if (strcmp("NULL", Students[i].Valid)!=0) fprintf(fp_Students,"%s;%s;%s;%s;%s;%s",Students[i].Valid,Students[i].Surname,Students[i].Name,Students[i].patronymic,Students[i].Fackultet,Students[i].Spec);
				if(i!=LineCount-1){fprintf(fp_Students,"\n");}
				}
				fclose(fp_Students);
				printf("Бекап загружен. Перезапуск библиотеки\n");
				char c=getchar();
			break;
			}
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("Ошибка: Файл лога не может быть открыт.");
			else
			{
				time_t CurTime=time(NULL); // Создаем переменную для хранениня времени и присваиваем ей текущее время
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// т.к. сtime возвращает время с переносом строки в конце - нужно перенос удалить
				i=0;
				while (Time[i]!='\0')
				{
					if (Time[i]==':' || Time[i]==' ') Time[i]='_';
					i++;
				}
				fprintf(LogFile, "\n%s;%s;\"LoadStudentBackUp\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==7){	// ПОИСК ПО ФАМИЛИИ
		printf("Введите Фамилию студента:");
		char Surname[128];
		char A;
		int k=0;
		SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
		A=getchar();
		A=getchar();
		while (A != '\n'){
			Surname[k]=A;
			k++;
			A=getchar();
		}
		SetConsoleCP(866); 	// Меняем кодировку консоли назад
		Surname[k]='\0';
		printf("Поиск Cудентов...\n");
		int i=0; int T=-1;
		for (i=0;i<LineCount;i++){
			if(strcmp(Surname, Students[i].Surname)==0){	
				T=i;
				printf("%s %s %s\nНомер зачетки: %s\nФакультет и специальность: %s %s\n",Students[i].Surname,Students[i].Name,Students[i].patronymic,Students[i].Valid,Students[i].Fackultet,Students[i].Spec);
			}
		}
		if (T==-1) printf("Студент не найден, возврат в меню.\n");
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("Ошибка: Файл лога не может быть открыт.");
			else
			{
				time_t CurTime=time(NULL); // Создаем переменную для хранениня времени и присваиваем ей текущее время
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// т.к. сtime возвращает время с переносом строки в конце - нужно перенос удалить
				i=0;
				while (Time[i]!='\0')
				{
					if (Time[i]==':' || Time[i]==' ') Time[i]='_';
					i++;
				}
				fprintf(LogFile, "\n%s;%s;\"StudentSerch\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if (Case==8){	// ПРОСМОТР ВСЕХ КНИГ СТУДЕНТА
		printf("Введите Номер зачетки:");
		char Valid[7];
		char A;
		int k=0;
		A=getchar();
		SetConsoleCP(1251);  
		A=getchar();
		while (A != '\n'){
			Valid[k]=A;
			k++;
			A=getchar();
		}
		SetConsoleCP(866); 	
		Valid[k]='\0';
		printf("Поиск студента...\n");
		int i=0; int T=-1;
		int Error=0;
		for(i=0; i<LineCount; i++) {
			if(strcmp(Valid, Students[i].Valid)==0){
				printf("Студент найден.\n\n");T=i; break;		
				}
		}
		if (T==-1) printf("Студент не найден, возврат в меню.\n");
		else{
			FILE *SBFile=fopen("student_books.csv", "r"); // Открываем файл чтобы посчитать количество строк (подробно в book.c)
			if (SBFile==NULL) printf("Ошибка: Файл не может быть открыт.");
			else{	
				int SBLineCount=0;		
				while(! feof(SBFile)){	
					if (fgetc(SBFile)=='\n')
						SBLineCount++;
				}
				SBLineCount++; 
				fclose(SBFile);
				// Найти строку с нужным номером зачетки
				char Buff[1024];
				SBFile=fopen("student_books.csv", "r"); // Открываем файл для поиска книг у данного студента
				int BooksTrigger=0;
				long long *ArrISBN;	// Динамический массив с номерами книг
				char Date[SBLineCount][20];
				int ArrCounter=0;
				ArrISBN=(long long*)malloc(sizeof(long long));
				for (i=0; i<SBLineCount;i++){
					fgets(Buff, 1024,SBFile);
					char Valid[7];
					long long ISBN;
					char CheckDate[20];
					
					ISBN=atoll(strtok(Buff,";")); // Запоминаем номер ИСБН
					strcpy(Valid,strtok(NULL,";"));	// записываем номер зачетки
					strcpy(CheckDate,strtok(NULL,";"));
						if (strcmp(Valid,Students[T].Valid)==0){  // Если в файле есть такой номер зачетки, то записываем Номер в массив
						ArrISBN=(long long*)realloc(ArrISBN ,(ArrCounter+2)*sizeof(long long));
						ArrISBN[ArrCounter]=ISBN;
						strcpy(Date[ArrCounter],CheckDate);
						ArrCounter++;
					}
				}
				fclose(SBFile);
				
				if (ArrCounter==0){
					printf("У студента нет книг на руках.\n");
				}
				else{
					FILE *fp_Books=fopen("books.csv", "r");
					if (fp_Books==NULL) printf("Ошибка: Файл с книгами не может быть открыт.");
					else{
						int BLineCount=0;		
						while(! feof(fp_Books)){
							if (fgetc(fp_Books)=='\n')
								BLineCount++;
						}
						BLineCount++;
						fclose(fp_Books);
						
						fp_Books=fopen("books.csv", "r");
						printf ("Книги на руках:");
						for (i=0; i<BLineCount;i++){
							fgets(Buff, 1024,fp_Books); //Считываем строку
							long long ISBN;
							ISBN=atoll(strtok(Buff,";"));
							int k=0;
							for (k=0; k<=ArrCounter;k++){
								if(ArrISBN[k]==ISBN) printf("%lli\nКнига: %s\nАвтор: %s\nДата возврата: %s\n\n",ISBN,strtok(NULL,";"),strtok(NULL,";"), Date[k]);
							}
						}
						fclose(fp_Books);
					}
				}
			}
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("Ошибка: Файл лога не может быть открыт.");
			else
			{
				time_t CurTime=time(NULL); // Создаем переменную для хранениня времени и присваиваем ей текущее время
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// т.к. сtime возвращает время с переносом строки в конце - нужно перенос удалить
				i=0;
				while (Time[i]!='\0')
				{
					if (Time[i]==':' || Time[i]==' ') Time[i]='_';
					i++;
				}
				fprintf(LogFile, "\n%s;%s;\"AllBooksOFStudent\"",Time,Login);
				fclose(LogFile);
			}
	}
}
}
}
