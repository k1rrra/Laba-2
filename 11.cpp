// Лабораторная работа №11
// Вариант 1

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale>
#include <iostream>;

using namespace std;

FILE* file;										// Переменная файла
const char* filename = "output.txt";			// Имя файла

/* Структура однонаправленного списка */
struct point {
	int key;			// Ключевое поле элемента списка
	point* next;		// Указатель на следующий элемент
};

/* Создание списка. Возвращает указатель на голову списка */
point* create_list() {
	int n;
	cout << "Введите количество элементов списка: ";
	cin >> n;
	point* head, * p;				// Голова нового списка head и временный элемент р
	if (n == 0)						// Создание пустого списка при количестве элементов равном 0
		head = NULL;
	else {
		head = new(point);			// Создание головного элемента списка
		head->key = n;				// Присваивание значения ключевому полю
		head->next = NULL;			// Поскольку это последний элемент в списке, то "хвоста" у него нет

		// В цикле происходит аналогичное создание оставшихся n-1 элементов, но при этом элемент p опережает голову head,
		// чтобы оставалась возможность сохранить её в хвост p. В конце итерации head присваивается значение p и он
		// снова становится головным элементом
		for (int i = n - 1; i > 0; i--) {	
			p = new(point);
			p->key = i;
			p->next = head;     
			head = p;           
		}
	}
	return head;
}

/* Добавление элемента в список */
point* add_to_list(point* head) {
	int el, num;
	cout << "Введите элемент для добавления: ";
	cin >> el;
	cout << "Введите номер элемента для добавления: ";
	cin >> num;

	point* p, * temp;				// Вспомогательные указатели для сохранения головы исходного списка и вставки элемента
	p = head;						// Сохранение исходной головы
	int count = 2;

	// Если вставляется в первую позицию, то элемент становится головным и следующим имеет исходную голову
	if (num == 1) {
		temp = new(point);
		temp->key = el;
		temp->next = head;
		head = temp;			// Новый указатель на голову - добавленный элемент
	} else {
		// Обход списка до конца
		while (head != NULL) {
			// Если номер текущего элемента совпадает с номером вставляемого, то вставляется элемент с заданным ключом
			if (count == num) {
				temp = new(point);
				temp->key = el;
				temp->next = head->next;
				head->next = temp;
				break;						// Преждевременный выход из цикла
			}
			count++;
			head = head->next;		// Продвижение по списку
		}
		head = p;				// Возвращение указателя на голову
	}
	return head;
}

/* Удаление элемента из списка */
point* delete_from_list(point* head) {
	int num;
	cout << "Введите номер элемента для удаления: ";
	cin >> num;

	point* p, * q;
	bool find_el = false;		// Флаг состояния поиска (true - элемент найден, false - иначе)
	
	p = head;					// Сохранение указателя на голову исходного списка

	// Если требуется удалить первый элемент, то голове присваевается хвост
	if (num == 1) 
		head = p->next;
	else {
		int count = 2;
		// Цикл остановится либо в конце списка, либо когда следующий элемент искомый
		while (!find_el && head != NULL) {
			if (count == num) find_el = true;
			else {
				head = head->next;
				count++;
			}
		}
		if (!find_el) {
			cout << "Элемент не найден." << endl;
		} else {
			q = head->next;				// Установка указателя q на удаляемый элемент
			head->next = q->next;		// Пропуск удаляемого элемента
			delete(q);
		}
		head = p;				// Возвращение указателя на голову
	}

	return head;
}

/* Печать списка */
void print_list(point* head) {
	point* p;
	p = head;

	if (head == NULL)						// Вывод сообщения о пустом списке
		cout << "Список пустой.";

	// Печать списка до конца
	while (head != NULL) {
		cout << head->key << " ";
		head = head->next;
	}
	
	cout << endl;
	head = p;
}

/* Запись списка в файл */
void write_list_in_file(point* head) {
	file = fopen(filename, "w");		// Открытие файла на запись (комментарии в print_list)

	point* p;
	p = head;

	while (head != NULL) {
		fprintf(file, "%d ", head->key);
		head = head->next;
	}
	cout << "Список записан в файл." << endl;
	head = p;

	fclose(file);
}

/* Уничтожение списка */
point* delete_list(point* head) {
	point* q;
	while (head != NULL) {
		q = head;				// Сохранение указателя на текущий элемент списка
		head = head->next;		// Перемещение указателя по списку далее
		delete(q);				// Удаление сохраненного указателя
	}
	head = NULL;	// Указатель никуда не указывает
	cout << "Список успешно удалён.\n";
	return head;
}

/* Восстановление списка из файла */
point* read_list_from_file() {
	file = fopen(filename, "r");		// Открытие файла на чтение
	point* head, * p, * q;

	// Если сразу обнаружен конец файла, значит список пуст, иначе создается список и считывается из файла
	if (feof(file))
		head = NULL;  
	else {
		int n;							// Создание аналогично функции create_list
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

	cout << endl << "* Создание списка *" << endl;
	head = create_list(); 

	cout << endl << "* Печать списка *" << endl;
	print_list(head);       

	cout << endl << "* Добавление элемента в список *" << endl;
	head = add_to_list(head);
	cout << "Результат:" << endl;
	print_list(head);

	cout << endl << "* Удаление элемента из списка *" << endl;
	head = delete_from_list(head);
	cout << "Результат:" << endl;
	print_list(head);

	cout << endl << "* Запись списка в файл *" << endl;
	write_list_in_file(head); 

	cout << endl << "* Уничтожение списка *" << endl;
	head = delete_list(head);

	cout << endl << "* Печать списка *" << endl;
	print_list(head);

	cout << endl << "* Восстановление списка из файла *" << endl;
	head = read_list_from_file();
	print_list(head);  

	cout << endl << "* Уничтожение списка *" << endl;
	delete_list(head);
}