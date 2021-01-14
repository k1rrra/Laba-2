// Лабораторная работа №9
// Вариант 1

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 
#include "windows.h"
#include <locale>
#include <iostream>
#include <io.h>

using namespace std;

FILE* source;						// Файл источник (F1.txt)
FILE* target;						// Файл для результата задания (F2.txt)
const int MAXLINESIZE = 255;		// Максимальная длина строки

/* Задание 1 */
void task_1() {
	source = fopen("F1.txt", "r");		// Открытие файла F1 для чтения
	target = fopen("F2.txt", "w");		// Открытие файла F2 для записи
	char buff[MAXLINESIZE];	

	int counter = 1;
	// Пока не конец файла считываются строки файла F1 и проверяется четность строк счетчиком counter
	while (!feof(source)) {
		fgets(buff, MAXLINESIZE, source);
		if (counter % 2 == 0) {
			fputs(buff, target);
		}
		counter++;
	}

	fclose(source);
	fclose(target);
}

/* Задание 2 */
void task_2() {
	source = fopen("F1.txt", "rb");		// Открытие файла на чтение как двоичного
	fseek(source, 0, SEEK_END);			// Перемещение указателя в файле на его конец
	int size1 = ftell(source);			// ftell возвращает текущее значение указателя в виде количества байт
	fclose(source);

	target = fopen("F2.txt", "rb");
	fseek(target, 0, SEEK_END);
	int size2 = ftell(target);
	fclose(target);

	cout << "> Размер файла F1.txt: " << size1 << " МБ" << endl << "> Размер файла F2.txt: " << size2 << " МБ" << endl;
}

void main() {
	setlocale(LC_ALL, "russian");
	task_1();
	task_2();
}