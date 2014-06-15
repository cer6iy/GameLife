// ���� �����.cpp: ���������� ����� ����� ��� ����������� ����������.

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
	int col = 77;							// ���������� ��������
	int row = 21;							// ���������� �����
	bool exit = true;

	int** mattr = new int* [row];			// ������� ������ ��� �������� ���������
	for (int i = 0; i<row; i++){			// ������
		mattr[i] = new int [col];			// �������
	}
	int** newMattr = new int* [row];		// ������� ������ ��� �������������� ���������
	for (int i = 0; i<row; i++){			// ������
		newMattr[i] = new int [col];		// �������
	}

	printAbout();
	_getch();
	system("CLS"); // ������ �����
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

	printMassive(mattr, row, col);			// �������� ������
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
	printf("  ��� ���� \"�����\". ����� ����, ����� ��������� ��������. ������� ������:\n");
	printf("\n");
	printf("\t1 ����� �����������, ���� � ������� ������� ����� 3 �����\n");
	printf("\t2 ����� ������������, ���� � ������� �������  2 ��� 3 ������\n");
	printf("\t3 ����� ������������, ���� ���������� ������� �2\n");
	printf("\n");
	printf("  � ���� ����������� ��� ������� ����� ������� ���������: ������ � �� �����\n");
	printf(" ===========================================================================\n");
	printf(" ======= ��� ����������� ������� ����� ������� =============================\n");
}

bool selectMenuItem(void){
	int unsigned item = 3;
	while (true){		// ������� ���������, � � ����� ���������� ���� � ��������
		printf(" ======= ��� ����������� �������� ������ ����� =============================\n");
		printf("  0 - �������������� ��������� ������������\n");
		printf("  1 - ���� �� �����\n");
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
	printf(" ======= ������� ��� ����� � �������� ������������� ========================\n");
	cin >> fileName;
	FILE *inFile = fopen(fileName, "r");
	if (inFile == NULL) {
		system("CLS");
		printf(" ======= ������: ���� %s �� ������ =====================================\n", fileName);
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
		/* ����� ������� */
		
		for (int j=1; j<col-1; j++){
			if (mattr[i][j]==1){
				printf("#");
			} else {
				printf(" ");
			}
		}
	}
	printf("\n ======= ��� ��������� ���������� ��������� ������� ����� �������===========");

}


bool lifeStep(int** &mattr, int** &newMattr, const int row, const int col){
	bool res = true;
	int n = 0;

	int** buffer=mattr;

	initTor(mattr, row, col);
	for (int i=1;i<row-1; i++){
		for (int j=1; j<col-1; j++){
			n = neighbors(mattr, i, j);
			if (n==2 || n==3){						// ���� ������� 2 ��� 3, �� ���������
				if  (n==2 && mattr[i][j]==0){			
					newMattr[i][j]=0;					// ���� ������ ���, � ������ �������, �� ����� � ��� �� ��������
				} else {													
					newMattr[i][j]=1;					// ����� ����� �����������/������������
				}
			} else {								// ����� ������ ������
				newMattr[i][j]=0;
			}

		}
	}
	tor(mattr, row, col);									// �������� �����������
	res = isNull(newMattr, row, col);			// ���� ��������� �� ����������, �� ���������� ���� � ������� �� ����

	mattr = newMattr;
	newMattr = buffer;



	printMassive(mattr, row, col);			// �������� ������
	return res;
}


