// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
int main()
{
	vector<vector<int>> V;
	vector<int> col;
	ifstream file("fffff.txt");
	if (file.is_open()) {
		for (int i = 0; i < 50000; ++i) {
			for (int j = 0; j < 10000; ++j) {
				int s;
				file >> s;
				col.push_back(s);
			}
			V.push_back(col);
			col.clear();
		}
	}
	/*for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 9; ++j) {
			cout << V[i][j] << " ";
		}
		cout << endl;
	}*/
	system("pause");
}

