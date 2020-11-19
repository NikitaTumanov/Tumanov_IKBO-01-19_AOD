#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <clocale>
#include <Windows.h>
#include <map>
#include<iomanip>
#include <queue>
using namespace std;
map<char, string> codes;
map<char, int> freq;

struct MinHeapNode
{
	char data;
	int freq;
	MinHeapNode* left, * right;

	MinHeapNode(char data, int freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};


struct compare
{
	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		return (l->freq > r->freq);
	}
};



void storeCodes(struct MinHeapNode* root, string str)
{
	if (root == NULL)
		return;
	if (root->data != '$')
		codes[root->data] = str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}


priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
template<typename T> void print_queue(T& q, int size) {
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> q1 = q;
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> q2 = q;
	cout << "Алфавит:              ";
	while (!q.empty()) {
		if (q.top() != NULL) {
			cout << setw(4) << q.top()->data << " ";
		}

		q.pop();

	}
	cout << endl << "Количество вхождений: ";
	while (!q1.empty()) {
		if (q1.top() != NULL) {
			cout << setw(4) << q1.top()->freq << " ";
		}
		q1.pop();
	}
	cout << endl << "Вероятность:          ";
	while (!q2.empty()) {
		if (q2.top() != NULL) {
			cout << setw(4) << float(q2.top()->freq) / size << " ";
		}
		q2.pop();
	}

	std::cout << '\n';
}
void HuffmanCodes(int size)
{
	struct MinHeapNode* left, * right, * top;
	for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
		minHeap.push(new MinHeapNode(v->first, v->second));
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap2 = minHeap;
	print_queue(minHeap2, size);
	while (minHeap.size() != 1)
	{
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		top = new MinHeapNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	storeCodes(minHeap.top(), "");
}
void calcFreq(string str, int n)
{
	for (int i = 0; i < str.size(); i++) {
		freq[str[i]]++;

	}
}
string haffman_code(string input) {
	string encodedString;
	for (auto i : input)
		encodedString += codes[i];
	return encodedString;
}
void print_table(string str) {		
	cout << "Алфавит:              ";
	for (auto item : freq) {
		cout << setw(4) << item.first << " ";
	}
	cout << endl << "Количество вхождений: ";
	for (auto item : freq) {
		cout << setw(4) << item.second << " ";
	}
	cout << endl << "Вероятность:          ";
	for (auto item : freq) {
		cout.setf(std::ios::fixed);
		cout << setprecision(2) << float(item.second) / str.length() << " ";
	}
	cout << endl;
	cout << endl;
}
void connection() {	
	for (auto s : codes) {
		cout << s.first << ": " << s.second << endl;
	}
}
int toBin(int num)
{
	int bin = 0, k = 1;
	while (num)
	{
		bin += (num % 2) * k;
		k *= 10;
		num /= 2;
	}
	return bin;
}
string ascii_code(string input) {
	string asci = "";
	for (int i = 0; i < input.size(); ++i) {
		asci += to_string(toBin((int(input[i]))));
	}
	return asci;
}
void show(string a) {
	cout << "Коды символов: " << endl; connection();
	cout << "Код по Хаффману: " << haffman_code(a) << endl;
	cout << "Длина кода (алгоритм Хаффмана): " << haffman_code(a).length() << endl;
	cout << "Код по ASCII: " << ascii_code(a) << endl;
	cout << "Длина кода (ASCII): " << ascii_code(a).length() << endl;
	cout << "Дисперсия " << ((float)haffman_code(a).length() / ascii_code(a).length()) << endl;
}
int main()//главная функция
{
	setlocale(LC_ALL, "RUS");
	string str = "tumanov nikita alekseevich";
	calcFreq(str, str.length());
	print_table(str);
	HuffmanCodes(str.length());
	show(str);
	return 0;
}