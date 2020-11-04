#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <clocale>

using namespace std;

class Node {
public:
	int code;
	string name;
	Node(int code, string name) {
		this->code = code;
		this->name = name;
	}
};


template<typename T>
class HashTable {
	vector<list<T>> table;
	int size = 10;
	int hash(const T& n) {
		return n.code % size;
	}

	int hash(int code) {
		return code % size;
	}
public:
	HashTable() {
		size = 10;
		table.resize(size);
	}
	void add(const T& n) {
		table[hash(n)].push_back(n);
	}

	void rehash() {
		queue<T> q;
		for (int i = 0; i < size; ++i) {
			for (T el : table[i]) {
				q.push(el);
			}
		}
		size = size * 2 + 1;
		table.clear();
		table.resize(size);
		while (!q.empty()) {
			this->add(q.front());
			q.pop();
		}
		cout << "Рехеширование завершено\n";
	}

	T find(int code) {
		for (T q : table[hash(code)]) {
			if (q.code == code) return q;
		}
		return T(0, "не найдено");
	}

	void del(int code) {
		table[hash(code)].erase(remove_if(table[hash(code)].begin(), table[hash(code)].end(), [code](const T t) {
			return t.code == code;
			}), table[hash(code)].end());
	}

	void out() {
		for (int i = 0; i < size; ++i) {
			for (T q : table[i]) {
				cout << q.code << "\t" << q.name << "\n";
			}
		}
	}

	void show() {
		for (int i = 0; i < size; ++i) {
			cout << "Index " << i<<": ";
			for (T q : table[i]) {
				cout << q.name << "\t";
			}
			cout << endl;
		}
	}
};

int main(){
	setlocale(LC_ALL,"rus");
	HashTable<Node> hash;
	hash.add(Node(986843, "Table"));
	hash.add(Node(187196, "Book"));
	hash.add(Node(987172, "Pen"));
	hash.add(Node(321686, "Jacket"));
	hash.add(Node(648987, "Shoes"));
	hash.add(Node(108981, "Toy"));
	int k, code;
	string name;
	cout << "Введите 0 для выхода из программы\nВведите 1 для ввода нового товара\nВведите 2 для удаления товара\nВведите 3 для просмотра всех товаров\nВведите 4 для поиска товара\nВведите 5 для рехеширования\nВведите 6 для вывода цепи\n";
	while (true) {
		cin >> k;
		switch (k) {
		case 0:
			return 0;
		case 1:
			cout << "Введите шестизначное число ";
			cin >> code;
			cout << "Введите название товара ";
			cin >> name;
			hash.add(Node(code, name));
			break;
		case 2:
			cout << "Введите шестизначное число ";
			cin >> code;
			hash.del(code);
			break;
		case 3:
			hash.out();
			break;
		case 4:
			cout << "Введите шестизначное число ";
			cin >> code;
			cout << "Название товара с номером " << code << ": " << hash.find(code).name << endl;
			break;
		case 5:
			hash.rehash();
			break;
		case 6:
			hash.show();
			break;
		}
	}
}
