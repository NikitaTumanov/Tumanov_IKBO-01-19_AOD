#include <iostream> 
#include <iomanip> 
#include <cmath> 
#include<string> 
#include <fstream> 
#include<vector> 
using namespace std;
struct bank_account {
	int number;
	string name;
	string surname;
	string secondName;
	string address;
};
vector<bank_account>bank;
void print_data(bank_account a) {
	cout << "Number: " << a.number << " Name: " << a.name << " Surname: " << a.surname << " Second Name: " << a.secondName << " Address: " << a.address << endl;
}
void readFile() {
	bank_account temp;
	ifstream in("input.txt");
	while (!in.eof()) {
		in >> temp.number >> temp.name >> temp.surname >> temp.secondName >> temp.address;
		bank.push_back(temp);
	}
}
void readBinaryFile() {
	ifstream fin("output.txt", istream::binary);
	bank_account temp;
	int size = bank.size();
	for (int i = 0; i < size; i++) {
		fin.read((char*)&bank.at(i), sizeof(bank_account));
	}
	fin.close();
}

void toBinary()
{
	bank_account temp;
	ofstream fout("output.txt", ostream::binary);
	for (int i = 0; i < bank.size(); ++i)
	{
		fout.write((char*)&bank.at(i), sizeof(bank_account));
	}
	fout.close();
}
void find() {
	int a;
	cout << "Введите номер аккаунта, который хотите найти : ";
	cin >> a;
	for (int i = 0; i < bank.size(); i++) {
		if (bank[i].number == a) {
			print_data(bank[i]);
		}
	}
}
void change() {
	int a;
	string b;
	cout << "Введите номер аккаунта, который хотите поменять : ";
	cin >> a;
	cout << "Введите новую фамилию : ";
	cin >> b;
	readBinaryFile();
	for (int i = 0; i < bank.size(); i++) {
		if (bank[i].number == a) {
			bank[i].surname = b;
		}
	}
	toBinary();
}
void deletee() {
	int a;
	cout << "Введите номер аккаунта, который хотите удалить : ";
	cin >> a;
	readBinaryFile();
	for (int i = 0; i < bank.size(); i++) {
		if (bank[i].number == a) {
			bank.erase(bank.begin() + i);
		}
	}
	toBinary();
}
void show() {
	for (int i = 0; i < bank.size(); i++) {
		print_data(bank[i]);
	}
}
int main() {
	setlocale(LC_ALL, "RUS");
	string line;
	readFile();
	toBinary();
	readBinaryFile();
	show();
	find();
	change();
	show();
	deletee();
	show();
}