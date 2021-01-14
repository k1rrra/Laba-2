// ������������ ������ �9
// ������� 1

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 
#include "windows.h"
#include <locale>
#include <iostream>
#include <io.h>

using namespace std;

FILE* source;						// ���� �������� (F1.txt)
FILE* target;						// ���� ��� ���������� ������� (F2.txt)
const int MAXLINESIZE = 255;		// ������������ ����� ������

/* ������� 1 */
void task_1() {
	source = fopen("F1.txt", "r");		// �������� ����� F1 ��� ������
	target = fopen("F2.txt", "w");		// �������� ����� F2 ��� ������
	char buff[MAXLINESIZE];	

	int counter = 1;
	// ���� �� ����� ����� ����������� ������ ����� F1 � ����������� �������� ����� ��������� counter
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

/* ������� 2 */
void task_2() {
	source = fopen("F1.txt", "rb");		// �������� ����� �� ������ ��� ���������
	fseek(source, 0, SEEK_END);			// ����������� ��������� � ����� �� ��� �����
	int size1 = ftell(source);			// ftell ���������� ������� �������� ��������� � ���� ���������� ����
	fclose(source);

	target = fopen("F2.txt", "rb");
	fseek(target, 0, SEEK_END);
	int size2 = ftell(target);
	fclose(target);

	cout << "> ������ ����� F1.txt: " << size1 << " ��" << endl << "> ������ ����� F2.txt: " << size2 << " ��" << endl;
}

void main() {
	setlocale(LC_ALL, "russian");
	task_1();
	task_2();
}