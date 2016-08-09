#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct cus c;

struct cus {
	int t;
	int d;
	int s;
};

bool asc(c i, c j) {
	return i.t < j.t;
}

int main() {
	int num = 0;
	cin >> num;

	vector<c> v;

	for(int i=0;i<num;i++) {
		c nw;
		nw.s = i+1;
		cin >> nw.t;
		cin >> nw.d;
		v.push_back(nw);
	}

	sort(v.begin(), v.end(), asc);

	int time = 0;

	while(!v.empty()) {
		time++;
		for(int i=0;i<v.size();i++) {
			if(time > v[i].t) {
				v[i].d--;
				if(v[i].d == 0) {
					cout << v[i].s << " ";
					v.erase(v.begin()+i);
				}
			}
		}
	}

}