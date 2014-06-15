// Игра Жизнь.cpp: определяет точку входа для консольного приложения.

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <string.h>
#include <locale>
#include <stdio.h>
#include <tchar.h>
#include "stdlib.h"
#include <conio.h>
#include <time.h>
#include <iostream>

#include "Init.h"


using namespace std;

int main()
{
	setlocale(0,"RUS");
	int col = 77;							// Количество столбцов
	int row = 21;							// Количество строк
	bool exit = true;

	int** mattr = new int* [row];			// Создаем массив для текущего поколения
	for (int i = 0; i<row; i++){			// Строки
		mattr[i] = new int [col];			// Столбцы
	}
	int** newMattr = new int* [row];		// Создаем массив для зарождающегося поколения
	for (int i = 0; i<row; i++){			// Строки
		newMattr[i] = new int [col];		// Столбцы
	}

	printAbout();
	_getch();
	system("CLS"); // чистим экран
	if (selectMenuItem()){
		system("CLS");
		if (!fileMattrix(mattr, row, col))
			return 0;
		system("CLS");
	} else {
		system("CLS");
		randomMattrix(mattr, row,col);
	}

	initTor(mattr, row, col);

	printMassive(mattr, row, col);			// Печатаем массив
	_getch();
	while (exit){
		
		system("CLS");
		exit=lifeStep(mattr, newMattr, row, col);
		
		_getch();


	}
	return 0;
}


void printAbout(void){
	printf(" ===========================================================================\n");
	printf("  Это игра \"Жизнь\". Чтобы жить, нужно следовать правилам. Правила просты:\n");
	printf("\n");
	printf("\t1 Жизнь зарождается, если в смежных клетках ровно 3 живые\n");
	printf("\t2 Жизнь продолжается, если в смежных клетках  2 или 3 соседа\n");
	printf("\t3 Жизнь прекращается, если нарушается правило №2\n");
	printf("\n");
	printf("  В игре реализованы два способа ввода первого поколения: ручной и из файла\n");
	printf(" ===========================================================================\n");
	printf(" ======= Для продолжения нажмите любую клавишу =============================\n");
}

bool selectMenuItem(void){
	int unsigned item = 3;
	while (true){		// Выводим сообщение, и в цикле производим ввод и проверку
		printf(" ======= Для продолжения выберите способ ввода =============================\n");
		printf("  0 - сгененрировать случайную конфигурацию\n");
		printf("  1 - ввод из файла\n");
		printf(" ===========================================================================\n");
		if (cin >> item){
			if(item==0 || item==1){		
				if (item == 0){
					return false;
				} else {
					return true;
				}
			}
		} else {
			cin.clear();
			cin.sync();
		}
		system("CLS");
	}
	system("CLS");	
}

void initTor(int** mattr, const int row, const int col){
	for (int i = 1; i < col-1; i++){
		mattr[0][i]=mattr[row-2][i];
	}
	for (int i = 1; i < col-1; i++){ 
		mattr[row-1][i]=mattr[1][i];
	}
	for (int j = 1; j < row-1; j++){
		mattr[j][0]=mattr[j][col-2];
	}
	for (int j = 1; j < row-1; j++){
		mattr[j][col-1]=mattr[j][1];
	}

}

void tor(int** mattr, const int row, const int col){

	for (int i = 1; i < col-1; i++){
		mattr[row-2][i]=mattr[0][i];
	}
	for (int i = 1; i < col-1; i++){ 
		mattr[1][i]=mattr[row-1][i];
	}
	for (int j = 1; j < row-1; j++){
		mattr[j][col-2]=mattr[j][0];
	}
	for (int j = 1; j < row-1; j++){
		mattr[j][1]=mattr[j][col-1];
	}
}

void generationChange(int** mattr, int** newMattr, const int row, const int col){
	for (int i = 0; i<row; i++){
		for (int j = 0; j<col; j++){
			mattr[i][j]=newMattr[i][j];
		}

	}
}

bool isNull(int** newMattr, const int row, const int col){
	bool res = false;
	for (int i = 1; i<row-1; i++){
		for (int j = 1; j<col-1; j++){
			if (newMattr[i][j]!=0){
				return true;
			}
		}
	}
	return false;
}

void randomMattrix(int** mattr, const int row, const int col){
	srand((int)time(0));
	for (int i=1;i<row-1; i++){
		for (int j=1; j<col-1; j++){
			mattr[i][j] = rand() % 2;			
		}
	}
}

int fileMattrix(int** mattr, const int row, const int col){
	char *fileName = new char[255];
	printf(" ======= Введите имя файла с исходной конфигурацией ========================\n");
	cin >> fileName;
	FILE *inFile = fopen(fileName, "r");
	if (inFile == NULL) {
		system("CLS");
		printf(" ======= ОШИБКА: файл %s не найден =====================================\n", fileName);
		_getch();
		return 0;
	} else {
		for (int i = 1; i<row-1; i++){
			for (int j = 1; j<col-1; j++){
				fscanf(inFile, "%d", &mattr[i][j]);
			}
			fscanf(inFile, "\n");
		}
		fclose(inFile);
		return 1;
	}
}

int neighbors(int** mattr, const int i, const int j){
	int summ = mattr[i-1][j+1]+mattr[i-1][j]+mattr[i-1][j-1]+mattr[i][j+1]+mattr[i][j-1]+mattr[i+1][j-1]+mattr[i+1][j]+mattr[i+1][j+1];
	return summ;
}

void printMassive(int** mattr, const int row, const int col){
	for (int i=1;i<row-1; i++){
		/* вывод массива */
		
		for (int j=1; j<col-1; j++){
			if (mattr[i][j]==1){
				printf("#");
			} else {
				printf(" ");
			}
		}
	}
	printf("\n ======= Для генерации следующего поколения нажмите любую клавишу===========");

}


bool lifeStep(int** &mattr, int** &newMattr, const int row, const int col){
	bool res = true;
	int n = 0;

	int** buffer=mattr;

	initTor(mattr, row, col);
	for (int i=1;i<row-1; i++){
		for (int j=1; j<col-1; j++){
			n = neighbors(mattr, i, j);
			if (n==2 || n==3){						// Если соседей 2 или 3, то проверяем
				if  (n==2 && mattr[i][j]==0){			
					newMattr[i][j]=0;					// Если соседа два, а клетка мертвая, то жизнь в ней не появится
				} else {													
					newMattr[i][j]=1;					// Иначе жизнь зараждается/продолжается
				}
			} else {								// Иначе клетка гибнет
				newMattr[i][j]=0;
			}

		}
	}
	tor(mattr, row, col);									// Замыкаем поверхность
	res = isNull(newMattr, row, col);			// Если поколение не изменилось, то возвращаем ложь и выходим из игры

	mattr = newMattr;
	newMattr = buffer;



	printMassive(mattr, row, col);			// Печатаем массив
	return res;
}


