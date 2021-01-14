// ������������ ������ �10
// ������� 1

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <cstdlib> 
#include <iostream>; 
#include <math.h>
#include <ctime>
#include <locale>

using namespace std;

/* �������� � ������������ ������� */
int* create_arr(int n) {
	srand(time(0));
	int* a = new int[n];
	// ��������� ��������� ������� ��������� ������� �� 1 �� 10
	for (int i = 0; i < n; i++)
		a[i] = rand() % 10 + 1;
	return a;
}

/* ����� ������ � ������� */
void print_arr(int* arr, int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

/* ������������ ������������ ������ */
void delete_arr(int* arr) {
	delete[]arr;
}

/* ������� �� �������� */
void task(int* arr, int n) {
	cout << endl << "< ������� >" << endl;

	int temp_arr_n = n;							// ������ ���������� �������
	int* temp_arr = new int[temp_arr_n];		// ��������� ������ ��� ���������� �������

	// �������� �������� � �������� �������
	// ��� ���������� ���������� ��������, ����������� ��������� ������� � ����� ����� ������������� �����������
	int num1 = -1;
	while (num1 < 1 || num1 > temp_arr_n) {							// ���� ����������� ������
		cout << "������� ����� �������� ��� ��������: ";
		cin >> num1;
	}
	num1--;													// ������ �� 1 ������ ������
	
	for (int i = 0, j = 0; i < n; i++) {
		if (i != num1)							// �� ��������� � ����� ������ ������� ��� ��������
			temp_arr[j++] = arr[i];
	}
	temp_arr_n--;								// ��������� ������� �� ��� ��������, ������ ������� ����������� �� 1
	//

	cout << endl << "������ ����� �������� ��������:" << endl;
	print_arr(temp_arr, temp_arr_n);
	cout << endl;

	// ���������� �������� � �������� �������
	int el, num2 = -1;
	cout << "������� ������� ��� ����������: ";
	cin >> el;
	while (num2 < 1 || num2 > temp_arr_n + 1) {							// ���� ����������� ������
		cout << "������� ����� �������� ��� ����������: ";
		cin >> num2;
	}
	num2--;
	
	temp_arr_n++;								// ����������� �������, ������ ������ ������� ������������� �� 1
	for (int i = temp_arr_n - 1; i > num2; i--) {		// ����� ��������� ������� ������ ��������� ������ ������ �� ���� ������
		temp_arr[i] = temp_arr[i - 1];
	}
	temp_arr[num2] = el;			// ���������� ��������� �������� � �������� �������
	//

	cout << endl << "������ ����� ���������� ��������:" << endl;
	print_arr(temp_arr, temp_arr_n);

	// �������� ������������� �������
	delete_arr(temp_arr);
}

void main() {
	setlocale(LC_ALL, "russian");

	int n;
	cout << "������� ������ ������� n: ";
	cin >> n;
	cout << endl;

	int* arr = create_arr(n);
	cout << "�������� ������: " << endl;
	print_arr(arr, n);

	task(arr, n);				// ���������� ������� ��������

	// �������� ������������� �������
	delete_arr(arr);
}