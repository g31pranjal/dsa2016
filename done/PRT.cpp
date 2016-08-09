#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

typedef struct {
	int o;
	int e;
} rng;

bool cs(rng i, rng j) {
	return i.e - i.o > j.e - j.o;
}

int main() {
	int num=0, tmp=0;
	cin >> num;
	vector<int> v;

	for(int i=0;i<num;i++) {
		cin >> tmp;
		v.push_back(tmp);
	}	

	sort(v.begin(), v.end(), less<int>());

	// for(int i=0;i<num;i++) {
	// 	cout << v[i] << endl;
	// }

	vector<rng> rlist;

	int base = v[0];
	int basei = 0;
		
	for(int i=1;i<num;i++) {
		if(i < num && v[i] <= base+4) {
			continue;
		}
		else {
			rng t;
			t.o = basei;
			t.e = i-1;
			base = v[i];
			basei = i;
			rlist.push_back(t);
		}
	}

	rng t;
	t.o = basei;
	t.e = num-1;
	rlist.push_back(t);

	sort(rlist.begin(), rlist.end(), cs);

	int cost=0;

	for(int i=0;i<rlist.size();i++) {
		int o = rlist[i].o;
		int e = rlist[i].e;
		bool free = true;
		for(int j=o;j<=e;j++) {
			if(v[j] == -1) {
				free = false;
				break;
			}
		}
		if(free) {
			for(int j=o;j<=e;j++) {
				v[j] = -1;
			}
			cost++;
		}

	}

	cout << cost << endl;

	// for(int i=0;i<rlist.size(); i++) {
	// 	cout << rlist[i].o << " , " << rlist[i].e << endl;
	// }
}