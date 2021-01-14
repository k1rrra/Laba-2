#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 
#include "windows.h"
#include <locale>
#include <iostream>

using namespace std;

FILE* file;	// ��������� �� ����
int n;		// ���������� ������� � �����

/* ��������� "����������" */
struct Enrolee {
	char surname[50];			// �������
	char name[50];				// ���
	char patronymic[50];		// ��������
	int year;					// ��� ��������
	int mark_1;					// ������ ������������� ��������� (3)
	int mark_2;
	int mark_3;
	double avg_mark;			// ������� ����
};

/* ������������ ��������� */
Enrolee create() {
	Enrolee el;
	cout << "�������: ";
	cin >> el.surname;
	cout << "���: ";
	cin >> el.name;
	cout << "��������: ";
	cin >> el.patronymic;
	cout << "��� ��������: ";
	cin >> el.year;
	cout << "������ ������������� ���������:" << endl << "1 �������: ";
	cin >> el.mark_1;
	cout << "2 �������: ";
	cin >> el.mark_2;
	cout << "3 �������: ";
	cin >> el.mark_3;
	el.avg_mark = (el.mark_1 + el.mark_2 + el.mark_3) / 3;
	return el;
}

/* �������� ����� */
void createFile() {
	cout << "*������������ �����*" << endl;

	file = fopen("example.dat", "wb");
	
	if (file == NULL) {
		cout << "������ ��� �������� �����";
		exit(1);
	}
	
	cout << "��� ������ ������������ ����� ������� ������ �������" << endl;
	Enrolee el = create();											// �������� ������ ��������
	fwrite(&el, sizeof(Enrolee), 1, file);							// ������ ������ �������� � ����
	
	if (ferror(file) != NULL) {
		cout << "������ ��� ������ � ����";
		exit(2);
	}
	
	n = 1;															// ���������� ��������� ����� 1
	cout << "*���� �����������*" << endl;
	fclose(file);
}

/* ������ ����� */
void readFile() {
	cout << "############ ���������� ����� ##############" << endl << "############################################" << endl;
	file = fopen("example.dat", "rb");
	
	if (file == NULL) {
		cout << "������ ��� �������� �����";
		exit(1);
	}

	Enrolee el;
	int k = 0;
	while (!feof(file) && k < n) {
		fread(&el, sizeof(Enrolee), 1, file);

		if (ferror(file) != NULL) {
			cout << "������ ��� ������ �����";
			exit(4);
		}

		cout << "�������: " << el.surname << endl;
		cout << "���: " << el.name << endl;
		cout << "��������: " << el.patronymic << endl;
		cout << "��� ��������: " << el.year << endl;
		cout << "������ ������������� ��������� (3): " << el.mark_1 << " " << el.mark_2 << " " << el.mark_3 << endl;
		cout << "������� ����: " << el.avg_mark << endl;
		cout << "############################################" << endl;
		k++;
	}
	fclose(file);
	cout << "############################################" << endl;
}

/* ���������� ������ �������� � ���� */
void addFile() {
	cout << "*���������� ������ �������� � ����" << endl;
	Enrolee new_el;
	new_el = create();							// �������� ������ ��������
				
	char after_sur[50];							// �������, ����� ������� ����������� �������											
	cout << endl << "����� �������� � ����� �������� �������� ����� �������?" << endl;
	cin >> after_sur;

	file = fopen("example.dat", "rb");
	
	if (file == NULL) {
		cout << "������ ��� �������� �����";
		exit(1);
	}

	FILE* temp;									// ��������� ���� ��� ������ � ���� ������. ����� ����������������� � �������� ����, � �������� ���������
	temp = fopen("temp.dat", "wb");

	if (temp == NULL) {
		cout << "������ ��� �������� �����";
		exit(1);
	}

	bool isAdded = false;
	Enrolee el;
	for (int i = 1; i <= n; i++) {
		fread(&el, sizeof(Enrolee), 1, file);

		if (ferror(file) != NULL) {
			cout << "������ ��� ������ �����";
			exit(4);
		}

		fwrite(&el, sizeof(Enrolee), 1, temp);

		if (ferror(temp) != NULL) {
			cout << "������ ��� ������ �����";
			exit(2);
		}

		if (!strcmp(el.surname, after_sur)) {
			fwrite(&new_el, sizeof(Enrolee), 1, temp);

			if (ferror(temp) != NULL) {
				cout << "������ ��� ������ �����";
				exit(2);
			}

			isAdded = true;
		}
	}
	
	if (isAdded) {
		n++;
		cout << "������� ��������" << endl;
	} else cout << endl << "�������� � ��������� �������� �� �������" << endl;

	fclose(file);
	fclose(temp);
	remove("example.dat");
	rename("temp.dat", "example.dat");
}

/* �������� �������� �� ����� */
void deleteFile() {
	int num;
	cout << "*�������� �������� �� �����*" << endl;
	cout << "������� ����� �������� ��� ��������: ";
	cin >> num;

	file = fopen("example.dat", "rb");

	if (file == NULL) {
		cout << "������ ��� �������� �����";
		exit(1);
	}

	FILE* temp;
	temp = fopen("temp.dat", "wb");

	if (temp == NULL) {
		cout << "������ ��� �������� �����";
		exit(1);
	}

	Enrolee el;
	for (int i = 1; i <= n; i++) {
		fread(&el, sizeof(Enrolee), 1, file);

		if (ferror(file) != NULL) {
			cout << "������ ��� ������ �����";
			exit(4);
		}

		if (i != num) {
			fwrite(&el, sizeof(Enrolee), 1, temp);

			if (ferror(temp) != NULL) {
				cout << "������ ��� ������ �����";
				exit(2);
			}
		} else {
			n--;
			break;
		}
	}
	fclose(file);
	fclose(temp);
	remove("example.dat");
	rename("temp.dat", "example.dat");
}

void main() {
	setlocale(LC_ALL, "russian");

	SetConsoleCP(1251);			// ��������� ������� ��� �����
	SetConsoleOutputCP(1251);	// ��������� ������� ��� ������

	createFile();

	int decision = -1;
	while (decision != 0) {
		switch (decision) {
		case 1: readFile(); break;
		case 2: addFile(); break;
		case 3: deleteFile(); break;
		}
		if (n == 0) exit(1);
		cout << endl << "~ �������� ���������� ��������: 1 - ������ ����, 2 - �������� � ����, 3 - ������� �� ����� ~" << endl << "~ ";
		cin >> decision;
		cout << endl;
	}

	system("pause");
}