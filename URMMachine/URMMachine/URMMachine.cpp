
#include <fstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <cstring>
#include <string>
#include <array>


using namespace std;



int main() {
	//definisco il registro di 256 celle
	int reg[256] = {0};

	//creo il vettore di array
	vector<array<unsigned int, 4>> v;
	//apro il file
	string link;
	cout << "Insert the binary file name: " << endl;
	cin >> link;
	ifstream file(link, ios::binary);
	int len = 0;
	
	//leggo il file binario e immagazzino tutti i valori in una matrice
	if (file.is_open()) {
		file.seekg(0, ios::end);
		len = file.tellg();
		file.seekg(0, ios::beg);
		//cout << len << endl;
		array<unsigned int, 4> p = { 0 };

		for (int i = 0; i < len / 4; i++) {
			for (int j = 0; j < 4; j++) {
				file.read((char*)&p[j], 1);
			}
			v.push_back(p);
		}
		file.close();
	}
	else {
		cout << "The file is not open properly." << endl;
		return 0;
	}
	
	for (int i = 0; i < len / 4; i++) {
		for (int j = 0; j < 4; j++) {
			v[i][j] = v[i][j];
			cout << v[i][j] << "  ";
		}
		cout << endl;		
	}

	//svolgo le istruzioni
	for (int n = 0; n < len / 4; ) {
		switch (v[n][0]) {
		case 0:
			reg[v[n][1]] = 0;
			cout << "Zero cell " << v[n][1] << endl;
			n++;
			break;

		case 1:
			reg[v[n][1]]++;
			cout << "Increase cell " << v[n][1] << endl;
			n++;
			break;

		case 2:
			reg[v[n][2]] = reg[v[n][1]];
			cout << "Project cell " << v[n][1] << " into cell " << v[n][2] << endl;
			n++;
			break;

		case 3:
			cout << "Jump to line " << v[n][3] << " if cell " << v[n][1] << " is equal to cell " << v[n][2] << endl;
				if (reg[v[n][2]] == reg[v[n][1]]) {
					n = v[n][3];
				}
				else {
					n++;
				}
				break;

			default:
				cout << "Error! The operator is not correct";
				return 0;
				break;
		}
	}
	cout << "\nThe result of the URM machine is: " << reg[0] << endl;
}