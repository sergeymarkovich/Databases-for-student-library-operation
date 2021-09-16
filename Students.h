#ifndef STUDENTS_H
#define STUDENTS_H

void Students(char Login[]);

struct Student{
	
	char Valid[7]; // Номер зачетной книжки 6 символов и конец строки
	char Surname[32]; // Фамилия
	char Name[32];
	char patronymic[32]; // Отчество
	char Fackultet[5]; // Факультет - несколько символов и конец строки
	char Spec[128]; // Специальность
};


#endif
