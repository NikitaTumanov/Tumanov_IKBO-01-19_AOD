#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

pair<uint32_t, vector<vector<uint32_t>>> multiplyOrder(vector<uint32_t> p){
	uint32_t n = p.size() - 1;
	vector<vector<uint32_t>> kVals(n, vector<uint32_t>(n, 0));
	vector<vector<uint32_t>> dp(n, vector<uint32_t>(n, 0));
	for (uint32_t l = 1; l < n; l++){
		for (uint32_t i = 0; i < n - l; i++){
			uint32_t j = i + l;
			dp[i][j] = UINT32_MAX;
			for (uint32_t k = i; k < j; k++){
				if (dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1] < dp[i][j]){
					dp[i][j] = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
					kVals[i][j] = k;
				}
			}
		}
	}
	return make_pair(dp[0][n - 1], kVals);
}

string getCorrectBracets(uint32_t i, uint32_t j, vector<vector<uint32_t>> kVals, bool zeroize = true){
	static string str;
	if (zeroize) str = "";
	if (i == j)
		str += "A" + to_string(i);
	else{
		str += "(";
		getCorrectBracets(i, kVals[i][j], kVals, 0);
		str += "*";
		getCorrectBracets(kVals[i][j] + 1, j, kVals, 0);
		str += ")";
	}
	return str;
}
int main(){
	setlocale(LC_ALL, "RUS");
	vector<uint32_t> sizes;
	int k = 0;
	for (uint32_t i = 0;; i++){
		uint32_t size[8] = {5,10,3,12,5,50,6,0};
		if (size[k] == 0){
			break; 
		}
		else {
			cout << "Размер[" << i << "]: " << size[k] << endl;
		}
		sizes.push_back(size[k]);
		k++;
	}
	pair<uint32_t, vector<vector<uint32_t>>> p = multiplyOrder(sizes);
	cout << "Расставленные скобки в произведении последовательности матриц: " << getCorrectBracets(0, p.second.size() - 1, p.second) << endl;
	cout << "Минимальное колличество скалярных умножений: " << p.first << endl;
	cout << "Эмпирическая оценка сложности алгоритма: О(n^3)" << endl;
	return 0;
}