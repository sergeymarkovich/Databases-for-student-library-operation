#ifndef STUDENTS_H
#define STUDENTS_H

void Students(char Login[]);

struct Student{
	
	char Valid[7]; // ����� �������� ������ 6 �������� � ����� ������
	char Surname[32]; // �������
	char Name[32];
	char patronymic[32]; // ��������
	char Fackultet[5]; // ��������� - ��������� �������� � ����� ������
	char Spec[128]; // �������������
};


#endif
