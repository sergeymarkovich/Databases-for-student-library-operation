#include "Books.h"
#include "students.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
/*
Эта библиотека нужна для работы с файлами "book.csv" и что-то там еще, потом подправлю (Сложность 1)
*/


void Books(char Login[]) 
{
	char Buff[1024];
	int Case=0;	// Триггер на выбор комманды
	int BackUpTrigger=0; // Переменная, которая не дает изменить файл после бекапа
	FILE *fp_Books=fopen("books.csv", "r");
	if (fp_Books==NULL) printf("Ошибка: Файл с книгами не может быть открыт.");
	else{
		
int LineCount=0;		// Как запустился этот модуль кода, он открывает файл
while(! feof(fp_Books)){	// и считает количество строк в нем (количество переносов строки +1)
	if (fgetc(fp_Books)=='\n')
		LineCount++;
}
LineCount++; // То самое "+1"
fclose(fp_Books); // Закрываем файл

struct Book *Books; // А потом создает массив объектов класса Книга (Подробнее в Books.h)
Books=(struct Book*)malloc(sizeof(struct Book)); // Выделяем память под первую книгу
int i=0;
fp_Books=fopen("books.csv", "r"); // ...Открываем файл чтобы считать содержимое
for (i=0; i<LineCount;i++){ // И заполняем его
	int k=0;
	fgets(Buff, 1024,fp_Books); //Считываем строку
												// strtok -  разделяеn строку по спец символу (;)
	Books[i].ISBN=atoll(strtok(Buff,";")); 		// atoll - разновидность atoi для бооольших чисел
	strcpy(Books[i].Author,strtok(NULL,";"));   // strcpy - копироет содержимое из второй переменной в первую (Другими способами получить содержимое файла не получилось)
	strcpy(Books[i].Name,strtok(NULL,";"));
	Books[i].NumAll=atoi(strtok(NULL,";"));
	Books[i].NumUsed=atoi(strtok(NULL,"\n"));
	Books=(struct Book*)realloc(Books ,(i+2)*sizeof(struct Book)); //выделяем память под следующую переменную
}
fclose(fp_Books);

printf("Библиотека запущена\nУправление:\n0 - Выход\n1 - Просмотр таблицы\n2 - Добавить новую книгу\n3 - Удалить книгу\n4 - Подробнее о книге\n5 - Редактировать информацию о книге\n6 - Изменить количество книг\n7 - Выдать книгу\n8 - Вернуть книгу\n9 - Cделать бекап\n10 - Загрузить бекап\n11 - Поиск по автору\n12 - Посмотреть у кого книга на руках\n");

while (1){
	
	scanf("%d", &Case);  // Используем адресс переменной - особенность сканф
	printf("\n");
	if (Case==0){	// ВЫХОД ИЗ ПРОГРАММЫ С СОХРАНЕНИЕМ ИЗМЕНЕНИЙ
		printf("Сохраняем базу данных...\n");
		FILE *fp_Books=fopen("books.csv", "w"); // Открываем файл уже для записи
		if (fp_Books==NULL) printf("Ошибка: Файл с книгами не может быть открыт.");
		else{
			for(i=0; i<LineCount;i++){
			if (Books[i].ISBN!=0) {
			fprintf(fp_Books,"%lli;%s;%s;%d;%d", Books[i].ISBN,Books[i].Author, Books[i].Name, Books[i].NumAll, Books[i].NumUsed);
			if(i!=LineCount-1) fprintf(fp_Books,"\n");
			}
			}
			printf("Сохранено успешно, завершаем работу.\n");
			fclose(fp_Books);
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
				fprintf(LogFile,"\n%s;%s;\"LibEndOfWork\"",Time,Login);
				fclose(LogFile);
			}
		return ;
		}
	}
	else if (Case==1){	// ВЫВОД ИНФОРМАЦИИ ПО ВСЕМ КНИГАМ
		struct Book BuffBook; // Создаем элемент - буфер обмена для перестановки книг местами.
		int s=0; // переменная сдвига		ПРИМЕНЯЕМ СОРТИРОВКУ ПУЗЫРЬКОМ!!!!
		for(i=0; i<LineCount; i++){
			for(s=0; s<LineCount-1; s++){
				if (Books[s].ISBN>Books[s+1].ISBN){
					
					//Записываем нашу книгу в буфер
					BuffBook.ISBN=Books[s].ISBN;
					strcpy(BuffBook.Author,Books[s].Author);
					strcpy(BuffBook.Name,Books[s].Name);
					BuffBook.NumAll=Books[s].NumAll;
					BuffBook.NumUsed=Books[s].NumUsed;
					
					//Перезаписываем следующую по порядку книгу на ее место
					Books[s].ISBN=Books[s+1].ISBN;
					strcpy(Books[s].Author,Books[s+1].Author);
					strcpy(Books[s].Name,Books[s+1].Name);
					Books[s].NumAll=Books[s+1].NumAll;
					Books[s].NumUsed=Books[s+1].NumUsed;
					
					//Записываем книгу из буфера на новое место
					Books[s+1].ISBN=BuffBook.ISBN;
					strcpy(Books[s+1].Author,BuffBook.Author);
					strcpy(Books[s+1].Name,BuffBook.Name);
					Books[s+1].NumAll=BuffBook.NumAll;
					Books[s+1].NumUsed=BuffBook.NumUsed;
				}
			}
		}
		for (i=0; i<LineCount; i++)
		{
			if (Books[i].ISBN!=0) printf("%lli %s %s %d %d\n", Books[i].ISBN,Books[i].Author, Books[i].Name, Books[i].NumAll, Books[i].NumAll-Books[i].NumUsed); // lli - индентефикатор для long long типа
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
				fprintf(LogFile, "\n%s;%s;\"BookList\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if (Case==2){	// ДОБАВИТЬ НОВУЮ КНИГУ
		while (1){
			printf("Добавить новую книгу:\nВведите ее ISBN:");
			unsigned long long ISBN;
			scanf("%lli", &ISBN);
			
			int Error=0;
			for(i=0; i<LineCount; i++) {// Проверка если ли уже такой код в базе
				if(Books[i].ISBN==ISBN){
					printf("Ошибка, такой ISBN уже используется.\n"); Error=1; break;
					}
			}
			if (Error==1) break;
			
			int k=0;
			int A;
			A=getchar(); // Почему-то в потоке консоли остается перенос строки просто сожрем его
			printf("Введите автора:");
			char Author[128]; k=0;
			SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
			A=getchar();
			while (A != '\n'){
				Author[k]=A;
				k++;
				A=getchar();
			}
			SetConsoleCP(866); 	// Меняем кодировку консоли назад
			Author[k]='\0';
			
			printf("Введите название:");
			char Name[128]; k=0;
			SetConsoleCP(1251);
			A=getchar();
			while (A != '\n'){
				Name[k]=A;
				k++;
				A=getchar();
			}
			SetConsoleCP(866);
			Name[k]='\0';
			
			printf("Введите количество книг:");
			int Count;
			scanf("%d", &Count);
			
			LineCount++; 	// И говорим что теперь у нас на одну книгу больше
			Books=(struct Book*)realloc(Books ,(LineCount)*sizeof(struct Book));
			Books[LineCount-1].ISBN=ISBN;
			Books[LineCount-1].NumAll=Count;
			Books[LineCount-1].NumUsed=0;
			strcpy(Books[LineCount-1].Author, Author);
			strcpy(Books[LineCount-1].Name, Name);
			
			break;
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
				fprintf(LogFile, "\n%s;%s;\"AddBook\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==3){	// УДАЛИТЬ КНИГУ
		printf("Введите ISBN книги для удаления:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("Поиск книги...\n");
		int i=0; int T=-1; // T - проверка на нахождение
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN){
				printf("Книга найдена...\nПодготовка к удалению....\n"); T=i; break;
			}
		}
		if (T==-1) printf("Книга не найдена, возврат в меню.\n");
		else{
			// Открыть файл с записями
			FILE *SBFile=fopen("student_books.csv", "r"); // Открываем файл чтобы посчитать количество строк (подробно в book.c)
			if (SBFile==NULL) printf("Ошибка: Файл c записями не может быть открыт.");
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
					long long ISBN;
					ISBN=atoll(strtok(Buff,";"));	// записываем номер книги
						if (Books[T].ISBN==ISBN){  // Если в файле есть такой номер зачетки, то у студента есть книги.
						BooksTrigger=1;
						break;	// Завершаем цикл
					}
				}
				fclose(SBFile);
				// Если строка есть вывести ошибку, если нет - удалить студента
				if (BooksTrigger==0){
					Books[T].ISBN=0;// Обозначаем запись как удаленную
					printf("Удалено успешно!\n\n");
				}
				else printf("Данная книга находится на руках!\n");
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
				fprintf(LogFile, "\n%s;%s;\"DelBook\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==4){	// ВЫВЕСТИ ИНФОРМАЦИЮ ПО КНИГЕ
		printf("Введите ISBN книги:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("Поиск книги...\n");
		int i=0; int T=-1; // T - проверка на нахождение
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("Книга найдена...\n"); T=i; break;
			}
		}
		if (T==-1) printf("Книга не найдена, возврат в меню.\n");
		else{
			printf("ISBN: %lli\nАвтор: %s\nНазвание: %s\nКниг в библиотеке: %d\nКниг на руках: %d\n", Books[T].ISBN,Books[T].Author, Books[T].Name, Books[T].NumAll, Books[T].NumUsed);
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
				fprintf(LogFile, "\n%s;%s;\"BookInfo\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==5){	// РЕДАКТИРОВАТЬ ИНФОРМАЦИЮ ПО КНИГЕ 
		printf("Введите ISBN книги:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("Поиск книги...\n");
		int i=0; int T=-1; // T - проверка на нахождение
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("Книга найдена...\n\n"); T=i; break;
			}
		}
		if (T==-1) printf("Книга не найдена, возврат в меню.\n");
		else{
			printf("Информация по книге:\nАвтор: %s\nНазвание: %s\n\n", Books[T].Author, Books[T].Name);
			printf("Введите новое название:");
			char Name[128];
			SetConsoleCP(1251);
			scanf("%s", &Name);
			SetConsoleCP(866);
			printf("Введите автора:");
			char Author[128];
			SetConsoleCP(1251);
			scanf("%s", &Author);
			SetConsoleCP(866);
			strcpy(Books[T].Name,Name);
			strcpy(Books[T].Author, Author);
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
				fprintf(LogFile, "\n%s;%s;\"BookEdit\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==6){	// ИЗМЕНИТЬ КОЛИЧЕСТВО КНИГ В БИБЛИОТЕКЕ
		printf("Введите ISBN книги:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("Поиск книги...\n");
		int i=0; int T=-1; // T - проверка на нахождение
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("Книга найдена...\n\n"); T=i; break;
			}
		}
		if (T==-1) printf("Книга не найдена, возврат в меню.\n");
		else{
			printf("Информация по книге:\nАвтор: %s\nНазвание: %s\n\n", Books[T].Author, Books[T].Name);
			printf("Введите новое количество книг:");
			int Count=0;
			scanf("%d", &Count);
			Books[T].NumAll=Count;
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
				fprintf(LogFile, "\n%s;%s;\"BookCountEdit\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==7){	// ВЫДАТЬ КНИГУ
		printf("Введите ISBN книги:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("Поиск книги...\n");
		int i=0; int T=-1;
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("Книга найдена...\n\n"); T=i; break;
			}
		}
		if (T==-1) printf("Книга не найдена, возврат в меню.\n");
		else{
			printf("Название: %s Автор: %s\n", Books[T].Name, Books[T].Author);
			if (Books[T].NumUsed==Books[T].NumAll){
				printf("Ошибка. Недостаточно книг.\n");
				printf("Эта книга будет сдана:\n");
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
					
					SBFile=fopen("student_books.csv", "r");
					char StringArr[SBLineCount][64]; // Копируем содержимое файла в оперативную память
					char Buff[64];
					for (i=0; i<SBLineCount; i++){
						fgets(Buff, 1024,SBFile);
						long long CheckISBN=atoll(strtok(Buff,";"));
						char CheckZach[7];
						strcpy(CheckZach,strtok(NULL,";"));
						char Date[16];
						strcpy(Date,strtok(NULL,";"));
						if(CheckISBN==ISBN) printf("%s\n",Date);
					}
					fclose(SBFile);
				}
			} 
			else{
				printf("Введите номер студента: ");
				char Zach[7];
				char A;
				int k=0;
				A=getchar();
				SetConsoleCP(1251);  
				A=getchar();
				while (A != '\n'){
					Zach[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	
				Zach[k]='\0';
				printf("Введите дату сдачи книги в формате \"день.месяц.год\": ");
				char Date[16];
				k=0;
				SetConsoleCP(1251);  
				A=getchar();
				while (A != '\n'){
					Date[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	
				Date[k]='\0';
				
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
					
					SBFile=fopen("student_books.csv", "r");
					char StringArr[SBLineCount][64]; // Копируем содержимое файла в оперативную память
					char Buff[64];
					for (i=0; i<SBLineCount; i++){
						fgets(Buff, 1024,SBFile);
						strcpy(StringArr[i],Buff);
					}
					fclose(SBFile);
					
					SBFile=fopen("student_books.csv", "w");
					for(i=0;i<SBLineCount;i++){
						fprintf(SBFile,"%s\n",StringArr[i]);
					}
					fprintf(SBFile,"%lli;%s;<%s>",ISBN,Zach,Date);
					fclose(SBFile);
					printf("Книга выдана. Возврат в меню.\n");
					Books[T].NumUsed++;
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
				fprintf(LogFile, "\n%s;%s;\"GiveBook\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==8){	// ВЕРНУТЬ КНИГУ В БИБЛИОТЕКУ
		printf("Введите ISBN книги:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("Поиск книги...\n");
		int i=0; int T=-1;
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("Книга найдена...\n\n"); T=i; break;
			}
		}
		if (T==-1) printf("Книга не найдена, возврат в меню.\n");
		else{
			printf("Введите номер студента: ");
				char Zach[7];
				char A;
				int k=0;
				A=getchar();
				SetConsoleCP(1251);  
				A=getchar();
				while (A != '\n'){
					Zach[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	
				Zach[k]='\0';
				
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
					SBFile=fopen("student_books.csv", "r");
					char StringArr[SBLineCount][64]; // Копируем содержимое файла в оперативную память
					char Buff[64];					// Кроме удаляемой строки
					for (i=0; i<SBLineCount; i++){
						fgets(Buff, 1024,SBFile);
						strcpy(StringArr[i],Buff); // Сохраняем строку
						long long CheckISBN=atoll(strtok(Buff,";")); // Дробим ее на состовляющие
						char CheckZach[7];
						strcpy(CheckZach, strtok(NULL,";"));
						
						if (ISBN!=CheckISBN || strcmp(Zach,CheckZach)==0)	// И если это искомая строка - обнуляем ее.
						strcpy(StringArr[i],"NULL");
					}
					fclose(SBFile);		
					SBFile=fopen("student_books.csv", "w");
					for(i=0;i<SBLineCount;i++){
						char NULLS[5];
						strcpy(NULLS,"NULL");
						
						if(strcmp(StringArr[i],NULLS)!=0){
							fprintf(SBFile,"%s\n",StringArr[i]);	// Записываем все строки кроме обнуленной
						}
						
					}
					fclose(SBFile);
					printf("Книга выдана. Возврат в меню.\n");
					Books[T].NumUsed++;
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
				fprintf(LogFile, "\n%s;%s;\"TakeBook\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==9){	// СОХРАНЯЕМ БЕКАП
		time_t CurTime=time(NULL); // Создаем переменную для хранениня времени и присваиваем ей текущее время
		char Way[64]="books_"; // Создаем переменную для пути размер массива должен быть большим чтобы избежать ошибок нехватки места
		char Time[32];
		strcpy(Time,ctime(&CurTime));
		Time[strlen(Time)-1]='\0';	// т.к. сtime возвращает время с переносом строки в конце - нужно перенос удалить
		i=0;
		while (Time[i]!='\0'){	//Проверим строку на недопустимые символы и заменим их нижним прочерком
			if (Time[i]==':' || Time[i]==' ') Time[i]='_';
			i++;
		}
		strcat(Way,Time);
		strcat(Way,".csv");
		FILE *BackFile=fopen(Way, "w"); // Создаем файл для записи
		if (BackFile==NULL) printf("Ошибка: Файл с книгами не может быть создан.");
		for(i=0; i<LineCount; i++){
			if (Books[i].ISBN!=0) fprintf(BackFile,"%lli;%s;%s;%d;%d", Books[i].ISBN,Books[i].Author, Books[i].Name, Books[i].NumAll, Books[i].NumUsed);
			if(i!=LineCount-1 && Books[i].ISBN!=0) fprintf(BackFile,"\n"); // Чтобы избежать лишнего переноса строки в конце
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
				fprintf(LogFile, "\n%s;%s;\"BackUp\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==10){	// ЗАГРУЖАЕМ ИЗ БЕКАПА
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
			struct Book BackBooks[LineCount]; // НО вот тут +12 не нужно, так-как новые книги не появятся в процессе востановления
			int i=0;
			for (i=0; i<LineCount;i++){ // И заполняем его
				int k=0;
				fgets(Buff, 1024,BackFile); 
				BackBooks[i].ISBN=atoll(strtok(Buff,";")); 	
				strcpy(BackBooks[i].Author,strtok(NULL,";"));
				strcpy(BackBooks[i].Name,strtok(NULL,";"));
				BackBooks[i].NumAll=atoi(strtok(NULL,";"));
				BackBooks[i].NumUsed=atoi(strtok(NULL,"\n"));
			}
			fclose(BackFile);
			
			FILE *fp_Books=fopen("books.csv", "w"); // Открываем файл уже для записи
			if (fp_Books==NULL) printf("Ошибка: Файл с книгами не может быть открыт.");
			else{
				for(i=0; i<LineCount;i++){
				fprintf(fp_Books,"%lli;%s;%s;%d;%d", BackBooks[i].ISBN,BackBooks[i].Author, BackBooks[i].Name, BackBooks[i].NumAll, BackBooks[i].NumUsed);
				if(i!=LineCount-1) fprintf(fp_Books,"\n");
				}
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
				fprintf(LogFile, "\n%s;%s;\"LoadBackUp\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==11){	// ПОИСК ПО АВТОРУ
		printf("Введите Автора:");
		char Author[128];
		char A;
		int k=0;
		SetConsoleCP(1251);  // Меняем кодировку консоли чтобы нормально считать символы кириллицы
		A=getchar();
		A=getchar();
		while (A != '\n'){
			Author[k]=A;
			k++;
			A=getchar();
		}
		SetConsoleCP(866); 	// Меняем кодировку консоли назад
		Author[k]='\0';
		printf("Поиск книг...\n");
		int i=0; int T=-1;
		for (i=0;i<LineCount;i++){
			if(strcmp(Author, Books[i].Author)==0 && Books[i].ISBN!=0){	
				T=i;
				printf("Номер ISBN: %lli Название: %s Количество в библиотеке: %d\n",Books[i].ISBN, Books[T].Name, Books[i].NumAll);
			}
		}
		if (T==-1) printf("Книга не найдена, возврат в меню.\n");
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
				fprintf(LogFile, "\n%s;%s;\"AuthorSerch\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if (Case==12){	// ПРОСМОТР ВСЕХ СТУДЕНТОВ ПО НОМЕРУ КНИГИ
		printf("Введите ISBN книги: ");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("Поиск книги...\n");
		int i=0; int T=-1;
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("Книга найдена...\n\n"); T=i; break;
			}
		}
		if (T==-1) printf("Книга не найдена, возврат в меню.\n");
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
				// Найти строку с нужным номером книги
				char Buff[1024];
				SBFile=fopen("student_books.csv", "r"); // Открываем файл для поиска студентов у данной книги
				int BooksTrigger=0;
				char ArrZach[SBLineCount][7]; // Создаем массив по количеству строк
				char Date[SBLineCount][20];	// Массив для даты
				int ArrCounter=0;
				for (i=0; i<SBLineCount;i++){
					fgets(Buff, 1024,SBFile);
					char CheckZach[7];
					long long CheckISBN;
					char CheckDate[20];
					CheckISBN=atoll(strtok(Buff,";")); // Запоминаем номер ИСБН
					strcpy(CheckZach,strtok(NULL,";"));	// записываем номер зачетки
					strcpy(CheckDate,strtok(NULL,";"));
						if (CheckISBN==Books[T].ISBN){  // Если в файле есть такой номер книги
						strcpy(ArrZach[ArrCounter],CheckZach);
						strcpy(Date[ArrCounter],CheckDate);
						ArrCounter++;
					}
				}
				fclose(SBFile);
				
				if (ArrCounter==0){
					printf("Этой книги нет на руках.\n");
				}
				else{
					FILE *fp_Students=fopen("students.csv", "r");
					if (fp_Students==NULL) printf("Ошибка: Файл с книгами не может быть открыт.");
					else{
						int SLineCount=0;
						while(! feof(fp_Students)){
							if (fgetc(fp_Students)=='\n')
								SLineCount++;
						}
						SLineCount++;
						fclose(fp_Books);
						
						fp_Students=fopen("students.csv", "r");
						if (fp_Students==NULL) printf("Ошибка: Файл студентов не может быть открыт.");
						else{
							printf ("Эта книга на руках у:\n");
							for (i=0; i<SLineCount;i++){
								fgets(Buff, 1024,fp_Books); //Считываем строку
								char Zach[7];
								strcpy(Zach,strtok(Buff,";"));
								int k=0;
								for (k=0; k<=ArrCounter;k++){
									if(strcmp(Zach, ArrZach[k])==0){
										printf("%s %s %s\nДата возврата:%s\n\n",strtok(NULL,";"),strtok(NULL,";"),strtok(NULL,";"), Date[k]);
									}
								}
							}
							fclose(fp_Books);	
						}
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
				fprintf(LogFile, "\n%s;%s;\"CheckStudentsWithBook\"",Time,Login);
				fclose(LogFile);
			}
	}
}
}
}


