// Ëàáîðàòîðíàÿ ðàáîòà ¹9
// Âàðèàíò 1.

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 
#include "windows.h"
#include <locale>
#include <iostream>
#include <io.h>

using namespace std;

FILE* source;						// Ôàéë èñòî÷íèê (F1.txt)
FILE* target;						// Ôàéë äëÿ ðåçóëüòàòà çàäàíèÿ (F2.txt)
const int MAXLINESIZE = 255;		// Ìàêñèìàëüíàÿ äëèíà ñòðîêè

/* Çàäàíèå 1 */
void task_1() {
	source = fopen("F1.txt", "r");		// Îòêðûòèå ôàéëà F1 äëÿ ÷òåíèÿ
	target = fopen("F2.txt", "w");		// Îòêðûòèå ôàéëà F2 äëÿ çàïèñè
	char buff[MAXLINESIZE];	

	int counter = 1;
	// Ïîêà íå êîíåö ôàéëà ñ÷èòûâàþòñÿ ñòðîêè ôàéëà F1 è ïðîâåðÿåòñÿ ÷åòíîñòü ñòðîê ñ÷åò÷èêîì counter
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

/* Çàäàíèå 2 */
void task_2() {
	source = fopen("F1.txt", "rb");		// Îòêðûòèå ôàéëà íà ÷òåíèå êàê äâîè÷íîãî
	fseek(source, 0, SEEK_END);			// Ïåðåìåùåíèå óêàçàòåëÿ â ôàéëå íà åãî êîíåö
	int size1 = ftell(source);			// ftell âîçâðàùàåò òåêóùåå çíà÷åíèå óêàçàòåëÿ â âèäå êîëè÷åñòâà áàéò
	fclose(source);

	target = fopen("F2.txt", "rb");
	fseek(target, 0, SEEK_END);
	int size2 = ftell(target);
	fclose(target);

	cout << "> Ðàçìåð ôàéëà F1.txt: " << size1 << " ÌÁ" << endl << "> Ðàçìåð ôàéëà F2.txt: " << size2 << " ÌÁ" << endl;
}

void main() {
	setlocale(LC_ALL, "russian");
	task_1();
	task_2();
}
