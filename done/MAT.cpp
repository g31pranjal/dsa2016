#include <iostream> 
#include <vector>
#include <algorithm>

using namespace std;

bool lesss(int i, int j) {
	return i<j;
}

int main() {
	int num=0,m=0,tmp=0;
	cin >> num;
	cin >> m;

	vector<int> v;

	for(int i=0;i<num;i++) {
		cin >> tmp;
		v.push_back(tmp);
	}

	sort(v.begin(), v.end(), lesss);

	int i = 0;
	int toys = 0;

	while(m - v[i] >= 0) {
		m -= v[i++];
		toys++;
	}

	cout << toys << endl;

}	