#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 
#include "windows.h"
#include <locale>
#include <iostream>

using namespace std;

FILE* file;	// Указатель на файл
int n;		// Количество записей в файле

/* Структура "Абитуриент" */
struct Enrolee {
	char surname[50];			// Фамилия
	char name[50];				// Имя
	char patronymic[50];		// Отчество
	int year;					// Год рождения
	int mark_1;					// Оценки вступительных экзаменов (3)
	int mark_2;
	int mark_3;
	double avg_mark;			// Средний балл
};

/* Формирование структуры */
Enrolee create() {
	Enrolee el;
	cout << "Фамилия: ";
	cin >> el.surname;
	cout << "Имя: ";
	cin >> el.name;
	cout << "Отчество: ";
	cin >> el.patronymic;
	cout << "Год рождения: ";
	cin >> el.year;
	cout << "Оценки вступительный экзаменов:" << endl << "1 экзамен: ";
	cin >> el.mark_1;
	cout << "2 экзамен: ";
	cin >> el.mark_2;
	cout << "3 экзамен: ";
	cin >> el.mark_3;
	el.avg_mark = (el.mark_1 + el.mark_2 + el.mark_3) / 3;
	return el;
}

/* Создание файла */
void createFile() {
	cout << "*Формирование файла*" << endl;

	file = fopen("example.dat", "wb");
	
	if (file == NULL) {
		cout << "Ошибка при открытии файла";
		exit(1);
	}
	
	cout << "Для начала формирования файла введите первый элемент" << endl;
	Enrolee el = create();											// Создание нового элемента
	fwrite(&el, sizeof(Enrolee), 1, file);							// Запись нового элемента в файл
	
	if (ferror(file) != NULL) {
		cout << "Ошибка при записи в файл";
		exit(2);
	}
	
	n = 1;															// Количество элементов стало 1
	cout << "*Файл сформирован*" << endl;
	fclose(file);
}

/* Чтение файла */
void readFile() {
	cout << "############ Содержимое файла ##############" << endl << "############################################" << endl;
	file = fopen("example.dat", "rb");
	
	if (file == NULL) {
		cout << "Ошибка при открытии файла";
		exit(1);
	}

	Enrolee el;
	int k = 0;
	while (!feof(file) && k < n) {
		fread(&el, sizeof(Enrolee), 1, file);

		if (ferror(file) != NULL) {
			cout << "Ошибка при чтении файла";
			exit(4);
		}

		cout << "Фамилия: " << el.surname << endl;
		cout << "Имя: " << el.name << endl;
		cout << "Отчество: " << el.patronymic << endl;
		cout << "Год рождения: " << el.year << endl;
		cout << "Оценки вступительных экзаменов (3): " << el.mark_1 << " " << el.mark_2 << " " << el.mark_3 << endl;
		cout << "Средний балл: " << el.avg_mark << endl;
		cout << "############################################" << endl;
		k++;
	}
	fclose(file);
	cout << "############################################" << endl;
}

/* Добавление нового элемента в файл */
void addFile() {
	cout << "*Добавление нового элемента в файл" << endl;
	Enrolee new_el;
	new_el = create();							// Создание нового элемента
				
	char after_sur[50];							// Фамилия, после которой добавляется элемент											
	cout << endl << "После элемента с какой фамилией добавить новый элемент?" << endl;
	cin >> after_sur;

	file = fopen("example.dat", "rb");
	
	if (file == NULL) {
		cout << "Ошибка при открытии файла";
		exit(1);
	}

	FILE* temp;									// Временный файл для записи в него данных. Далее переименовывается в исходный файл, а исходный удаляется
	temp = fopen("temp.dat", "wb");

	if (temp == NULL) {
		cout << "Ошибка при открытии файла";
		exit(1);
	}

	bool isAdded = false;
	Enrolee el;
	for (int i = 1; i <= n; i++) {
		fread(&el, sizeof(Enrolee), 1, file);

		if (ferror(file) != NULL) {
			cout << "Ошибка при чтении файла";
			exit(4);
		}

		fwrite(&el, sizeof(Enrolee), 1, temp);

		if (ferror(temp) != NULL) {
			cout << "Ошибка при записи файла";
			exit(2);
		}

		if (!strcmp(el.surname, after_sur)) {
			fwrite(&new_el, sizeof(Enrolee), 1, temp);

			if (ferror(temp) != NULL) {
				cout << "Ошибка при записи файла";
				exit(2);
			}

			isAdded = true;
		}
	}
	
	if (isAdded) {
		n++;
		cout << "Элемент добавлен" << endl;
	} else cout << endl << "Элемента с выбранной фамилией не найдено" << endl;

	fclose(file);
	fclose(temp);
	remove("example.dat");
	rename("temp.dat", "example.dat");
}

/* Удаление элемента из файла */
void deleteFile() {
	int num;
	cout << "*Удаление элемента из файла*" << endl;
	cout << "Укажите номер элемента для удаления: ";
	cin >> num;

	file = fopen("example.dat", "rb");

	if (file == NULL) {
		cout << "Ошибка при открытии файла";
		exit(1);
	}

	FILE* temp;
	temp = fopen("temp.dat", "wb");

	if (temp == NULL) {
		cout << "Ошибка при открытии файла";
		exit(1);
	}

	Enrolee el;
	int temp_n = n;
	for (int i = 1; i <= temp_n; i++) {
		fread(&el, sizeof(Enrolee), 1, file);

		if (ferror(file) != NULL) {
			cout << "Ошибка при чтении файла";
			exit(4);
		}

		if (i != num) {
			fwrite(&el, sizeof(Enrolee), 1, temp);

			if (ferror(temp) != NULL) {
				cout << "Ошибка при записи файла";
				exit(2);
			}
		} else {
			n--;
		}
	}
	fclose(file);
	fclose(temp);
	remove("example.dat");
	rename("temp.dat", "example.dat");
}

void main() {
	setlocale(LC_ALL, "russian");

	SetConsoleCP(1251);			// Кодировка консоли для ввода
	SetConsoleOutputCP(1251);	// Кодировка консоли для вывода

	createFile();

	int decision = -1;
	while (decision != 0) {
		switch (decision) {
		case 1: readFile(); break;
		case 2: addFile(); break;
		case 3: deleteFile(); break;
		}
		if (n == 0) exit(1);
		cout << endl << "~ Выберите дальнейшее действие: 1 - читать файл, 2 - добавить в файл, 3 - удалить из файла ~" << endl << "~ ";
		cin >> decision;
		cout << endl;
	}

	system("pause");
}
