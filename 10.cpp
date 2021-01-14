// Лабораторная работа №10
// Вариант 1

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <cstdlib> 
#include <iostream>; 
#include <math.h>
#include <ctime>
#include <locale>

using namespace std;

/* Создание и формирование массива */
int* create_arr(int n) {
	srand(time(0));
	int* a = new int[n];
	// Генерация элементов массива случайным образом от 1 до 10
	for (int i = 0; i < n; i++)
		a[i] = rand() % 10 + 1;
	return a;
}

/* Вывод массив в консоль */
void print_arr(int* arr, int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

/* Освобождение выделененной памяти */
void delete_arr(int* arr) {
	delete[]arr;
}

/* Задание из варианта */
void task(int* arr, int n) {
	cout << endl << "< Задание >" << endl;

	int temp_arr_n = n;							// Размер временного массива
	int* temp_arr = new int[temp_arr_n];		// Временный массив для выполнения задания

	// Удаление элемента с заданным номером
	// Для уменьшения количества итераций, копирование исходного массива в новый будет производиться параллельно
	int num1 = -1;
	while (num1 < 1 || num1 > temp_arr_n) {							// Ввод корректного номера
		cout << "Введите номер элемента для удаления: ";
		cin >> num1;
	}
	num1--;													// Индекс на 1 меньше номера
	
	for (int i = 0, j = 0; i < n; i++) {
		if (i != num1)							// Не добавлять в новый массив элемент для удаления
			temp_arr[j++] = arr[i];
	}
	temp_arr_n--;								// Поскольку элемент не был добавлен, размер массива уменьшается на 1
	//

	cout << endl << "Массив после удаления элемента:" << endl;
	print_arr(temp_arr, temp_arr_n);
	cout << endl;

	// Добавление элемента с заданным номером
	int el, num2 = -1;
	cout << "Введите элемент для добавления: ";
	cin >> el;
	while (num2 < 1 || num2 > temp_arr_n + 1) {							// Ввод корректного номера
		cout << "Введите номер элемента для добавления: ";
		cin >> num2;
	}
	num2--;
	
	temp_arr_n++;								// Добавляется элемент, значит размер массива увеличивается на 1
	for (int i = temp_arr_n - 1; i > num2; i--) {		// Сдвиг элементов массива правее заданного номера вправо на одну ячейку
		temp_arr[i] = temp_arr[i - 1];
	}
	temp_arr[num2] = el;			// Размещение заданного элемента в заданную позицию
	//

	cout << endl << "Массив после добавления элемента:" << endl;
	print_arr(temp_arr, temp_arr_n);

	// Удаление динамического массива
	delete_arr(temp_arr);
}

void main() {
	setlocale(LC_ALL, "russian");

	int n;
	cout << "Введите размер массива n: ";
	cin >> n;
	cout << endl;

	int* arr = create_arr(n);
	cout << "Исходный массив: " << endl;
	print_arr(arr, n);

	task(arr, n);				// Выполнение задания варианта

	// Удаление динамического массива
	delete_arr(arr);
}