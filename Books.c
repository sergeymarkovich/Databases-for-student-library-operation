#include "Books.h"
#include "students.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
/*
��� ���������� ����� ��� ������ � ������� "book.csv" � ���-�� ��� ���, ����� ��������� (��������� 1)
*/


void Books(char Login[]) 
{
	char Buff[1024];
	int Case=0;	// ������� �� ����� ��������
	int BackUpTrigger=0; // ����������, ������� �� ���� �������� ���� ����� ������
	FILE *fp_Books=fopen("books.csv", "r");
	if (fp_Books==NULL) printf("������: ���� � ������� �� ����� ���� ������.");
	else{
		
int LineCount=0;		// ��� ���������� ���� ������ ����, �� ��������� ����
while(! feof(fp_Books)){	// � ������� ���������� ����� � ��� (���������� ��������� ������ +1)
	if (fgetc(fp_Books)=='\n')
		LineCount++;
}
LineCount++; // �� ����� "+1"
fclose(fp_Books); // ��������� ����

struct Book *Books; // � ����� ������� ������ �������� ������ ����� (��������� � Books.h)
Books=(struct Book*)malloc(sizeof(struct Book)); // �������� ������ ��� ������ �����
int i=0;
fp_Books=fopen("books.csv", "r"); // ...��������� ���� ����� ������� ����������
for (i=0; i<LineCount;i++){ // � ��������� ���
	int k=0;
	fgets(Buff, 1024,fp_Books); //��������� ������
												// strtok -  ��������n ������ �� ���� ������� (;)
	Books[i].ISBN=atoll(strtok(Buff,";")); 		// atoll - ������������� atoi ��� ��������� �����
	strcpy(Books[i].Author,strtok(NULL,";"));   // strcpy - �������� ���������� �� ������ ���������� � ������ (������� ��������� �������� ���������� ����� �� ����������)
	strcpy(Books[i].Name,strtok(NULL,";"));
	Books[i].NumAll=atoi(strtok(NULL,";"));
	Books[i].NumUsed=atoi(strtok(NULL,"\n"));
	Books=(struct Book*)realloc(Books ,(i+2)*sizeof(struct Book)); //�������� ������ ��� ��������� ����������
}
fclose(fp_Books);

printf("���������� ��������\n����������:\n0 - �����\n1 - �������� �������\n2 - �������� ����� �����\n3 - ������� �����\n4 - ��������� � �����\n5 - ������������� ���������� � �����\n6 - �������� ���������� ����\n7 - ������ �����\n8 - ������� �����\n9 - C������ �����\n10 - ��������� �����\n11 - ����� �� ������\n12 - ���������� � ���� ����� �� �����\n");

while (1){
	
	scanf("%d", &Case);  // ���������� ������ ���������� - ����������� �����
	printf("\n");
	if (Case==0){	// ����� �� ��������� � ����������� ���������
		printf("��������� ���� ������...\n");
		FILE *fp_Books=fopen("books.csv", "w"); // ��������� ���� ��� ��� ������
		if (fp_Books==NULL) printf("������: ���� � ������� �� ����� ���� ������.");
		else{
			for(i=0; i<LineCount;i++){
			if (Books[i].ISBN!=0) {
			fprintf(fp_Books,"%lli;%s;%s;%d;%d", Books[i].ISBN,Books[i].Author, Books[i].Name, Books[i].NumAll, Books[i].NumUsed);
			if(i!=LineCount-1) fprintf(fp_Books,"\n");
			}
			}
			printf("��������� �������, ��������� ������.\n");
			fclose(fp_Books);
			char c=getchar();
			FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if (Case==1){	// ����� ���������� �� ���� ������
		struct Book BuffBook; // ������� ������� - ����� ������ ��� ������������ ���� �������.
		int s=0; // ���������� ������		��������� ���������� ���������!!!!
		for(i=0; i<LineCount; i++){
			for(s=0; s<LineCount-1; s++){
				if (Books[s].ISBN>Books[s+1].ISBN){
					
					//���������� ���� ����� � �����
					BuffBook.ISBN=Books[s].ISBN;
					strcpy(BuffBook.Author,Books[s].Author);
					strcpy(BuffBook.Name,Books[s].Name);
					BuffBook.NumAll=Books[s].NumAll;
					BuffBook.NumUsed=Books[s].NumUsed;
					
					//�������������� ��������� �� ������� ����� �� �� �����
					Books[s].ISBN=Books[s+1].ISBN;
					strcpy(Books[s].Author,Books[s+1].Author);
					strcpy(Books[s].Name,Books[s+1].Name);
					Books[s].NumAll=Books[s+1].NumAll;
					Books[s].NumUsed=Books[s+1].NumUsed;
					
					//���������� ����� �� ������ �� ����� �����
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
			if (Books[i].ISBN!=0) printf("%lli %s %s %d %d\n", Books[i].ISBN,Books[i].Author, Books[i].Name, Books[i].NumAll, Books[i].NumAll-Books[i].NumUsed); // lli - �������������� ��� long long ����
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if (Case==2){	// �������� ����� �����
		while (1){
			printf("�������� ����� �����:\n������� �� ISBN:");
			unsigned long long ISBN;
			scanf("%lli", &ISBN);
			
			int Error=0;
			for(i=0; i<LineCount; i++) {// �������� ���� �� ��� ����� ��� � ����
				if(Books[i].ISBN==ISBN){
					printf("������, ����� ISBN ��� ������������.\n"); Error=1; break;
					}
			}
			if (Error==1) break;
			
			int k=0;
			int A;
			A=getchar(); // ������-�� � ������ ������� �������� ������� ������ ������ ������ ���
			printf("������� ������:");
			char Author[128]; k=0;
			SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
			A=getchar();
			while (A != '\n'){
				Author[k]=A;
				k++;
				A=getchar();
			}
			SetConsoleCP(866); 	// ������ ��������� ������� �����
			Author[k]='\0';
			
			printf("������� ��������:");
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
			
			printf("������� ���������� ����:");
			int Count;
			scanf("%d", &Count);
			
			LineCount++; 	// � ������� ��� ������ � ��� �� ���� ����� ������
			Books=(struct Book*)realloc(Books ,(LineCount)*sizeof(struct Book));
			Books[LineCount-1].ISBN=ISBN;
			Books[LineCount-1].NumAll=Count;
			Books[LineCount-1].NumUsed=0;
			strcpy(Books[LineCount-1].Author, Author);
			strcpy(Books[LineCount-1].Name, Name);
			
			break;
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if(Case==3){	// ������� �����
		printf("������� ISBN ����� ��� ��������:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("����� �����...\n");
		int i=0; int T=-1; // T - �������� �� ����������
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN){
				printf("����� �������...\n���������� � ��������....\n"); T=i; break;
			}
		}
		if (T==-1) printf("����� �� �������, ������� � ����.\n");
		else{
			// ������� ���� � ��������
			FILE *SBFile=fopen("student_books.csv", "r"); // ��������� ���� ����� ��������� ���������� ����� (�������� � book.c)
			if (SBFile==NULL) printf("������: ���� c �������� �� ����� ���� ������.");
			else{	
				int SBLineCount=0;
				while(! feof(SBFile)){
					if (fgetc(SBFile)=='\n')
						SBLineCount++;
				}
				SBLineCount++; 
				fclose(SBFile);
				// ����� ������ � ������ ������� �������
				char Buff[1024];
				SBFile=fopen("student_books.csv", "r"); // ��������� ���� ��� ������ ���� � ������� ��������
				int BooksTrigger=0;
				for (i=0; i<SBLineCount;i++){
					fgets(Buff, 1024,SBFile);
					long long ISBN;
					ISBN=atoll(strtok(Buff,";"));	// ���������� ����� �����
						if (Books[T].ISBN==ISBN){  // ���� � ����� ���� ����� ����� �������, �� � �������� ���� �����.
						BooksTrigger=1;
						break;	// ��������� ����
					}
				}
				fclose(SBFile);
				// ���� ������ ���� ������� ������, ���� ��� - ������� ��������
				if (BooksTrigger==0){
					Books[T].ISBN=0;// ���������� ������ ��� ���������
					printf("������� �������!\n\n");
				}
				else printf("������ ����� ��������� �� �����!\n");
			}
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if(Case==4){	// ������� ���������� �� �����
		printf("������� ISBN �����:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("����� �����...\n");
		int i=0; int T=-1; // T - �������� �� ����������
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("����� �������...\n"); T=i; break;
			}
		}
		if (T==-1) printf("����� �� �������, ������� � ����.\n");
		else{
			printf("ISBN: %lli\n�����: %s\n��������: %s\n���� � ����������: %d\n���� �� �����: %d\n", Books[T].ISBN,Books[T].Author, Books[T].Name, Books[T].NumAll, Books[T].NumUsed);
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if(Case==5){	// ������������� ���������� �� ����� 
		printf("������� ISBN �����:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("����� �����...\n");
		int i=0; int T=-1; // T - �������� �� ����������
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("����� �������...\n\n"); T=i; break;
			}
		}
		if (T==-1) printf("����� �� �������, ������� � ����.\n");
		else{
			printf("���������� �� �����:\n�����: %s\n��������: %s\n\n", Books[T].Author, Books[T].Name);
			printf("������� ����� ��������:");
			char Name[128];
			SetConsoleCP(1251);
			scanf("%s", &Name);
			SetConsoleCP(866);
			printf("������� ������:");
			char Author[128];
			SetConsoleCP(1251);
			scanf("%s", &Author);
			SetConsoleCP(866);
			strcpy(Books[T].Name,Name);
			strcpy(Books[T].Author, Author);
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if(Case==6){	// �������� ���������� ���� � ����������
		printf("������� ISBN �����:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("����� �����...\n");
		int i=0; int T=-1; // T - �������� �� ����������
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("����� �������...\n\n"); T=i; break;
			}
		}
		if (T==-1) printf("����� �� �������, ������� � ����.\n");
		else{
			printf("���������� �� �����:\n�����: %s\n��������: %s\n\n", Books[T].Author, Books[T].Name);
			printf("������� ����� ���������� ����:");
			int Count=0;
			scanf("%d", &Count);
			Books[T].NumAll=Count;
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if(Case==7){	// ������ �����
		printf("������� ISBN �����:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("����� �����...\n");
		int i=0; int T=-1;
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("����� �������...\n\n"); T=i; break;
			}
		}
		if (T==-1) printf("����� �� �������, ������� � ����.\n");
		else{
			printf("��������: %s �����: %s\n", Books[T].Name, Books[T].Author);
			if (Books[T].NumUsed==Books[T].NumAll){
				printf("������. ������������ ����.\n");
				printf("��� ����� ����� �����:\n");
				FILE *SBFile=fopen("student_books.csv", "r"); // ��������� ���� ����� ��������� ���������� ����� (�������� � book.c)
				if (SBFile==NULL) printf("������: ���� �� ����� ���� ������.");
				else{
					int SBLineCount=0;		
					while(! feof(SBFile)){	
						if (fgetc(SBFile)=='\n')
							SBLineCount++;
					}
					SBLineCount++; 
					fclose(SBFile);
					
					SBFile=fopen("student_books.csv", "r");
					char StringArr[SBLineCount][64]; // �������� ���������� ����� � ����������� ������
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
				printf("������� ����� ��������: ");
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
				printf("������� ���� ����� ����� � ������� \"����.�����.���\": ");
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
				
				FILE *SBFile=fopen("student_books.csv", "r"); // ��������� ���� ����� ��������� ���������� ����� (�������� � book.c)
				if (SBFile==NULL) printf("������: ���� �� ����� ���� ������.");
				else{
					int SBLineCount=0;		
					while(! feof(SBFile)){	
						if (fgetc(SBFile)=='\n')
							SBLineCount++;
					}
					SBLineCount++; 
					fclose(SBFile);
					
					SBFile=fopen("student_books.csv", "r");
					char StringArr[SBLineCount][64]; // �������� ���������� ����� � ����������� ������
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
					printf("����� ������. ������� � ����.\n");
					Books[T].NumUsed++;
				}
			}
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if(Case==8){	// ������� ����� � ����������
		printf("������� ISBN �����:");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("����� �����...\n");
		int i=0; int T=-1;
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("����� �������...\n\n"); T=i; break;
			}
		}
		if (T==-1) printf("����� �� �������, ������� � ����.\n");
		else{
			printf("������� ����� ��������: ");
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
				
				FILE *SBFile=fopen("student_books.csv", "r"); // ��������� ���� ����� ��������� ���������� ����� (�������� � book.c)
				if (SBFile==NULL) printf("������: ���� �� ����� ���� ������.");
				else{
					int SBLineCount=0;		
					while(! feof(SBFile)){	
						if (fgetc(SBFile)=='\n')
							SBLineCount++;
					}
					SBLineCount++; 
					fclose(SBFile);
					SBFile=fopen("student_books.csv", "r");
					char StringArr[SBLineCount][64]; // �������� ���������� ����� � ����������� ������
					char Buff[64];					// ����� ��������� ������
					for (i=0; i<SBLineCount; i++){
						fgets(Buff, 1024,SBFile);
						strcpy(StringArr[i],Buff); // ��������� ������
						long long CheckISBN=atoll(strtok(Buff,";")); // ������ �� �� ������������
						char CheckZach[7];
						strcpy(CheckZach, strtok(NULL,";"));
						
						if (ISBN!=CheckISBN || strcmp(Zach,CheckZach)==0)	// � ���� ��� ������� ������ - �������� ��.
						strcpy(StringArr[i],"NULL");
					}
					fclose(SBFile);		
					SBFile=fopen("student_books.csv", "w");
					for(i=0;i<SBLineCount;i++){
						char NULLS[5];
						strcpy(NULLS,"NULL");
						
						if(strcmp(StringArr[i],NULLS)!=0){
							fprintf(SBFile,"%s\n",StringArr[i]);	// ���������� ��� ������ ����� ����������
						}
						
					}
					fclose(SBFile);
					printf("����� ������. ������� � ����.\n");
					Books[T].NumUsed++;
				}
			}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if(Case==9){	// ��������� �����
		time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
		char Way[64]="books_"; // ������� ���������� ��� ���� ������ ������� ������ ���� ������� ����� �������� ������ �������� �����
		char Time[32];
		strcpy(Time,ctime(&CurTime));
		Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
		i=0;
		while (Time[i]!='\0'){	//�������� ������ �� ������������ ������� � ������� �� ������ ���������
			if (Time[i]==':' || Time[i]==' ') Time[i]='_';
			i++;
		}
		strcat(Way,Time);
		strcat(Way,".csv");
		FILE *BackFile=fopen(Way, "w"); // ������� ���� ��� ������
		if (BackFile==NULL) printf("������: ���� � ������� �� ����� ���� ������.");
		for(i=0; i<LineCount; i++){
			if (Books[i].ISBN!=0) fprintf(BackFile,"%lli;%s;%s;%d;%d", Books[i].ISBN,Books[i].Author, Books[i].Name, Books[i].NumAll, Books[i].NumUsed);
			if(i!=LineCount-1 && Books[i].ISBN!=0) fprintf(BackFile,"\n"); // ����� �������� ������� �������� ������ � �����
		}
		fclose(BackFile);
		printf("������� ���������\n");
		printf("��� �����: %s\n", Way);
		printf("������� � ����\n");
		
	FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if(Case==10){	// ��������� �� ������
		printf("������� �������� �����-������: ");
		char Way[64];
		scanf("%s", &Way);
		FILE *BackFile=fopen(Way, "r");
		if (BackFile==NULL) printf("������: ���� ���������� �� ����� ���� ������.\n");
		else{	
			LineCount=0;				//  ������� ������ � ����� ������
			while(! feof(BackFile)){	// 	� ����� �� �� �����, ��� � � ������ ���������, ��������� ������ ��������� � �������� ����.
				if (fgetc(BackFile)=='\n')
					LineCount++;
			}
			LineCount++; 
			fclose(BackFile); 
			FILE *BackFile=fopen(Way, "r");
			struct Book BackBooks[LineCount]; // �� ��� ��� +12 �� �����, ���-��� ����� ����� �� �������� � �������� �������������
			int i=0;
			for (i=0; i<LineCount;i++){ // � ��������� ���
				int k=0;
				fgets(Buff, 1024,BackFile); 
				BackBooks[i].ISBN=atoll(strtok(Buff,";")); 	
				strcpy(BackBooks[i].Author,strtok(NULL,";"));
				strcpy(BackBooks[i].Name,strtok(NULL,";"));
				BackBooks[i].NumAll=atoi(strtok(NULL,";"));
				BackBooks[i].NumUsed=atoi(strtok(NULL,"\n"));
			}
			fclose(BackFile);
			
			FILE *fp_Books=fopen("books.csv", "w"); // ��������� ���� ��� ��� ������
			if (fp_Books==NULL) printf("������: ���� � ������� �� ����� ���� ������.");
			else{
				for(i=0; i<LineCount;i++){
				fprintf(fp_Books,"%lli;%s;%s;%d;%d", BackBooks[i].ISBN,BackBooks[i].Author, BackBooks[i].Name, BackBooks[i].NumAll, BackBooks[i].NumUsed);
				if(i!=LineCount-1) fprintf(fp_Books,"\n");
				}
				printf("����� ��������. ���������� ����������\n");
				char c=getchar();
			break;
			}
		}
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if(Case==11){	// ����� �� ������
		printf("������� ������:");
		char Author[128];
		char A;
		int k=0;
		SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
		A=getchar();
		A=getchar();
		while (A != '\n'){
			Author[k]=A;
			k++;
			A=getchar();
		}
		SetConsoleCP(866); 	// ������ ��������� ������� �����
		Author[k]='\0';
		printf("����� ����...\n");
		int i=0; int T=-1;
		for (i=0;i<LineCount;i++){
			if(strcmp(Author, Books[i].Author)==0 && Books[i].ISBN!=0){	
				T=i;
				printf("����� ISBN: %lli ��������: %s ���������� � ����������: %d\n",Books[i].ISBN, Books[T].Name, Books[i].NumAll);
			}
		}
		if (T==-1) printf("����� �� �������, ������� � ����.\n");
		FILE *LogFile=fopen("library.log", "a");
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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
	else if (Case==12){	// �������� ���� ��������� �� ������ �����
		printf("������� ISBN �����: ");
		long long ISBN;
		scanf("%lli", &ISBN);
		printf("����� �����...\n");
		int i=0; int T=-1;
		for (i=0;i<LineCount;i++){
			if(ISBN==Books[i].ISBN && Books[i].ISBN!=0){
				printf("����� �������...\n\n"); T=i; break;
			}
		}
		if (T==-1) printf("����� �� �������, ������� � ����.\n");
		else{
			FILE *SBFile=fopen("student_books.csv", "r"); // ��������� ���� ����� ��������� ���������� ����� (�������� � book.c)
			if (SBFile==NULL) printf("������: ���� �� ����� ���� ������.");
			else{	
				int SBLineCount=0;		
				while(! feof(SBFile)){	
					if (fgetc(SBFile)=='\n')
						SBLineCount++;
				}
				SBLineCount++; 
				fclose(SBFile);
				// ����� ������ � ������ ������� �����
				char Buff[1024];
				SBFile=fopen("student_books.csv", "r"); // ��������� ���� ��� ������ ��������� � ������ �����
				int BooksTrigger=0;
				char ArrZach[SBLineCount][7]; // ������� ������ �� ���������� �����
				char Date[SBLineCount][20];	// ������ ��� ����
				int ArrCounter=0;
				for (i=0; i<SBLineCount;i++){
					fgets(Buff, 1024,SBFile);
					char CheckZach[7];
					long long CheckISBN;
					char CheckDate[20];
					CheckISBN=atoll(strtok(Buff,";")); // ���������� ����� ����
					strcpy(CheckZach,strtok(NULL,";"));	// ���������� ����� �������
					strcpy(CheckDate,strtok(NULL,";"));
						if (CheckISBN==Books[T].ISBN){  // ���� � ����� ���� ����� ����� �����
						strcpy(ArrZach[ArrCounter],CheckZach);
						strcpy(Date[ArrCounter],CheckDate);
						ArrCounter++;
					}
				}
				fclose(SBFile);
				
				if (ArrCounter==0){
					printf("���� ����� ��� �� �����.\n");
				}
				else{
					FILE *fp_Students=fopen("students.csv", "r");
					if (fp_Students==NULL) printf("������: ���� � ������� �� ����� ���� ������.");
					else{
						int SLineCount=0;
						while(! feof(fp_Students)){
							if (fgetc(fp_Students)=='\n')
								SLineCount++;
						}
						SLineCount++;
						fclose(fp_Books);
						
						fp_Students=fopen("students.csv", "r");
						if (fp_Students==NULL) printf("������: ���� ��������� �� ����� ���� ������.");
						else{
							printf ("��� ����� �� ����� �:\n");
							for (i=0; i<SLineCount;i++){
								fgets(Buff, 1024,fp_Books); //��������� ������
								char Zach[7];
								strcpy(Zach,strtok(Buff,";"));
								int k=0;
								for (k=0; k<=ArrCounter;k++){
									if(strcmp(Zach, ArrZach[k])==0){
										printf("%s %s %s\n���� ��������:%s\n\n",strtok(NULL,";"),strtok(NULL,";"),strtok(NULL,";"), Date[k]);
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
			if (LogFile==NULL) printf("������: ���� ���� �� ����� ���� ������.");
			else
			{
				time_t CurTime=time(NULL); // ������� ���������� ��� ��������� ������� � ����������� �� ������� �����
				char Time[32];
				strcpy(Time,ctime(&CurTime));
				Time[strlen(Time)-1]='\0';	// �.�. �time ���������� ����� � ��������� ������ � ����� - ����� ������� �������
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


