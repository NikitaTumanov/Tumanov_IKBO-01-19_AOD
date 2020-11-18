#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
//№ 14.1.3
vector <vector<int>> arr;
struct Node {
	int num;
	vector <pair<Node*, int>> sv;
	Node(int num);
};
Node::Node(int num) {
	this->num = num;
}
vector <Node*> gr;
void graph() {
	gr.resize(arr.size());
	for (int i = 0; i < arr.size(); i++) gr[i] = new Node(i + 1);
}

void create() {
	bool* b = new bool[arr.size()];
	for (int i = 1; i < arr.size(); i++) b[i] = false;
	b[0] = true;
	int min, num_par, num_ch;
	for (int k = 0; k < gr.size() - 1; k++) {
		min = 10000000000;
		for (int i = 0; i < arr.size(); i++) {
			if (b[i] == true) {
				for (int j = 0; j < arr[i].size(); j++) {
					if (!b[j] and arr[i][j] != 0 and arr[i][j] < min) {
						num_par = i;
						num_ch = j;
						min = arr[i][j];
					}
				}
			}
		}
		gr[num_par]->sv.push_back(make_pair(gr[num_ch], min));
		gr[num_ch]->sv.push_back(make_pair(gr[num_par], min));
		b[num_ch] = true;
	}
}

void input() {
	int nodes, k, number, length;
	cout << "Введите количество вершин графа: ";
	cin >> nodes;
	arr.resize(nodes);
	for (int i = 0; i < arr.size(); i++) {
		arr[i].resize(nodes);
		for (int j = 0; j < arr[i].size(); j++) arr[i][j] = 0;
	}
	for (int i = 0; i < arr.size() - 1; ++i) {
		cout << "Количество связей у вершины " << i + 1 << " (без повторений): ";
		cin >> k;
		for (int j = 0; j < k; j++) {
			cout << j + 1 << " ребро:" << endl;
			cout << "   Номер вершины, к которой идёт связь: ";
			cin >> number;
			cout << "   Длина связи: ";
			cin >> length;
			arr[i][number - 1] = length;
			arr[number - 1][i] = length;
		}
	}
}

void show() {
	vector <vector<int>> ost_tree;
	ost_tree.resize(arr.size());
	for (int i = 0; i < ost_tree.size(); i++) {
		ost_tree[i].resize(ost_tree.size());
		for (int j = 0; j < ost_tree[i].size(); j++) ost_tree[i][j] = 0;
	}
	for (int i = 0; i < gr.size(); i++) {
		for (int j = 0; j < gr[i]->sv.size(); j++) {
			ost_tree[gr[i]->num - 1][gr[i]->sv[j].first->num - 1] = gr[i]->sv[j].second;
			ost_tree[gr[i]->sv[j].first->num - 1][gr[i]->num - 1] = gr[i]->sv[j].second;
		}
	}
	cout << endl;
	cout <<"№  ";
	for (int i = 0; i < ost_tree.size(); i++) cout << i + 1 << "  ";
	cout << endl << endl;
	for (int i = 0; i < ost_tree.size(); i++) {
		cout << i + 1 << "  ";
		for (int j = 0; j < ost_tree[i].size(); j++) {
			if (ost_tree[i][j] < 10) {
				cout << ost_tree[i][j] << " |";
			}
			else {
				cout << ost_tree[i][j] << "|";
			}
		}
		cout << endl;
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	arr = {
		{0,20,0,0,0,23,1},
		{20,0,15,0,0,0,4},
	    {0,15,0,3,0,0,9},
		{0,0,3,0,17,0,16},
		{0,0,0,17,0,28,25},
		{23,0,0,0,28,0,36},
		{1,4,9,16,25,36,0}
	};
	//input();
	graph();
	create();
	show();
}