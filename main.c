#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "string.h"
#include "time.h"
// ����� ����������, ������� �� �������� ����. ��������� � ����� �����������.
#include "Books.h"
#include "students.h"

/*
	
*/

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Russian");
	
	char A;		// ���������� ��� ���������� � �������
	int Books_R=0;	// ����� ��� ������ � �������
	int Students_R=0;	// ����� ��� ������ �� ����������
	
	FILE *fp_users=fopen("users.csv", "r"); // ��������� ���� ����� ��������� ���������� ����� (�������� � book.c)
	if (fp_users==NULL) printf("������: ���� � �������������� �� ����� ���� ������.");
	else{	
		int LineCount=0;		
		while(! feof(fp_users)){	
			if (fgetc(fp_users)=='\n')
				LineCount++;
		}
		LineCount++; 
		fclose(fp_users);
		while (1){
			printf("���������� ���� ��. �������\n\n��������� �����������\n\n");
			printf("������� �����: ");
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
			
			printf("������� ������: ");
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
			fp_users=fopen("users.csv", "r"); // ...��������� ���� ��� ��������� ���� �����/������
			
			int i=0;
			for (i=0; i<LineCount;i++){
				fgets(Buffer, 1024,fp_users);
				char CheckLogin[128]; // ���������� ��� �������� ������
				char CheckPassword[128]; 	// � ��� ��� ������
				strcpy(CheckLogin,strtok(Buffer,";"));
				strcpy(CheckPassword,strtok(NULL,";"));
				if (strcmp(Password, CheckPassword)==0 && strcmp(Login, CheckLogin)==0){  // ���� ������ � ������ ��������� � ����, ��� � �����
					Students_R=atoi(strtok(NULL,";"));	// ��������� �����
					Books_R=atoi(strtok(NULL,";"));
					break;
				}
			}
			fclose(fp_users);
			
			if (Students_R==1 && Books_R==1){
				int Case;
				while(1){
					printf("\n�������� ��������:\n0 - �����\n1 - ������ � �������\n2 - ������ �� ����������\n");
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
				printf("������. �������� ����� ��� ������.\n");
			}
		}
	}
}
