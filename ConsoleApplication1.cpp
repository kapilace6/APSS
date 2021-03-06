// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<iostream>
#include"time.h"
#include<fstream>
#include <omp.h>
using namespace std;
int main()
{
	srand(time(0));
	int x, y;
	cin>>x;
	cin >> y;
	int **array = new int*[y];
	ofstream sdf; 
	sdf.open("fffff.txt");
	//Creating the dynamically generated array
	#pragma omp parallel for
	for (int i = 0; i < y; i++) {
		array[i] = new int[x];
	}
	//Filling in values

	#pragma omp parallel for
	for (int i = 0; i < y; i++) {
		#pragma omp parallel for
		for (int j = 0; j < x; j++) {
				array[i][j] = 0;
		}
	}

	#pragma omp parallel for
	for (int i = 0; i < y; i++) {
		int Coeffecient = rand() % 5+1;
		//cout <<"Coeffecient"<< Coeffecient << endl;
		int count = (Coeffecient*x)/100;

		//cout <<"Count=" << count<< endl;
		int put = 0;

		while (put < count) {
			int index = rand() % x;
			if(array[i][index]==0)
				//cout << "Putting Num in Index " << index << endl;
				int val = rand() % 9+1;
				array[i][index] = 
				++put;
			}
		}
	//cout << "Printing to Console";
	/*
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	*/
	//Printing to File
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			sdf << array[i][j]<<" ";
		}
		sdf <<endl;
	}
	system("pause");
}

