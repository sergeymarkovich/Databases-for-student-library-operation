
#include "Books.h"
#include "students.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

void Students(char Login[]){ // ������ ���� � ������� ��� ����� ������
	char Buff[1024];
	int Case=0;	
	int BackUpTrigger=0;
	FILE *fp_Students=fopen("students.csv", "r");
	if (fp_Students==NULL) printf("������: ���� ��������� �� ����� ���� ������.");
	else{
		
int LineCount=0;		// ��� ���������� ���� ������ ����, �� ��������� ����
while(! feof(fp_Students)){	// � ������� ���������� ����� � ��� (���������� ��������� ������ +1)
	if (fgetc(fp_Students)=='\n')
		LineCount++;
}
LineCount++;
fclose(fp_Students); // ��������� ����
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

printf("������ �� ������� ���������\n����������:\n0 - �����\n1 - �������� ��������\n2 - ������� ��������\n3 - ������������� ���������� �� ��������\n4 - ���������� ����������\n5 - ��������� �����\n6 - ��������� �����\n7 - ����� �� �������\n8 - �������� ���� ��������\n");

while(1){
	
	scanf("%d", &Case);
	printf("\n");  
	if (Case==0){	// ����� �� ��������� � ����������� ���������
		printf("��������� ���� ������...\n");
		FILE *fp_Students=fopen("students.csv", "w"); // ��������� ���� ��� ��� ������
		if (fp_Students==NULL) printf("������: ���� � ������� �� ����� ���� ������.");
		else{
			for(i=0; i<LineCount;i++)
				if (strcmp("NULL", Students[i].Valid)!=0) fprintf(fp_Students,"%s;%s;%s;%s;%s;%s",Students[i].Valid,Students[i].Surname,Students[i].Name,Students[i].patronymic,Students[i].Fackultet,Students[i].Spec);
				
			fclose(fp_Students);
			printf("��������� �������, ��������� ������.\n");
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
				fprintf(LogFile, "\n%s;%s;\"StudentsEndOfWork\"",Time,Login);
				fclose(LogFile);
			}
		return ;
		}
	}
	else if (Case==1){	// �������� ������ ��������
		while (1){
			printf("�������� ������ ��������:\n������� ����� ����.������:");
			char Valid[7];
			char A;
			int k=0;
			A=getchar();
			SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
			A=getchar();
			while (A != '\n'){
				Valid[k]=A;
				k++;
				A=getchar();
			}
			SetConsoleCP(866); 	// ������ ��������� ������� �����
			Valid[k]='\0';
			int Error=0;
			for(i=0; i<LineCount; i++) {// �������� ���� �� ��� ����� ��� � ����
				if(strcmp(Valid, Students[i].Valid)==0){
					printf("������, ������� � ����� �������� ��� ���� � ����.\n"); Error=1; break;
					}
			}
			if (Error==1) break;
			else{
				k=0;
				printf("������� ���:");
				char Name[128]; k=0;
				SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
				A=getchar();
				while (A != '\n'){
					Name[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// ������ ��������� ������� �����
				Name[k]='\0';
				
				printf("������� �������:");
				char Surname[128]; k=0;
				SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
				A=getchar();
				while (A != '\n'){
					Surname[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// ������ ��������� ������� �����
				Surname[k]='\0';
				
				printf("������� ��������:");
				char patronymic[128]; k=0;
				SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
				A=getchar();
				while (A != '\n'){
					patronymic[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// ������ ��������� ������� �����
				patronymic[k]='\0';
				
				printf("������� ���������:");
				char Fackultet[128]; k=0;
				SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
				A=getchar();
				while (A != '\n'){
					Fackultet[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// ������ ��������� ������� �����
				Fackultet[k]='\0';
				
				printf("������� �������������:");
				char Spec[128]; k=0;
				SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
				A=getchar();
				while (A != '\n'){
					Spec[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// ������ ��������� ������� �����
				Spec[k]='\0';
				
				LineCount++; 	
				Students=(struct Student*)realloc(Students ,(LineCount)*sizeof(struct Student));
				strcpy(Buff,"\0"); 	//��������� ������� ������ ����� � ����� ��� ���� ���������
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
				printf("������� ��������. ������� � ����.\n");
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
				fprintf(LogFile, "\n%s;%s;\"AddStudent\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==2){	// ������� 
		printf("������� ����� ������� ��� ��������:");
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
		printf("����� ��������...\n");
		int i=0; int T=-1;
		int Error=0;
		for(i=0; i<LineCount; i++) {
			if(strcmp(Valid, Students[i].Valid)==0){
				printf("������� ������...\n"); T=i; break;		
				}
		}
		if (T==-1) printf("������� �� ������, ������� � ����.\n");
		else{
			// ������� ���� � ��������
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
				// ����� ������ � ������ ������� �������
				char Buff[1024];
				SBFile=fopen("student_books.csv", "r"); // ��������� ���� ��� ������ ���� � ������� ��������
				int BooksTrigger=0;
				for (i=0; i<SBLineCount;i++){
					fgets(Buff, 1024,SBFile);
					char Valid[7];
					strtok(Buff,";"); // ���������� ����� �����
					strcpy(Valid,strtok(NULL,";"));	// ���������� ����� �������
						if (strcmp(Valid,Students[T].Valid)==0){  // ���� � ����� ���� ����� ����� �������, �� � �������� ���� �����.
						BooksTrigger=1;
						break;	// ��������� ����
					}
				}
				fclose(SBFile);
				// ���� ������ ���� ������� ������, ���� ��� - ������� ��������
				if (BooksTrigger==0){
					strcpy(Students[T].Valid,"NULL");// ���������� ������ ��� ���������
					printf("������� �������!\n\n");
				}
				else printf("� ������� �������� ���� �����!\n");
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
				fprintf(LogFile, "\n%s;%s;\"DelStudent\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==3){	// ������������� ���������� 
		printf("������� ����� ������� ��� ��������������:");
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
		printf("����� ��������...\n");
		int i=0; int T=-1;
		int Error=0;
		for(i=0; i<LineCount; i++) {
			if(strcmp(Valid, Students[i].Valid)==0){
				printf("������� ������.\n"); T=i; break;		
				}
		}
		if (T==-1) printf("������� �� ������, ������� � ����.\n");
		else{
			printf("���������� �� ��������:\n%s %s %s %s %s %s\n",Students[T].Valid,Students[T].Surname,Students[T].Name,Students[T].patronymic,Students[T].Fackultet,Students[T].Spec);
			printf("������� ���:");
				char Name[128]; k=0;
				SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
				A=getchar();
				while (A != '\n'){
					Name[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// ������ ��������� ������� �����
				Name[k]='\0';
				
				printf("������� �������:");
				char Surname[128]; k=0;
				SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
				A=getchar();
				while (A != '\n'){
					Surname[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// ������ ��������� ������� �����
				Surname[k]='\0';
				
				printf("������� ��������:");
				char patronymic[128]; k=0;
				SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
				A=getchar();
				while (A != '\n'){
					patronymic[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// ������ ��������� ������� �����
				patronymic[k]='\0';
				
				printf("������� ���������:");
				char Fackultet[128]; k=0;
				SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
				A=getchar();
				while (A != '\n'){
					Fackultet[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// ������ ��������� ������� �����
				Fackultet[k]='\0';
				
				printf("������� �������������:");
				char Spec[128]; k=0;
				SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
				A=getchar();
				while (A != '\n'){
					Spec[k]=A;
					k++;
					A=getchar();
				}
				SetConsoleCP(866); 	// ������ ��������� ������� �����
				Spec[k]='\0';
				
				strcpy(Students[T].Valid,Valid);  
				strcpy(Students[T].Surname,Surname);
				strcpy(Students[T].Name,Name);
				strcpy(Students[T].patronymic,patronymic);
				strcpy(Students[T].Fackultet,Fackultet);
				strcpy(Students[T].Spec,Spec);
				printf("�������� ��������� �������, ������� � ����.\n");
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
				fprintf(LogFile, "\n%s;%s;\"StudentEdit\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==4){
		printf("������� ����� �������:");
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
		printf("����� ��������...\n");
		int i=0; int T=-1;
		int Error=0;
		for(i=0; i<LineCount; i++) {
			if(strcmp(Valid, Students[i].Valid)==0){
				printf("������� ������.\n\n");T=i; break;		
				}
		}
		if (T==-1) printf("������� �� ������, ������� � ����.\n");
		else{
			printf("���������� �� ��������:\n����� �������: %s\n�������: %s\n���: %s\n��������: %s\n���������: %s\n������������:%s\n",Students[T].Valid,Students[T].Surname,Students[T].Name,Students[T].patronymic,Students[T].Fackultet,Students[T].Spec);
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
				fprintf(LogFile, "\n%s;%s;\"StudentInfo\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==5){	// ��������� �����
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
		FILE *BackFile=fopen(Way, "w"); // ������� ���� ��� ������
		if (BackFile==NULL) printf("������: ���� ���������� �� ����� ���� ������.");
		for(i=0; i<LineCount; i++){
			fprintf(BackFile,"%s;%s;%s;%s;%s;%s",Students[i].Valid,Students[i].Surname,Students[i].Name,Students[i].patronymic,Students[i].Fackultet,Students[i].Spec);
		//	if(i!=LineCount-1) fprintf(BackFile,"\n"); // ����� �������� ������� �������� ������ � �����
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
				fprintf(LogFile, "\n%s;%s;\"StudentBackUp\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==6){	// ��������� �� ������
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
			
			FILE *fp_Books=fopen("books.csv", "w"); // ��������� ���� ��� ��� ������
			if (fp_Books==NULL) printf("������: ���� � ������� �� ����� ���� ������.");
			else{
				for(i=0; i<LineCount;i++){
				if (strcmp("NULL", Students[i].Valid)!=0) fprintf(fp_Students,"%s;%s;%s;%s;%s;%s",Students[i].Valid,Students[i].Surname,Students[i].Name,Students[i].patronymic,Students[i].Fackultet,Students[i].Spec);
				if(i!=LineCount-1){fprintf(fp_Students,"\n");}
				}
				fclose(fp_Students);
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
				fprintf(LogFile, "\n%s;%s;\"LoadStudentBackUp\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if(Case==7){	// ����� �� �������
		printf("������� ������� ��������:");
		char Surname[128];
		char A;
		int k=0;
		SetConsoleCP(1251);  // ������ ��������� ������� ����� ��������� ������� ������� ���������
		A=getchar();
		A=getchar();
		while (A != '\n'){
			Surname[k]=A;
			k++;
			A=getchar();
		}
		SetConsoleCP(866); 	// ������ ��������� ������� �����
		Surname[k]='\0';
		printf("����� C�������...\n");
		int i=0; int T=-1;
		for (i=0;i<LineCount;i++){
			if(strcmp(Surname, Students[i].Surname)==0){	
				T=i;
				printf("%s %s %s\n����� �������: %s\n��������� � �������������: %s %s\n",Students[i].Surname,Students[i].Name,Students[i].patronymic,Students[i].Valid,Students[i].Fackultet,Students[i].Spec);
			}
		}
		if (T==-1) printf("������� �� ������, ������� � ����.\n");
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
				fprintf(LogFile, "\n%s;%s;\"StudentSerch\"",Time,Login);
				fclose(LogFile);
			}
	}
	else if (Case==8){	// �������� ���� ���� ��������
		printf("������� ����� �������:");
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
		printf("����� ��������...\n");
		int i=0; int T=-1;
		int Error=0;
		for(i=0; i<LineCount; i++) {
			if(strcmp(Valid, Students[i].Valid)==0){
				printf("������� ������.\n\n");T=i; break;		
				}
		}
		if (T==-1) printf("������� �� ������, ������� � ����.\n");
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
				// ����� ������ � ������ ������� �������
				char Buff[1024];
				SBFile=fopen("student_books.csv", "r"); // ��������� ���� ��� ������ ���� � ������� ��������
				int BooksTrigger=0;
				long long *ArrISBN;	// ������������ ������ � �������� ����
				char Date[SBLineCount][20];
				int ArrCounter=0;
				ArrISBN=(long long*)malloc(sizeof(long long));
				for (i=0; i<SBLineCount;i++){
					fgets(Buff, 1024,SBFile);
					char Valid[7];
					long long ISBN;
					char CheckDate[20];
					
					ISBN=atoll(strtok(Buff,";")); // ���������� ����� ����
					strcpy(Valid,strtok(NULL,";"));	// ���������� ����� �������
					strcpy(CheckDate,strtok(NULL,";"));
						if (strcmp(Valid,Students[T].Valid)==0){  // ���� � ����� ���� ����� ����� �������, �� ���������� ����� � ������
						ArrISBN=(long long*)realloc(ArrISBN ,(ArrCounter+2)*sizeof(long long));
						ArrISBN[ArrCounter]=ISBN;
						strcpy(Date[ArrCounter],CheckDate);
						ArrCounter++;
					}
				}
				fclose(SBFile);
				
				if (ArrCounter==0){
					printf("� �������� ��� ���� �� �����.\n");
				}
				else{
					FILE *fp_Books=fopen("books.csv", "r");
					if (fp_Books==NULL) printf("������: ���� � ������� �� ����� ���� ������.");
					else{
						int BLineCount=0;		
						while(! feof(fp_Books)){
							if (fgetc(fp_Books)=='\n')
								BLineCount++;
						}
						BLineCount++;
						fclose(fp_Books);
						
						fp_Books=fopen("books.csv", "r");
						printf ("����� �� �����:");
						for (i=0; i<BLineCount;i++){
							fgets(Buff, 1024,fp_Books); //��������� ������
							long long ISBN;
							ISBN=atoll(strtok(Buff,";"));
							int k=0;
							for (k=0; k<=ArrCounter;k++){
								if(ArrISBN[k]==ISBN) printf("%lli\n�����: %s\n�����: %s\n���� ��������: %s\n\n",ISBN,strtok(NULL,";"),strtok(NULL,";"), Date[k]);
							}
						}
						fclose(fp_Books);
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
				fprintf(LogFile, "\n%s;%s;\"AllBooksOFStudent\"",Time,Login);
				fclose(LogFile);
			}
	}
}
}
}
