// ������������ ������ �11
// ������� 1

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale>
#include <iostream>;

using namespace std;

FILE* file;										// ���������� �����
const char* filename = "output.txt";			// ��� �����

/* ��������� ����������������� ������ */
struct point {
	int key;			// �������� ���� �������� ������
	point* next;		// ��������� �� ��������� �������
};

/* �������� ������. ���������� ��������� �� ������ ������ */
point* create_list() {
	int n;
	cout << "������� ���������� ��������� ������: ";
	cin >> n;
	point* head, * p;				// ������ ������ ������ head � ��������� ������� �
	if (n == 0)						// �������� ������� ������ ��� ���������� ��������� ������ 0
		head = NULL;
	else {
		head = new(point);			// �������� ��������� �������� ������
		head->key = n;				// ������������ �������� ��������� ����
		head->next = NULL;			// ��������� ��� ��������� ������� � ������, �� "������" � ���� ���

		// � ����� ���������� ����������� �������� ���������� n-1 ���������, �� ��� ���� ������� p ��������� ������ head,
		// ����� ���������� ����������� ��������� � � ����� p. � ����� �������� head ������������� �������� p � ��
		// ����� ���������� �������� ���������
		for (int i = n - 1; i > 0; i--) {	
			p = new(point);
			p->key = i;
			p->next = head;     
			head = p;           
		}
	}
	return head;
}

/* ���������� �������� � ������ */
point* add_to_list(point* head) {
	int el, num;
	cout << "������� ������� ��� ����������: ";
	cin >> el;
	cout << "������� ����� �������� ��� ����������: ";
	cin >> num;

	point* p, * temp;				// ��������������� ��������� ��� ���������� ������ ��������� ������ � ������� ��������
	p = head;						// ���������� �������� ������
	int count = 2;

	// ���� ����������� � ������ �������, �� ������� ���������� �������� � ��������� ����� �������� ������
	if (num == 1) {
		temp = new(point);
		temp->key = el;
		temp->next = head;
		head = temp;			// ����� ��������� �� ������ - ����������� �������
	} else {
		// ����� ������ �� �����
		while (head != NULL) {
			// ���� ����� �������� �������� ��������� � ������� ������������, �� ����������� ������� � �������� ������
			if (count == num) {
				temp = new(point);
				temp->key = el;
				temp->next = head->next;
				head->next = temp;
				break;						// ��������������� ����� �� �����
			}
			count++;
			head = head->next;		// ����������� �� ������
		}
		head = p;				// ����������� ��������� �� ������
	}
	return head;
}

/* �������� �������� �� ������ */
point* delete_from_list(point* head) {
	int num;
	cout << "������� ����� �������� ��� ��������: ";
	cin >> num;

	point* p, * q;
	bool find_el = false;		// ���� ��������� ������ (true - ������� ������, false - �����)
	
	p = head;					// ���������� ��������� �� ������ ��������� ������

	// ���� ��������� ������� ������ �������, �� ������ ������������� �����
	if (num == 1) 
		head = p->next;
	else {
		int count = 2;
		// ���� ����������� ���� � ����� ������, ���� ����� ��������� ������� �������
		while (!find_el && head != NULL) {
			if (count == num) find_el = true;
			else {
				head = head->next;
				count++;
			}
		}
		if (!find_el) {
			cout << "������� �� ������." << endl;
		} else {
			q = head->next;				// ��������� ��������� q �� ��������� �������
			head->next = q->next;		// ������� ���������� ��������
			delete(q);
		}
		head = p;				// ����������� ��������� �� ������
	}

	return head;
}

/* ������ ������ */
void print_list(point* head) {
	point* p;
	p = head;

	if (head == NULL)						// ����� ��������� � ������ ������
		cout << "������ ������.";

	// ������ ������ �� �����
	while (head != NULL) {
		cout << head->key << " ";
		head = head->next;
	}
	
	cout << endl;
	head = p;
}

/* ������ ������ � ���� */
void write_list_in_file(point* head) {
	file = fopen(filename, "w");		// �������� ����� �� ������ (����������� � print_list)

	point* p;
	p = head;

	while (head != NULL) {
		fprintf(file, "%d ", head->key);
		head = head->next;
	}
	cout << "������ ������� � ����." << endl;
	head = p;

	fclose(file);
}

/* ����������� ������ */
point* delete_list(point* head) {
	point* q;
	while (head != NULL) {
		q = head;				// ���������� ��������� �� ������� ������� ������
		head = head->next;		// ����������� ��������� �� ������ �����
		delete(q);				// �������� ������������ ���������
	}
	head = NULL;	// ��������� ������ �� ���������
	cout << "������ ������� �����.\n";
	return head;
}

/* �������������� ������ �� ����� */
point* read_list_from_file() {
	file = fopen(filename, "r");		// �������� ����� �� ������
	point* head, * p, * q;

	// ���� ����� ��������� ����� �����, ������ ������ ����, ����� ��������� ������ � ����������� �� �����
	if (feof(file))
		head = NULL;  
	else {
		int n;							// �������� ���������� ������� create_list
		head = new(point);
		fscanf(file, "%d", &n);
		head->key = n;
		head->next = NULL;
		q = head;
		fscanf(file, "%d", &n); 

		while (!feof(file)) {
			p = new(point);
			p->key = n;
			p->next = NULL;
			head->next = p;
			head = head->next;
			fscanf(file, "%d", &n);
		}
		head = q;
	}
	fclose(file);
	return head;
}

void main() {
	setlocale(LC_ALL, "russian");

	point* head;

	cout << endl << "* �������� ������ *" << endl;
	head = create_list(); 

	cout << endl << "* ������ ������ *" << endl;
	print_list(head);       

	cout << endl << "* ���������� �������� � ������ *" << endl;
	head = add_to_list(head);
	cout << "���������:" << endl;
	print_list(head);

	cout << endl << "* �������� �������� �� ������ *" << endl;
	head = delete_from_list(head);
	cout << "���������:" << endl;
	print_list(head);

	cout << endl << "* ������ ������ � ���� *" << endl;
	write_list_in_file(head); 

	cout << endl << "* ����������� ������ *" << endl;
	head = delete_list(head);

	cout << endl << "* ������ ������ *" << endl;
	print_list(head);

	cout << endl << "* �������������� ������ �� ����� *" << endl;
	head = read_list_from_file();
	print_list(head);  

	cout << endl << "* ����������� ������ *" << endl;
	delete_list(head);
}